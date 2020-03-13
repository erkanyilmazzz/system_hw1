#include"complex_number.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void print_complex_num(struct complex_number c_num){
    printf("%d i + %d",c_num.imaginary,c_num.real);
}


int  string_to_comlpex_number_arr(char * str,struct complex_number ** arr){
    int size_of_string=strlen(str);
    if(0!=size_of_string%2){
        perror("sizeof string has to be even number \n");
    }
    int size_of_complex_number_arr=size_of_string/2;
    (*arr)=malloc(sizeof(struct complex_number)*size_of_complex_number_arr);

    for (size_t i = 0; i < size_of_complex_number_arr; i++)
    {
        (*arr)[i].imaginary=str[2*i];
        (*arr)[i].real=str[2*i+1];
    }
    /*
    (*arr)[0].imaginary=str[0];
    (*arr)[0].real=str[1];
    (*arr)[1].imaginary=str[2];
    (*arr)[1].real=str[3];
    (*arr)[2].imaginary=str[4];
    (*arr)[2].real=str[5];
    (*arr)[3].imaginary=str[6];
    (*arr)[3].real=str[7];

    */
    
    return size_of_complex_number_arr;
}
char * getString(struct complex_number num,char * snum){
    //char * snum=malloc(sizeof(char)*10);
    
    sprintf(snum, "%d+i%d", num.imaginary,num.real);
      
}

void unit_test_getString(){
    struct complex_number num;
    char * snum;
    num.imaginary=5;
    num.real=6;
   // printf("%s",getString(num));
}
void unit_test_string_to_complex_number(){
    char * str="a1b2c3d4e5f6g7x812345678";
    struct complex_number * arr;
    int sizeofcomplex_number_arr=string_to_comlpex_number_arr(str,&arr);
    for (size_t i = 0; i < sizeofcomplex_number_arr; i++){
        print_complex_num(arr[i]);printf("\n");
    }
    
}

