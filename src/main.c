#include "sysfs.h"

int main()
{
	int gpio = 21;
	sysfs_device *new_device = new_sysfs(gpio);
	set_direct_sysfs(new_device,"out");
	while(1)
	{
		write_sysfs(new_device,1);
		delay_s(1);
		write_sysfs(new_device,0);
		delay_s(1);
	}
	return 0;
}