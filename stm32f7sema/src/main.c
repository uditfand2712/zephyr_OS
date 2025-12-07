#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int	main(void)
{
	while (1)
	{
		LOG_INF("Hello world from stm32f767zi !");
		k_sleep(K_SECONDS(1));
	}
	return (0);
}