#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"arg.h"
#include"file_lib.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include"complex_number.h"


#define BUF 16


int main(){

      //unit_test_get_first_avalible_pos();
      unit_test_write_in_a_post();
 
}
 /*
      //unit_test_write_in_a_post();
      struct file_lib file1;
      struct file_lib file2;
      char str[BUF];

      file1.file_path="/home/erkan/Desktop/workspace/hw1/text.txt";
      //file1.fd=open(file1.file_path,O_RDONLY|O_SYNC,0666);
      file1.fd=open(file1.file_path,O_RDWR|O_SYNC,0666);
      file2.file_path="/home/erkan/Desktop/workspace/hw1/text2.txt";
      file2.fd=open(file2.file_path, O_RDWR|O_SYNC,0666);

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
file1.is_lock=0;

lseek(file2.fd,0,SEEK_SET);
do{
      if(!file1.is_lock){
            //lock
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

            char * writeable_text=malloc(sizeof(char)*100);
            char * temp;
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
                  printf("->%s",writeable_text);
                  
                  int pos=get_first_avalible_pos(file2.fd);
                  write_in_a_post(file2.fd,writeable_text,strlen(writeable_text),pos);
                  
                  printf("curser pos:::::%d pos:::%d",lseek(file2.fd,0,SEEK_CUR),pos);
            printf("\n");
            free(writeable_text);
            //unlock
      }else{
            //wait
      }

}while(read_byte==BUF);
    
close(file1.fd);
close(file2.fd);

return 0;
}
*/