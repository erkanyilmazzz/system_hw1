#include"complex_number.h"
#include<stdio.h>

void print_complex_num(struct complex_number c_num){
    printf("%di+%d",c_num.imaginary,c_num.real);
}