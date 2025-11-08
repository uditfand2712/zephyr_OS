#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int	main(void)
{
	while (1)
	{
		LOG_INF("Hello world from qemu context m3!");
		k_sleep(K_SECONDS(20));
	}
	return (0);
}