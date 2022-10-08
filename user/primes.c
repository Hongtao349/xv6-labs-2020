#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void proc_node(int fd_left[]){
    close(fd_left[1]);
    int num;
    //得到第一个数字
    int n=read(fd_left[0],(void *)&num,sizeof(int));
    if(n==0){//左邻居的写通道已经全部关闭
        return ;
    }
    //第一个数字一定是质数，打印
    fprintf(1,"prime %d\n",num);
    int pid;
    int fd_right[2];
    pipe(fd_right);
    pid=fork();
    if(pid==0){
        proc_node(fd_right);
        return ;
    }else{
        int num1;
        //继续读取数字
        close(fd_right[0]);
        while(read(fd_left[0],(void *)&num1,sizeof(int))){
            if(num1%num){
                write(fd_right[1],(void *)&num1,sizeof(int));
            }
        }
        close(fd_right[1]);
        int status;
        wait(&status);
        exit(0);
    }
       
}

int main()
{
    int pid;
    int i;
    int fd_ori[2];
    pipe(fd_ori);
    int start=2;//开始结点
    int end=35;//结束结点
    pid=fork();
    if(pid==0){
        proc_node(fd_ori);
        exit(0);
    }else{
        close(fd_ori[0]);
        fprintf(1,"prime %d\n",start);       
        for(i=start+1;i<=end;i++){
            if(i%2){
                write(fd_ori[1],(void *)&i,sizeof(int));
            }
        }
        close(fd_ori[1]);
        int status;
        wait(&status);
        exit(0);
    }

    return 0;
}