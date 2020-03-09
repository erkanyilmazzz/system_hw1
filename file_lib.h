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

int lock(struct flock* _lock,int pid);
int unlock(struct flock * _lock, int pid);

int foo();

#endif