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

      struct file_lib file1;
      struct file_lib file2;
      char str[BUF];

      file1.file_path="/home/erkan/Desktop/workspace/hw1/text.txt";
      file1.fd=open(file1.file_path,O_RDONLY|O_SYNC,0666);
      file2.file_path="/home/erkan/Desktop/workspace/hw1/text2.txt";
      file2.fd=open(file2.file_path,O_WRONLY|O_SYNC|O_RDONLY,0666);

    if(-1==file1.fd){
        perror("file cant open");
        exit(-1);
    }

    
int read_byte=BUF;
struct complex_number * arr;    
    file1.is_lock=0;
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
            //printf("%s\n",str);
            //printf("\n");
            printf(" ");
            if(BUF/2!=string_to_comlpex_number_arr(str,&arr)){
                  perror("worning !!!\n");
            }

            char * writeable_text=malloc(sizeof(char)*50);
            char * temp;
            for (size_t i = 0; i < BUF/2; i++)
            {
                  //print_complex_num(arr[i]);printf("\n");
                  //char * temp=malloc(sizeof(char )*10);
                  char temp[10];
                  getString(arr[i],temp);
                  strcat(writeable_text,temp);
                  if(BUF/2-1!=i){
                        strcat(writeable_text,",");
                  }else{
                        strcat(writeable_text,"\n");
                  }                 
                  //free(temp);
            }
                  printf("->%s",writeable_text);
                  write(file2.fd,writeable_text,strlen(writeable_text));
            
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