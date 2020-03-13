#include"file_lib.h"
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>



int lock(int fd,struct flock * _lock){
    int endOfFile;
    if(0>(endOfFile=lseek(fd,0,SEEK_END))){
        perror("lseek error line 12");
        exit(-1);
    }    
    if(0>lseek(fd,0,SEEK_SET)){
        perror("lseek error line 18");
        exit(-1);
    }
    
   // _lock->l_len=endOfFıle;
   // _lock->l_start=0;
   // _lock->l_pid=getpid();
    _lock->l_type=F_WRLCK;
    fcntl(fd,F_SETLKW,_lock);
    

    return 0;
}


int unlock(int fd,struct flock * _lock){
    _lock->l_type=F_UNLCK;
    fcntl(fd,F_SETLK,_lock);
    return 0;
}


/**has to be in readonly mode*/
int get_first_avalible_pos(int fd){

    int read_byte=0;
    char *temp=malloc(sizeof(char));
    int endOfFile=lseek(fd,0,SEEK_END);
    if(endOfFile<-1)perror("line 31");
    if(0>lseek(fd,0,SEEK_SET))perror("line 32");

    printf("end of file %d",endOfFile);
    int i=0;  
    int pos=0;
    int interpos=0;
    int beforeisnewline=0;
    do{
        read_byte=read(fd,temp,1); 
        if(read_byte<0)perror("asd");
        
        if('\n'==*temp  ){ 
            if(beforeisnewline){
                return i+1;
            }
            pos=i;
            beforeisnewline=1;
        }else 
            beforeisnewline=0;
        //printf("%c",*temp);
        ++i;
        if(i>endOfFile){
            
            if(i!=0)return i;
            return endOfFile;
        }
    
    }while(read_byte!=0);


}

void unit_test_get_first_avalible_pos(){
    int fd=open("/home/erkan/Desktop/workspace/hw1/text2.txt",O_RDWR|O_SYNC);   
    if(fd<0) {
        printf("hata");   
    }
    printf("pos is :::%d\n",get_first_avalible_pos(fd));
    close(fd);
}



int write_in_a_post(int fd,void * buf,int size,int pos){
    //printf("cur post%d",lseek(fd,SEEK_SET,pos));//lseek çalışmıyor 
    
    int doIinstart= (0==lseek(fd,0,SEEK_CUR));
    if(fd<0){
        printf("invalid file\n");
    }
    if(0>lseek(fd,pos,SEEK_SET)){
        perror("lseek\n");
        exit(-1);
    }
    strcat(buf,"\n");
    //printf("I will print %d",lseek(fd,0,SEEK_CUR));
    
    write(fd,buf,strlen(buf));
    
}

void unit_test_write_in_a_post(){
    
    int fd=open("/home/erkan/Desktop/workspace/hw1/text2.txt",O_RDWR|O_SYNC);
    if(fd<0)perror("file");
    int at=get_first_avalible_pos(fd);  
    printf("avalible pos:::%d\n",at);
  
    char str[100]="123456789";
    write_in_a_post(fd,str,strlen(str),at-1);
    close(fd);
}