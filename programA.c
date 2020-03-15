#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"arg.h"
#include"file_lib.h"
#include"complex_number.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include"complex_number.h"
#include<getopt.h>



#define BUF 32

int main(int argc,char ** argv){
 
    
    char *inputPathA;
    char *outputPathA;
    int  time;

    /*checking and setting arguments*/
    int errno=argHandler(argc,argv,&inputPathA,&outputPathA,&time);    
    if(USAGE_ERROR==errno){
        printf("usage:::: ./programA -i <<inputPathA>> -o <<outputPathA>> -t <<time>>\n");
        exit(EXIT_FAILURE);
    }else if(ARG_NOT_IN_RANGE_ERROR==errno){
        printf("time has to be range in 0-50\n");    
        exit(EXIT_FAILURE);
    }else if(INVALID_PATH_ERROR==errno){
        printf("invalid path\n"); //   
        exit(EXIT_FAILURE);
    }

      struct file_lib file1;
      struct file_lib file2;
      char str[BUF];
      

      file1.fd=open(inputPathA,O_RDWR|O_SYNC,0666);
      file2.fd=open(outputPathA, O_RDWR|O_SYNC,0666);

      if(-1==file1.fd){
            perror("file cant open");
            exit(-1);
      }
      if(-1==file2.fd){
            perror("file cant open");
            exit(-1);
      }
      
    
int read_byte=BUF;
struct complex_number * arr;    
struct flock _lock;
struct flock _inputlock;


memset (&_inputlock, 0, sizeof(_inputlock));;
memset (&_lock, 0, sizeof(_lock));;
 

file1.is_lock=0;

int i=0;
lseek(file2.fd,0,SEEK_SET);
do{
            //lock
            //lock(file1.fd,&_inputlock);
            read_byte=read(file1.fd,str,BUF);
            if(read_byte!=BUF)break;                        //handle it 
            str[BUF]='\0';

            if(-1==read_byte){
                  perror("reading error!\n");
                  exit(-1);
            }
            printf(" ");
            if(BUF/2!=string_to_comlpex_number_arr(str,&arr)){
                  perror("worning !!!\n");
            }

            char * writeable_text=malloc(sizeof(char)*500);
            for (size_t i = 0; i < BUF/2; i++){
                  char temp[10];
                  getString(arr[i],temp);
                  strcat(writeable_text,temp);
                  if(BUF/2-1!=i){
                        strcat(writeable_text,",");
                  }else{
                        //strcat(writeable_text,"\n");
                  }                 
            }
                  //printf("->%s",writeable_text);
                  printf("%d ",i);
                  memset (&_lock, 0, sizeof(_lock));                                      //locking file
                  lock(file2.fd,&_lock);
            
                  int pos=get_first_avalible_pos(file2.fd);
                  write_in_a_post(file2.fd,writeable_text,strlen(writeable_text),pos-1);
                  
                  unlock(file2.fd,&_lock);
                  //unlock(file1.fd,&_inputlock);
                  //printf("curser pos:::::%d pos:::%d",lseek(file2.fd,0,SEEK_CUR),pos);
                  printf("\n");
                  free(writeable_text);
                  sleep(time);
                  
            //unlock
      
      
++i;
}while(read_byte==BUF);



if(0>close(file1.fd)){
      perror("cant close");
      exit(-1);
}
if(0>close(file2.fd)){
      perror("cant close");
      exit(-1);
}

free(inputPathA);
free(outputPathA);

    
    return EXIT_SUCCESS;
}



