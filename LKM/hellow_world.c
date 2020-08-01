#include <linux/init.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/in.h>
#include <linux/errqueue.h>

MODULE_LICENSE("GPL")
MODULE_AUTHOR("STUDENT")
MODULE_DESCRIPTION("Printing process info")

int sysint_init(void) {
	printk("\n\n Hello World, Module Loaded !\n\n\n");
	struct task_struct *cur_task;
	cur_task = get_current();
	printk(KERN_ALERT, "\n\n Starting with process: %s[%d] \n\n", cur_task->comm, cur_task->pid);
	for_each_process(cur_task) {
		printk(KERN_ALERT, " %15s[%d] --- child of --- %15s[%d]", cur_task->comm, cur_task->pid, cur_task->real_parent->pid);
	}
	return 0;
}

void sysinit_exit(void) {
	printk("\n\n Bye, Bye, Nodule Unloaded \n\n");
}

module_init(sysint_init);
module_exit(sysint_exit);





