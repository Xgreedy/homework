/*
 * hw2/hello-2.c
 *
 * Weiwei Jia <wj47@njit.edu> (C) 2016
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static int hello2_data __initdata = 2;

static int __init hello2_init(void) {
	printk("<%d> Hello World.\n", hello2_data);
	return 0;
}

static void __exit hello2_exit(void) {
	printk("<%d> Goodbey.\n", hello2_data);
	return ;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weiwei Jia <wj47@njit.edu>");
MODULE_DESCRIPTION("Hello World 2");
module_init(hello2_init);
module_exit(hello2_exit);
