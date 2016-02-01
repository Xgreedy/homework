/*
 * hw2/hello-1.c
 *
 * Weiwei Jia <wj47@njit.edu> (C) 2016
 */
#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/init.h>
//#include <linux/sched.h>

int init_module(void) {
	printk("<1> Hello World.\n");
	return 0;
}

void cleanup_module(void) {
	printk("<1> Goodbey.\n");
	return ;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weiwei Jia <wj47@njit.edu>");
MODULE_DESCRIPTION("hello world 1");
