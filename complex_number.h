#ifndef COMPLEX_NUMBER
#define COMPLEX_NUMBER

struct complex_number
{
    int imaginary;
    int real;
};

void print_complex_num(struct complex_number);


/**
 * This function get a string and covert it a complex number arr 
 * return value is size of complex number arr
 * assumtions : size of string has to be even number 
*/
int  string_to_comlpex_number_arr(char * str,struct complex_number ** arr);

void unit_test_string_to_complex_number();


char * getString(struct complex_number,char *sum);


void unit_test_getString();

#endif