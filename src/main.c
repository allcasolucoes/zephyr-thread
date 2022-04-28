#include <zephyr.h>
#include<zephyr/kernel.h>
#include <drivers/gpio.h>

#define LED0 DT_ALIAS(led0)
#define LED1 DT_ALIAS(led1)
#define LED2 DT_ALIAS(led2)


#define DELAY_MS_LED0 1000
#define DELAY_MS_LED1 300
#define DELAY_MS_LED2 20


#define MY_STACK_SIZE 512
#define MY_PRIORITY 5


	static const struct gpio_dt_spec  led = GPIO_DT_SPEC_GET(LED0, gpios);
	static const struct gpio_dt_spec  led1 = GPIO_DT_SPEC_GET(LED1, gpios);
	static const struct gpio_dt_spec  led2 = GPIO_DT_SPEC_GET(LED2, gpios);



	/* struct k_thread led_tcb;
	k_thread_stack_t led_stack[1024]; */

	void led_thread0(void);
	void led_thread1(void);
	void led_thread2(void);


void main(void) {

	
} // end main

	void led_thread0(void) {
	
	int ret;

	if(!z_device_is_ready(led1.port)) {
		printk("Erro port led.port");
		return;
	}
	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	
	if(ret < 0) {
		printk("ret < 0");
		return;
	}

	while(1) {
		ret = gpio_pin_toggle_dt(&led1);
		if(ret < 0) {
			printk("ret < 0, while");
			return;
		}
		k_msleep(DELAY_MS_LED1);
	}
	}

	void led_thread1(void) {

		int ret;


	if(!z_device_is_ready(led.port)) {
		printk("Erro port led.port");
		return;
	}
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	
	if(ret < 0) {
		printk("ret < 0");
		return;
	}

	while(1) {
		ret = gpio_pin_toggle_dt(&led);
		if(ret < 0) {
			printk("ret < 0, while");
			return;
		}
		k_msleep(DELAY_MS_LED0);
	}
	}

	void led_thread2(void) {

		int ret;


	if(!z_device_is_ready(led2.port)) {
		printk("Erro port led.port");
		return;
	}
	ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	
	if(ret < 0) {
		printk("ret < 0");
		return;
	}

	while(1) {
		ret = gpio_pin_toggle_dt(&led2);
		if(ret < 0) {
			printk("ret < 0, while");
			return;
		}
		k_msleep(DELAY_MS_LED2);
	}
	}


K_THREAD_DEFINE(name_process_led1, MY_STACK_SIZE,
                led_thread0, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);

K_THREAD_DEFINE(name_process_led2, MY_STACK_SIZE,
led_thread1, NULL, NULL, NULL,
MY_PRIORITY, 0, 0);

K_THREAD_DEFINE(name_process_led3, MY_STACK_SIZE,
led_thread2, NULL, NULL, NULL,
MY_PRIORITY, 0, 0);