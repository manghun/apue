#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mytbf.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

//typedef void (*sighandler_t)(int);
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;

static struct mytbf_st *job[MYTBF_MAX];
static int inited = 0;
static pthread_t tid_alrm;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
//static sighandler_t alrm_handler_save;

struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
    pthread_mutex_t mut;
};

static void *thr_alrm(void *p)
{
    int i;

    //alarm(1);
    while (1)
    {
        pthread_mutex_lock(&mut_job);
        for (i = 0; i < MYTBF_MAX; i++)
        {
            if (job[i] != NULL)
            {
                pthread_mutex_lock(&job[i]->mut);
                job[i]->token += job[i]->cps;
                if (job[i]->token > job[i]->burst)
                    job[i]->token = job[i]->burst;
                pthread_mutex_unlock(&job[i]->mut);
            }
        }
        pthread_mutex_unlock(&mut_job);
        sleep(1);
    }
}

static void module_unload()
{
    int i;
    //signal(SIGALRM, alrm_handler_save);
    //alarm(0);

    pthread_cancel(tid_alrm);
    pthread_join(tid_alrm,NULL);

    for (i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] != NULL)
        {
            mytbf_destroy(job[i]);
        }
        
    }   

    pthread_mutex_destroy(&mut_job);
}

static void module_load(void)
{
    // = signal(SIGALRM,alrm_handler);
    //alarm(1);
    
    int err;
    err = pthread_create(&tid_alrm, NULL, thr_alrm, NULL);
    if (err)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }

    pthread_create();
    atexit(module_unload);
}

static int get_free_pos_unlocked(void)
{
    for (int i = 0; i < MYTBF_MAX; i++)
    {
        if (job[i] == NULL)
            return i;
    }

    return -1;
}

static int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

mytbf_t *mytbf_init(int cps, int burst)
{

    struct mytbf_st *me;
    int pos;
/* 
    if (!inited)
    {
        module_load();
        inited = 1;
    }
*/
    pthread_once(&init_once,module_load);
    me = malloc(sizeof(*me));

    if (me == NULL)
        return NULL;
    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    pthread_mutex_init(&me->mut, NULL);

    pthread_mutex_lock(&mut_job);
    pos = get_free_pos_unlocked();

    if (pos < 0)
    {
        pthread_mutex_unlock(&mut_job);
        free(me);
        return NULL;
    }

    me->pos = pos;

    job[pos] = me;
    pthread_mutex_unlock(&mut_job);
    return me;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    int n;

    if (size <= 0)
        return -EINVAL;

    pthread_mutex_lock(&me->mut);
    while (me->token <= 0)
    {
        pthread_mutex_unlock(&me->mut);
        sched_yield();
        pthread_mutex_lock(&me->mut);
    }

    n = min(me->token, size);

    me->token -= n;
    pthread_mutex_unlock(&me->mut);
    return n;
}

int mytbf_returntoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    if (size <= 0)
        return -EINVAL;

    pthread_mutex_lock(&me->mut);
    me->token += size;

    if (me->token > me->burst)
        me->token = me->burst;

    pthread_mutex_unlock(&me->mut);

    return size;
}

int mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;

    pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_unlock(&mut_job);
    pthread_mutexattr_destroy(&me->mut);
    free(ptr);

    return 0;
}
