#include"file_lib.h"
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>


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


int get_how_many_new_line(int fd){
    lseek(fd,0,SEEK_SET);

    int read_byte=1;
    int counter=0;
    char *temp=malloc(sizeof(char));    
    do{
        read_byte=read(fd,temp,1); 
        if(read_byte<0)perror("asd");
        
        if(*temp=='\n'){
            counter++;
        }
    
    }while(read_byte!=0);

    free(temp);
return counter;
}

void unit_test_get_how_many_new_line (){
    int fd=open("/home/erkan/Desktop/workspace/hw1/output.txt",O_RDWR|O_SYNC,0666);
    if(fd<0){
        perror("hata");
        exit(-1);
    }
    printf("here are %d line \n",get_how_many_new_line(fd));

    close(fd);
}




int get_random_line_start(int fd){/*sıkıntı var*/
    
    /*I get start of file en d end of dile */
    int end_of_file=lseek(fd,0,SEEK_END);                       
    int start=lseek(fd,0,SEEK_SET);
    
    /**check lseek works or not*/
    if(end_of_file<0|start<0){
        perror("asd");
        exit(-1);
    }

    /**calculate lengt of file */
    int leng_of_file=(end_of_file-start);
    if(leng_of_file==0)return 0;                                /*if file is empty return 0*/
    
    srand(time(NULL));
    /*get random cursur pos */
    int random= rand()%leng_of_file;

    /*set random cursor pos*/
    if(0>lseek(fd,random,SEEK_SET)){
        perror("lseek error");
        exit(-1);
    }
    printf("random :%d ye set edildi\n",random);
    int pos=0;
    int read_byte=1;
    char *temp=malloc(sizeof(char));    
    int i=0;
    int flag=0;
    char * debug=malloc(sizeof(char )*300);
    do{
        /*get char in temp*/
        read_byte=read(fd,temp,1); 
        if(read_byte<0){
            perror("reading error!");
            exit(-1);
        }
        




        if(*temp=='\n'){
            pos=i+random;
            
            flag=1;
        }
        if(i==leng_of_file-random){
            /**set cursor start of file */       
            if(0>lseek(fd,0,SEEK_SET)){
                perror("lseek error");
                exit(-1);
            }
            i=0;
        }
    ++i;
   // printf("temp::::::::::::::::%c\n",*temp);
    if(flag==0){
        strcat(debug,temp);
    }
    if(flag==1)break;
    }while(read_byte!=0);

    free(temp);

    printf("%s\n",debug);
    return pos;
}



void unit_test_get_random_line_start(){
    int fd=open("/home/erkan/Desktop/workspace/hw1/output.txt",O_RDWR|O_SYNC,0666);
    if(fd<0){
        perror("hata");
        exit(-1);
    }
    int size=0;
    int pos=get_random_line_start(fd);
    printf("random line start at %d ",pos);

    close(fd);

}

int sizeof_line(int fd,int starting_pos){
    int endoffile=lseek(fd,0,SEEK_END);
    int start=lseek(fd,0,SEEK_SET);
    int leng_of_file=endoffile-start;
    if(0>lseek(fd,starting_pos+1,SEEK_SET)){
        perror("asd");
        exit(-1);
    }
    int read_byte=1;
    char *temp=malloc(sizeof(char));
    char *temp2=malloc(sizeof(char));
    int counter=0;
    int i=0;

    do{
        read_byte=read(fd,temp,1);
        if(read_byte<0){
            perror("reading error\n");
            exit(-1);
        }
        if(1==is_char(*temp2) && *temp=='\n'){
            //printf("girdi");
            free(temp);
            free(temp2);
           return counter;
        }
         counter ++;
         ++i;
         printf("%d ",counter);
         printf("önceki ---%c--- sonraki ---%c---\n",*temp2,*temp);
        

        strcpy(temp2,temp);    

        if(i==leng_of_file){/*if file end */
            printf("girdiaaaaaaaaaaaaaaaaaaaa");
            
            /*set cursor start of file */     
            if(0>lseek(fd,0,SEEK_SET)){
                perror("asd");
                exit(-1);
            }
            int read_byte;
            int size=0;
            do{
                read_byte=read(fd,temp,1);
                size++;
                if(1==is_char(*temp2) && *temp=='\n'){
                   break;
                }

                *temp2=*temp;
            }while(1);
            deletenchar(fd,-1,size);
            free(temp);
            free(temp2);
            return size;
        }
    }while(i<leng_of_file);
        
    if(0>lseek(fd,0,SEEK_SET)){
        perror("asd");
        exit(-1);
    }

}

void unit_test_sizeof_line(){
    int fd=open("/home/erkan/Desktop/workspace/hw1/output.txt",O_RDWR|O_SYNC,0666);
    if(fd<0){
        perror("hata");
        exit(-1);
    }
    int start =get_random_line_start(fd);
    int size=sizeof_line(fd,start);
    printf("start :::%d  size::::%d\n ",start,size);

    close(fd);
}


int deletenchar(int fd,int pos,int size){
    lseek(fd,pos+1,SEEK_SET);
    char * temp=malloc(sizeof(char)*size);
    for (size_t i = 0; i < size-1; i++)
    {
        temp[i]=' ';
    }
    temp[size-1]='\n';
    write(fd,temp,size);

    


}

void unit_test_deletenchar(){
    int fd=open("/home/erkan/Desktop/workspace/hw1/output.txt",O_RDWR|O_SYNC,0666);
    if(fd<0){
        perror("hata");
        exit(-1);
    }
    int start =get_random_line_start(fd);
    int size=sizeof_line(fd,start);
    printf("start :::%d  size::::%d\n ",start,size);
    deletenchar(fd,start,size);
    

    close(fd);
}

int is_char(char c){
    if(!(c==' ' | c=='\n'|c=='\0'))return 1;
    else return 0;
}
