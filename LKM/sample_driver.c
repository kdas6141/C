#include <linux/init.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/in.h>
#include <linux/errqueue.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL")
MODULE_AUTHOR("STUDENT")
MODULE_DESCRIPTION("Printing process info")

struct file_opeartions mydrv_fops = {
	owner: THIS_MODULE,
	open: my_open,
	release: my_release,
	read: my_read,
	write: my_write,
	llseek: my_lseek,
	ioctl: my_ioctl,
};

struct foo_module { void *buf;/* .... */};

static int my_open(struct inode *inode, struct file *file) {
	struct foo_module *f;
	f = kmalloc(sizeof(struct foo_module), GFP_KERNEL);
	if (!f)
		return -ENOMEM;
	f->buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!f->buf) {
		kfree(f);
		return -ENOMEM;
	}
	memset(f->buf, 0, PAGE_SIZE);
	file->private_data = f;
	return 0;
}

static int my_release(struct inode *inode, struct file *file){
	struct foo_module *f;

	f = file->private_data;
	kfree(f->buf);
	kfree(f);
	return 0;
}

static int my_read(struct file *file, char *data, size_t size, loff_t *off){
	struct foo_module *f;

	f = file->private_data;

	if (size > PAGE_SIZE)
		size = PAGE_SIZE;

	if (copy_to_user(f->buf, data, size))
		return -EFAULT;

	return size;
}

#define MAGIC 'z'

#define GETIOCTL _IOR(MAGIC, 1, int *)

#define SETIOCTL _IOW(MAGIC, 2, int *)

static unsigned char secs2hello;
static int my_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg) {
	int ret;
	switch(cmd) {
		case GETIOCTL:
			printk("helloplus: ioctl: GETIOCTL\n");
			ret = copy_to_user((char *)arg, (char *)&secs2hello, 1);
			printk("Get:Seconds to hello %d %d\n", secs2hello, ret);
			break;
		case SETIOCTL:
			printk("helloplus: ioctl: SETIOCTL\n");
			ret = copy_from_user((char *)&secs2hello, (char *)arg, 1);
			printk("Get:Seconds to hello %d %d\n", secs2hello, ret);
			break;					
	}
	return 0;
}

int my_init_func(void) {
	printk("\n\n Hello World, Module Loaded !\n\n\n");
	struct task_struct *cur_task;
	cur_task = get_current();
	printk(KERN_ALERT, "\n\n Starting with process: %s[%d] \n\n", cur_task->comm, cur_task->pid);
	for_each_process(cur_task) {
		printk(KERN_ALERT, " %15s[%d] --- child of --- %15s[%d]", cur_task->comm, cur_task->pid, cur_task->real_parent->pid);
	}
	return 0;
}

void my_exit_func(void) {
	printk("\n\n Bye, Bye, Nodule Unloaded \n\n");
}

module_init(my_init_func);
module_exit(my_exit_func);






