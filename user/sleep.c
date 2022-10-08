#include "kernel/types.h"
#include "user/user.h"

int check(char * ch,int len)
{
    int i;
    for(i=0;i<len;i++){
        if(ch[i]>57||ch[i]<48){
            fprintf(2,"parameters isn't a number\n");
            return 1;
        }
    }
    return 0;
}

int main(int argc,char * argv[])
{
    int i;
    if(argc<=1){
        fprintf(2,"Usage: sleep times...\n");
        exit(1);
    }    

    for(i=1;i<argc;i++){
        if(check(argv[i],strlen(argv[i]))==0){
            int times=atoi(argv[i]);
            fprintf(2,"(nothing happens for a little while)\n");
            sleep(times);
        }else{
            exit(1);
        }
        
    }
    exit(0);
}
