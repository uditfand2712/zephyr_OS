#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* Define a mutex */
K_MUTEX_DEFINE(my_mutex);

/* Define a shared resource */
int shared_counter = 0;

/* Thread stack and priority */
#define STACK_SIZE 1024
#define THREAD_PRIORITY 7

/* Thread function 1 */
void thread1_func(void *arg1, void *arg2, void *arg3)
{
    for (int i = 0; i < 5; i++) {
        /* Lock the mutex before accessing shared resource */
        k_mutex_lock(&my_mutex, K_FOREVER);
        
        printk("Thread 1: Entering critical section (iteration %d)\n", i + 1);
        
        /* Access shared resource */
        shared_counter++;
        printk("Thread 1: Counter = %d\n", shared_counter);
        
        /* Simulate some work */
        k_sleep(K_MSEC(100));
        
        /* Unlock the mutex */
        k_mutex_unlock(&my_mutex);
        
        printk("Thread 1: Leaving critical section\n\n");
        
        /* Sleep between iterations */
        k_sleep(K_MSEC(200));
    }
    
    printk("Thread 1: Done\n");
}

/* Thread function 2 */
void thread2_func(void *arg1, void *arg2, void *arg3)
{
    for (int i = 0; i < 5; i++) {
        /* Lock the mutex before accessing shared resource */
        k_mutex_lock(&my_mutex, K_FOREVER);
        
        printk("Thread 2: Entering critical section (iteration %d)\n", i + 1);
        
        /* Access shared resource */
        shared_counter += 2;
        printk("Thread 2: Counter = %d\n", shared_counter);
        
        /* Simulate some work */
        k_sleep(K_MSEC(150));
        
        /* Unlock the mutex */
        k_mutex_unlock(&my_mutex);
        
        printk("Thread 2: Leaving critical section\n\n");
        
        /* Sleep between iterations */
        k_sleep(K_MSEC(250));
    }
    
    printk("Thread 2: Done\n");
}

/* Define thread stacks */
K_THREAD_STACK_DEFINE(thread1_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACK_SIZE);

/* Thread control blocks */
struct k_thread thread1;
struct k_thread thread2;

int main(void)
{
    printk("=== Zephyr Mutex Example ===\n");
    printk("Starting mutex demonstration with 2 threads\n\n");
    
    /* Create thread 1 */
    k_thread_create(&thread1, thread1_stack, STACK_SIZE,
                    thread1_func, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);
    
    /* Create thread 2 */
    k_thread_create(&thread2, thread2_stack, STACK_SIZE,
                    thread2_func, NULL, NULL, NULL,
                    THREAD_PRIORITY, 0, K_NO_WAIT);
    
    /* Wait for both threads to complete */
    k_thread_join(&thread1, K_FOREVER);
    k_thread_join(&thread2, K_FOREVER);
    
    printk("\n=== Final Result ===\n");
    printk("Final counter value: %d\n", shared_counter);
    printk("Expected value: 15 (0 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2)\n");
    
    return 0;
}