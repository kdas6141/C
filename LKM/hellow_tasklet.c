#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL")
MODULE_AUTHOR("STUDENT")
MODULE_DESCRIPTION("Tasklet using")

char one_shot_data[] = "one shot print from tasklet schedule";
DECLARE_TASKLET(my_tasklet, my_tone_shot_tasklet_function, (unsigned long) &one_shot_data);

void my_tone_shot_tasklet_function(char *one_shot_data){
	printk(KERN_DEBUG, "%s\n", in_data);
	return;
}

int my_init_module(void) {
	/*schedule the tasklet in the bottom half */
	tasklet_schedule(&my_tasklet);
	return 0;
}

void my_exit_module(void) {
	/* kill the tasklet scheduled earlier */
	tasklet_kill(&my_tasklet);
	return;
}

module_init(my_init_module);
module_exit(my_exit_module);
