#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

void find(char * file_name,char * path)
{
    int fd;
    if((fd=open(path,O_RDONLY))<0){
        fprintf(2,"find: cannot open %s\n",path);
        return ;
    }
    struct stat st;
    struct dirent de;
    if(fstat(fd,&st)<0){
        fprintf(2,"find: cannot stat %s\n",path);
    }
    switch(st.type){
        case T_FILE:
            
        case T_DIR:
    }

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
    find(argv[1],".");
    
    return 0;
}