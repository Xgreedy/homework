#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/desc.h>
 
#define DIVIDE_ERROR 0x00
 
/* global varaible */
char msg[200];
char *str = "test";
struct desc_ptr newidtr, oldidtr,tempidtr;
gate_desc *newidt, *oldidt, *tempidt;
int counter = 0;
unsigned long old_stub = 0xffffffff81016100;
 
/* global function */
extern asmlinkage void new_stub(void);
 
/* active idt_table by loading new idt pointer to the register */
static void load_IDTR(void *addr)
{
    asm volatile("lidt %0"::"m"(*(unsigned short *)addr));
}

/* my C handler */
void my_func(void)
{
    /* add the counter and send messge to console */
    printk("............999 dbg, Counter = %d\n", ++counter);
}
 
/* my Assembly handler */
void my_dummy(void)
{
        __asm__ (
	    ".globl new_stub\n\t"
        ".align 4, 0x90\n\t"
        "new_stub:\n\t"
#if 0
        "pushfq\n\t"
        "pushq %%rax\n\t"
        "pushq %%rbx\n\t"
        "pushq %%rcx\n\t"
        "pushq %%rdx\n\t"
        "pushq %%rbp\n\t"
        "pushq %%rsp\n\t"
        "pushq %%rdi\n\t"
        "pushq %%rsi\n\t"
#endif
        "call my_func\n\t"
#if 0
        "popq %%rsi\n\t"
        "popq %%rdi\n\t"
        "popq %%rsp\n\t"
        "popq %%rbp\n\t"
        "popq %%rdx\n\t"
        "popq %%rcx\n\t"
        "popq %%rbx\n\t"
        "popq %%rax\n\t"
        "popfq\n\t"
#endif
        "jmp old_stub\n\t"
         ::);
}
  
int __init hook_init(void){
 
    /* message */
	printk("1----------------------------------------\n");
 
    /* initialize tty for console print */
 //   my_tty = current->signal->tty;
 
    /* create new idt_table copied from old one */
    store_idt(&oldidtr);
	printk("a 999dbg -- old idtr is %p\n", &oldidtr);
	printk("999dbg -- old idtr address is %p\n", (void *) oldidtr.address);
    oldidt = (gate_desc *)oldidtr.address;
	printk("999dbg -- old idt is %p\n", oldidt);
    newidtr.address = __get_free_page(GFP_KERNEL);
    //newidtr.address = (int) kmalloc(oldidtr.size, GFP_KERNEL);
	printk("b 999dbg -- newidtr.address is %p\n", (void *) newidtr.address);
    if(!newidtr.address)
        return -1;
    newidtr.size = oldidtr.size;
	printk("999dbg -- size is %d\n", newidtr.size);
    newidt = (gate_desc *)newidtr.address;
	printk("c 999dbg -- new idt is %p\n", newidt);
    memcpy(newidt, oldidt, oldidtr.size);
	printk("2----------------------------------------\n");
 
    /* modify the divide_error entry to point to my assembly handler */
    pack_gate(&newidt[DIVIDE_ERROR], GATE_INTERRUPT, (unsigned long)new_stub, 0, 0, __KERNEL_CS);
	printk("3----------------------------------------\n");
 
    /* active the new idt_table */
    load_IDTR((void *)&newidtr);
	printk("4----------------------------------------\n");
 
    /* for smp architecture */
     //smp_call_function(load_IDTR,(void *)&newidtr, 0);
 
    return 0; 
} 
void __exit hook_exit(void){
 
    /* message */
//    write_console("Jianchen recovered interrupt_0 \r\n");
//    sprintf(msg, "Interrupt_0 handled during hijacking = %d \r\n", counter);
//    write_console(msg);
     
    /* active old idt_table */
    load_IDTR(&oldidtr);
 
    /* for smp architecture */
     //smp_call_function(load_IDTR, (void *)&oldidtr, 0);
 
    /* free the allocated page for new idt_table */
    if(newidtr.address)
        free_page(newidtr.address); 
	printk("Over......----------------------------------------\n");
}
  
module_init(hook_init);
module_exit(hook_exit);
MODULE_LICENSE("GPL");
