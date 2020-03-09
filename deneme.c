#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"arg.h"
#include"file_lib.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include"complex_number.h"


#define BUF 8


int main(){
    struct file_lib file1;
    char str[BUF];

    file1.file_path="/home/erkan/Desktop/workspace/hw1/text.txt";
    file1.fd=open(file1.file_path,O_RDONLY|O_SYNC,0666);
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
            printf("%s\n",str);
            if(BUF/2!=string_to_comlpex_number_arr(str,&arr)){
                  perror("worning !!!\n");
            }
            for (size_t i = 0; i < BUF/2; i++)
            {
                  print_complex_num(arr[i]);printf("\n");
            }
            

            printf("\n");
            //unlock
      }else{
            //wait
      }

}while(read_byte==BUF);
    

return 0;
}