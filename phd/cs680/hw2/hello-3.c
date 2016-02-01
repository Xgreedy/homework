/*
 * hw2/hello-3.c
 *
 * Weiwei Jia <wj47@njit.edu> (C) 2016
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/moduleparam.h>

static int number = 3;
static char *name = "Weiwei Jia";
static char *street = "Dong Da Street";
static char *city = "XiAn";
static char *zipcode = "07029";

module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(number, "Hello World number");
module_param(name, charp, 0000);
MODULE_PARM_DESC(name, "Name");
module_param(street, charp, 0000);
MODULE_PARM_DESC(street, "Street");
module_param(city, charp, 0000);
MODULE_PARM_DESC(city, "City");
module_param(zipcode, charp, 0000);
MODULE_PARM_DESC(zipcode, "Zipcode");

static int __init hello2_init(void) {
	printk("Loading Hello World %d: Hello World %d\n", number, number);
	printk("=======================================\n");
	printk("Name: %s\n", name);
	printk("Street: %s\n", street);
	printk("City: %s\n", city);
	printk("Zipcode: %s\n", zipcode);
	return 0;
}

static void __exit hello2_exit(void) {
	printk("<%d> Goodbey.\n", number);
	return ;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weiwei Jia <wj47@njit.edu>");
MODULE_DESCRIPTION("Hello World 3");
module_init(hello2_init);
module_exit(hello2_exit);
