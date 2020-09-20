#include "sysfs.h"

int main()
{
	int gpio = 21;
	sysfs_device *new_device = new_sysfs(gpio);
	set_direct_sysfs(new_device,"out");
	while(1)
	{
		write_sysfs(new_device,1);
		delay_ms(200);
		write_sysfs(new_device,0);
		delay_ms(200);
	}
	return 0;
}
