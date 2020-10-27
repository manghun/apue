#ifndef PROTO_H__
#define PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROJ 'a'

#define PATHMAX 1024
#define DATAMAX 1024

enum
{
    MSG_PATH = 1,
    MSG_DATA,
    MSG_EOT
};

struct msg_path_st
{
    long mytype;
    char path[PATHMAX]; /*ASCIIZ带尾0的串*/
};

struct msg_data_st
{
    long mytype;
    char data[DATAMAX];
    int datalen;
};

struct msg_eot_st
{
    long mytype;
    
};

#endif