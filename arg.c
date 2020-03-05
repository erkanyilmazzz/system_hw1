#include"arg.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int argHandler(int __argc,char ** __argv,char ** _inputPath, char ** _outputPath,int * _time){
    
    int time;
    int inputPathLen=0,outputPathLen=0;

    if(__argc!=7){
        return USAGE_ERROR;
    }

    int i;
    int where_is_i=-1,where_is_o=-1,where_is_t=-1;
    for ( i = 0; i < __argc; i++){
        if(0==strcmp(__argv[i],"-i"))
            where_is_i=i;
        if(0==strcmp(__argv[i],"-o"))
            where_is_o=i;
        if(0==strcmp(__argv[i],"-t"))
            where_is_t=i;        
    }
    //printf("%d %d %d",where_is_i,where_is_o,where_is_t);
    //printf("s1:%s s2:%s cmpdeneme: %d\n",__argv[1],"-i",strcmp(__argv[1],"-i"));
    
    if(where_is_i<0|where_is_o<0|where_is_t<0
        |where_is_t>__argc-1|where_is_o>__argc-1|where_is_i>__argc-1
        |abs(where_is_i-where_is_o)<=1|abs(where_is_i-where_is_t)<=1|abs(where_is_o-where_is_t)<=1){
        return USAGE_ERROR;
    }
    
    time=atoi(__argv[where_is_t+1]);
    if(time<0|time>50){
        return ARG_NOT_IN_RANGE_ERROR;
    }
    
    if(!((*_inputPath)=malloc(sizeof(char)*inputPathLen))){
        printf("malloc errror!\n");
        exit(EXIT_FAILURE);
    }   
        
    if(!((*_outputPath)=malloc(sizeof(char)*outputPathLen))){
        printf("malloc errror!\n");
        exit(EXIT_FAILURE);
    }

    strcpy((*_inputPath),__argv[where_is_i+1]);
    strcpy((*_outputPath),__argv[where_is_o+1]);
    *_time=time;
    //./programA -i path1 -o path2 -t 12
    // 0         1   2     3   4    5 6

}