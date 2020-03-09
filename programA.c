#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"arg.h"
#include"file_lib.h"


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


    foo();
    printf("s1:%s s2:%s time :%d\n",inputPathA,outputPathA,time);
    
    
    return EXIT_SUCCESS;
}



