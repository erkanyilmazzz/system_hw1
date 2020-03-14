#ifndef FILE__
#define FILE__
#include<fcntl.h>

struct file_lib
{
    struct flock lock;
    char * file_path;
    int fd;
    int index;
    int is_lock;
};

int lock(int fd,struct flock* _lock);
int unlock(int fd,struct flock * _lock);

/**has to be in readonly mode*/
int get_first_avalible_pos(int fd);
void unit_test_get_first_avalible_pos();

int write_in_a_post(int fd,void * buf,int size,int pos);

void unit_test_write_in_a_post();
int foo();



int get_how_many_new_line(int fd);
void unit_test_get_how_many_new_line();

/*file has to end with newline */
int get_random_line_start(int fd);

void unit_test_get_random_line_start();


int sizeof_line(int fd,int starting_pos);
void unit_test_sizeof_line();
#endif