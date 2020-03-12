#include"file_lib.h"
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>



int lock(struct flock * _lock,int pid){
    

    return 0;
}


int unlock(struct flock * _lock, int pid){


    return 0;
}


/**has to be in readonly mode*/
int get_first_avalible_pos(int fd){

    int read_byte=0;
    char *temp=malloc(sizeof(char));
    char temp2;
    int endOfFile=lseek(fd,0,SEEK_END);
    if(endOfFile<-1)perror("line 31");
    if(0>lseek(fd,0,SEEK_SET))perror("line 32");

    printf("end of file %d",endOfFile);
    int i=0;  
    int pos=0;
    do{
        read_byte=read(fd,temp,1); 
        if(read_byte<0)perror("asd");
        
   
        if('\0'==*temp ){
            //return i;
        }else if('\n'==*temp  ){
            pos=i;
        }
        //printf("%c",*temp);
        ++i;
        if(i>endOfFile){
            if(i!=0)return i;
            return endOfFile;
        }
        temp2=*temp;
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
    pos=pos-1;
    int doIinstart= (0==lseek(fd,0,SEEK_CUR));
    if(fd<0){
        printf("invalid file\n");
    }
    if(0>lseek(fd,pos,SEEK_SET)){
        perror("lseek\n");
        exit(-1);
    }
    strcat(buf,"\n");
    printf("I will print %d",lseek(fd,0,SEEK_CUR));
    
    write(fd,buf,strlen(buf));
   
}

void unit_test_write_in_a_post(){
    
    int fd=open("/home/erkan/Desktop/workspace/hw1/text2.txt",O_RDWR|O_SYNC);
    if(fd<0)perror("file");
    int at=get_first_avalible_pos(fd);  
    printf("avalible pos:::%d\n",at);
  
    char str[100]="bbb";
    write_in_a_post(fd,str,strlen(str),at-1);

}