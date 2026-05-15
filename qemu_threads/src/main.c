#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#define THREAD_PRIORITY 7
#define STACK_SIZE 1024
void thread1_func(void *arg1, void *arg2, void *arg3);
void thread2_func(void *arg1, void *arg2, void *arg3);
/* Thread control blocks */
struct k_thread thread1;
struct k_thread thread2;
K_THREAD_STACK_DEFINE(thread1_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACK_SIZE);
int main(void)
{
    printk("Hello from QEMU Threads example!\n");
    k_thread_create(&thread1, thread1_stack, STACK_SIZE,
                    thread1_func, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);

    /* Create thread 2 */
    k_thread_create(&thread2, thread2_stack, STACK_SIZE,
                    thread2_func, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);

    /* Create threads here if needed */

    return 0;
}

void thread1_func(void *arg1, void *arg2, void *arg3)
{
    while (1)
    {
        printk("Thread 1: Running\n");
        k_sleep(K_MSEC(500)); // Sleep for 500 milliseconds
    }
}
void thread2_func(void *arg1, void *arg2, void *arg3)
{
    while (1)
    {
        printk("Thread 2: Running\n");
        k_sleep(K_MSEC(500)); // Sleep for 500 milliseconds
    }
}
