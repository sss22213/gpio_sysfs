#include "sysfs.h"

int main()
{
	int gpio = 200;
	sysfs_device *new_device = new_sysfs(gpio);
	set_direct_sysfs(new_device,"in");
	while(1)
	{
		set_direct_sysfs(new_device,"out");
		write_sysfs(new_device,1);
		delay_ms(200);
		set_direct_sysfs(new_device,"in");
		printf("%d\n",read_sysfs(new_device));
		delay_ms(200);
		set_direct_sysfs(new_device,"out");
		write_sysfs(new_device,0);
		set_direct_sysfs(new_device,"in");
		printf("%d\n",read_sysfs(new_device));
		delay_ms(200);
	}
	
	return 0;
}
