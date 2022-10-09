#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

void find(char * path,char * file_name)
{
    int fd;
    char buf[512],*p;
    struct stat st;
    struct dirent de;
    if((fd=open(path,O_RDONLY))<0){
        fprintf(2,"find: cannot open %s\n",path);
        return ;
    }
    if(fstat(fd,&st)<0){
        fprintf(2,"find: cannot stat %s\n",path);
    }
    
    switch(st.type){
        case T_FILE:
            if(strcmp(file_name,path)){
                fprintf(1,path,strlen(path));
            }
        case T_DIR:
            strcpy(buf,path);
            p=buf+strlen(buf);
            *p++='/';
            while(read(fd,&de,sizeof(de))==sizeof(de)){
                if(de.inum==0) continue;
                if(strcmp(".",de.name)==0) continue;
                if(strcmp("..",de.name)==0) continue;
                memmove(p,de.name,DIRSIZ);
                if(stat(buf,&st)<0){
                    printf("ls: cannot stat %s\n",buf);
                    continue;
                }
                if(st.type==T_DIR){
                    find(buf,file_name);
                    continue;
                }
                if(strcmp(file_name,de.name)==0){
                    printf("%s\n",buf);
                }
                
                
            }
    }
    close(fd);
    return;

}


int main(int argc,char * argv[])
{
    if(argc<2){
        fprintf(2,"too few parameters...\n");
        exit(0);
    }
    if(argc>3){
        fprintf(2,"too many parameter...\n");
        exit(0);
    }
    
    find(argv[1],argv[2]);
   
    
    exit(0);
}