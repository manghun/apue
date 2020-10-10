#include <stdio.h>

static void b()
{
    printf("%s():Begin.\n",__FUNCTION__);

    printf("%s():Call b().\n",__FUNCTION__);



    printf("%s():a() returned.\n",__FUNCTION__);
    printf("%s():End.\n",__FUNCTION__);

}
static void a()
{
    printf("%s():Begin.\n",__FUNCTION__);

    printf("%s():Call b().\n",__FUNCTION__);

    b();


    printf("%s():a() returned.\n",__FUNCTION__);
    printf("%s():End.\n",__FUNCTION__);

}

int main()
{
    printf("%s():Begin.\n",__FUNCTION__);

    printf("%s():Call a().\n",__FUNCTION__);

    a();


    printf("%s():a() returned.\n",__FUNCTION__);
    printf("%s():End.\n",__FUNCTION__);

    exit(0);
}

