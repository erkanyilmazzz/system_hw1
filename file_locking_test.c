#include<stdio.h>
#include"file_lib.h"
#include<stdlib.h>
#include<string.h>
#include"arg.h"
#include"file_lib.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include"complex_number.h"



int main(){
    int fd=open("/home/erkan/Desktop/workspace/hw1/text2.txt",0666);
    if(fd<0){
        perror("hata");
        exit(-1);
    }
    if(0>write(fd,"erkan",5))perror("asd");

    struct flock _lock;
    memset (&_lock, 0, sizeof(_lock));;
    lock(fd,&_lock);
    char i;
    printf("please enter a char ");
    scanf("%c",&i);
    unlock(fd,&_lock);


    return 0;
}