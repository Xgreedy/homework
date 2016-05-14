/*
 * hw2/hw10.c
 *
 * Weiwei Jia <wj47@njit.edu> (C) 2016
 */
#include <linux/module.h>
#include <linux/cpu.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
//#include "linux/include/net/sch_generic.h"

#define NR_PKTCNTR	(3)

static char *pktcntr_to_name[NR_PKTCNTR] = {"Incoming packets number",
	"Outgoing packets number", "Process packets number"};

DEFINE_PER_CPU(struct softnet_data, softnet_data);
//DEFINE_PER_CPU(struct netif_rx_stats, netdev_rx_stat) = { 0, };

static int skb_qlen(struct sk_buff_head *list) {
	int __qlen = 0;
	struct sk_buff *next = list->next;
	if (next = (struct sk_buff *) list) goto out;
	while (next != (struct sk_buff *) list) {
		__qlen++;
		next = next->next;
	}
out:
	return __qlen;
}

/*
 * /proc/pkt_cntr  ... display the network package infos
 */
static int show_pktcntr(struct seq_file *p, void *v) {
	int i, j;
	struct softnet_data *sd;
#if 1
	seq_puts(p, "                            ");
	for_each_possible_cpu(i)
		seq_printf(p, "CPU%-8d", i);
	seq_putc(p, '\n');

	for (i = 0; i < NR_PKTCNTR; i++) {
		seq_printf(p, "%12s:", pktcntr_to_name[i]);
		for_each_possible_cpu(j) {
			sd = &per_cpu(softnet_data, j);
			printk(KERN_DEBUG "Addr of softnet_data on cpu %d is %p\n", j, sd);
			printk(KERN_DEBUG "Processed number is %d\n", sd->processed);
			printk(KERN_DEBUG "Process backlog weight is %d, gro_count is %d\n", sd->backlog.weight, sd->backlog.gro_count);
			printk(KERN_DEBUG "Addr of process_backlog on cpu %d is %p\n", j, sd->backlog.poll);
			if (i == 0) {
				//seq_printf(p, " %10u", sd->input_pkt_queue.qlen);
				seq_printf(p, " %10u", skb_qlen(&sd->input_pkt_queue));
				printk(KERN_DEBUG "Addr of output queue on cpu %d is %p\n", j, sd->output_queue);
			} else if (i == 1 && sd->output_queue) {
				//seq_printf(p, " %10u", sd->output_queue->q.qlen);
			} else if (i == 2) {
				seq_printf(p, " %10u", skb_qlen(&sd->process_queue));
			}
		}
		seq_putc(p, '\n');
	}
#endif
	return 0;
}

static int pktcntr_open(struct inode *inode, struct file *file) {
	return single_open(file, show_pktcntr, NULL);
}

static const struct file_operations proc_pktcntr_operations = {
		.open = pktcntr_open,
		.read = seq_read,
		.llseek	= seq_lseek,
		.release = single_release,
};

static int __init hw10_init(void) {
	printk(KERN_INFO "Enter CS680 homework #10...\n");
	proc_create("pkt_cntr", 0, NULL, &proc_pktcntr_operations);
	return 0;
}

static void __exit hw10_exit(void) {
	remove_proc_entry("pkt_cntr", NULL);
	printk(KERN_INFO "Exit CS680 homework #10...\n");
	return ;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weiwei Jia <wj47@njit.edu>");
MODULE_DESCRIPTION("CS680 Homework #10");
module_init(hw10_init);
module_exit(hw10_exit);
