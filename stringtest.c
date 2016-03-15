//string test
#include <stdio.h>
#include <stdlib.h>


int main(int argc,char **argv)
{
    int intlist[argc-1];
    int i;
    for(i=1; i<argc; i++)
    {
        intlist[i-1]=atoi(argv[i]);
    }
    int k;
    k=sum_it(intlist,sizeof(intlist)/sizeof(intlist[0]));
    printf("%d\n",k);
    return 0;

}

int sum_it(int ints[],int arrlen)
{
    int sum;
    int i;
    for(i=0; i<arrlen; i++)
    {
        //printf("%d\n",ints[i]);
        sum+=ints[i];

    }
    return sum-1;
}
