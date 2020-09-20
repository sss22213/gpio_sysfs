#ifndef __sysfs__h__
#define __sysfs__h__
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct sysfs_device sysfs_device;
typedef struct sysfs_device
{
    int fd; // file description
    int fd_rw;
    int gpio;
    int gpio_count;
    char *gpio_s;
    char set_direct_path[35];
    char read_write_device[35];
    char* export_gpio;
    char* unexport_gpio;
}sysfs_device;

void delay_s(int);
void delay_ms(int);
sysfs_device *new_sysfs(int);
uint8_t set_direct_sysfs(sysfs_device*,char*);
uint8_t read_sysfs(sysfs_device*);
uint8_t write_sysfs(sysfs_device*,int);
uint8_t export_sysfs(sysfs_device*);
uint8_t unexport_sysfs(sysfs_device*);

#endif