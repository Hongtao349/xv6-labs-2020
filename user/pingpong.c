#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int fd[2];
    int fd1[2];
    int pid;
    char buf[1];
    pipe(fd);
    pipe(fd1);
    pid=fork();
    if(pid==0){
        close(fd1[0]);//关闭fd1的读端
        
        close(fd[1]);//关闭fd的写端
        read(fd[0],buf,1);
        if(buf[0]=='0'){
            fprintf(2,"%d: received ping\n",getpid());
            write(fd1[1],"1",1);
            exit(0);
        }else{
            fprintf(2,"can't read\n");
        }
        
    }else{
        close(fd[0]);//关闭fd的读端
        write(fd[1],"0",1);
        close(fd[1]);//关闭fd1的写端
        read(fd1[0],buf,1);
        if(buf[0]=='1'){
            fprintf(2,"%d: received pong\n",getpid());
        }
        exit(0);
    }
    
    return 0;
}