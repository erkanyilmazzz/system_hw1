#include<stdio.h>
#include<stdlib.h>
#include"arg.h"
#include"file_lib.h"
#include<unistd.h>
#include"complex_number.h"
#include<string.h>
#include<time.h>
#include"file_lib.h"
#include<sys/stat.h>
#include<sys/types.h>

#define BUF 32




int main(int argc,char ** argv ){


    
    char *inputPathB;
    char *outputPathB;
    int  time;

    /*checking and setting arguments*/
    int errno=argHandler(argc,argv,&inputPathB,&outputPathB,&time);    
    if(USAGE_ERROR==errno){
        printf("usage:::: ./programB -i <<inputPathB>> -o <<outputPathB>> -t <<time>>\n");
        exit(EXIT_FAILURE);
    }else if(ARG_NOT_IN_RANGE_ERROR==errno){
        printf("time has to be range in 0-50\n");    
        exit(EXIT_FAILURE);
    }else if(INVALID_PATH_ERROR==errno){
        printf("invalid path\n"); //   
        exit(EXIT_FAILURE);
    }

    printf("i::::%s\no::::::%s\nt:::::%d\n",inputPathB,outputPathB,time);

    struct file_lib inputFile;
    struct file_lib outputFile;
    inputFile.fd=open(inputPathB,O_RDWR|O_SYNC,0666);
    outputFile.fd=open(outputPathB,O_RDWR|O_SYNC,066);
    if(inputFile.fd<0|outputFile.fd<0){
        perror("can not open file ");
        exit(-1);
    }


    struct complex_number *arr;
    struct flock _inputFileLock;
    memset(&_inputFileLock,0,sizeof(struct flock));

    int size=0;
    int start=0;
    char *line;
    char * clear_line;
    int i =0;
    
    do{
        lock(inputFile.fd,&_inputFileLock);//burda sıkıntı var
            if(!file_is_empty(inputFile.fd)){
                start =get_random_line_start(inputFile.fd);
                size =sizeof_line(inputFile.fd,start);
                if(size!=-1){
                    line = deletenchar(inputFile.fd,start,size);
                    //printf("\ncline %s\n",line);
                    //clear_line=clearString(line,size);
                    arr=get_complex_number_arr(line,size);
                    //free(clear_line);
                    int result=fft(arr,16);
                    //lock output file
                        char * res=malloc(sizeof(char)*2);
                        sprintf(res,"%d\n",result);
                        write(outputFile.fd,res,strlen(res));
                        free(res);
                    //unlock output file
                }else{
                    //printf("somting happen\n");
                }
                                            
            }else{
                printf("file is empty");
                sleep(time);
                
            }

        unlock(inputFile.fd,&_inputFileLock);
        //printf("size %d ,start %d \n",size,start);
        ++i;
        sleep(time );
    }while(!file_is_empty(inputFile.fd));

    printf("%d line işlendi",i);
    
    if(0>close(inputFile.fd)){
        perror("canr close");
        exit(-1);
    }
    if(0>close(outputFile.fd)){
        perror("canr close");
        exit(-1);
    }


    free(arr);
    return EXIT_SUCCESS;
}