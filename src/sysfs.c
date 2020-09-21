#include "sysfs.h"


void delay_us(int us)
{
	usleep(us);
}

void delay_ms(int ms)
{
	usleep(ms * 1000);
}

void delay_s(int sec)
{
	sleep(sec);
}

sysfs_device* new_sysfs(int gpio)
{
    sysfs_device* new_device = (sysfs_device*)calloc(sizeof(sysfs_device),1);
    new_device->gpio = gpio;
	snprintf(new_device->set_direct_path, 35,"/sys/class/gpio/gpio%d/direction", gpio);
	snprintf(new_device->read_write_device, 35,"/sys/class/gpio/gpio%d/value", gpio);
	// gpio count of number
	int gpio_tmp = gpio;
	int n_count = 1;
	while(gpio_tmp != 0)
	{
		gpio_tmp /= 10;
		n_count++;
	}
	new_device->gpio_count = n_count;
	new_device->gpio_s = (char*)calloc(sizeof(char),n_count);
	snprintf(new_device->gpio_s, n_count, "%d", gpio);
	new_device->export_gpio = (char*)calloc(sizeof(char),24);
	memcpy(new_device->export_gpio,"/sys/class/gpio/export",24);
	new_device->unexport_gpio = (char*)calloc(sizeof(char),25);
	memcpy(new_device->unexport_gpio,"/sys/class/gpio/unexport",25);
	export_sysfs(new_device);
    return new_device;
}

uint8_t set_direct_sysfs(sysfs_device* device, char* direct)
{
	device->fd = open(device->set_direct_path, O_WRONLY);
	if(device->fd < 0)return -1;
	int result = write(device->fd,direct,3);
	close(device->fd);
	return result;
}

uint8_t read_sysfs(sysfs_device* device)
{
	device->fd = open(device->read_write_device, O_RDONLY);
	char read_result[3];
	memset(read_result,0,3);
	if(device->fd < 0)return -1;
	read(device->fd, &read_result, 1);
	close(device->fd);
	return atoi(read_result);
}

uint8_t write_sysfs(sysfs_device* device, int val)
{
	device->fd = open(device->read_write_device, O_WRONLY);
	if(device->fd < 0)return -1;
	char *hi = "1";
	char *lo = "0";
	int result;
	if(val)result = write(device->fd,hi,1);
	else result = write(device->fd,lo,1);
	close(device->fd);
	return result;
}
uint8_t export_sysfs(sysfs_device* device)
{
	ssize_t bytes_written;
	device->fd = open(device->export_gpio, O_WRONLY);
	int result = write(device->fd, device->gpio_s, device->gpio_count);
	close(device->fd);
	return result;
}

uint8_t unexport_sysfs(sysfs_device* device);