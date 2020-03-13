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

#endif