/* kernel timer */
/* timer function to be called at expiration */
static void my_timer_func(unsigned long ptr) {
	struct timer_list my_timer;
	my_timer.expires = jiffies + DELAY*secs2hello;
	printk("helloplus: timer %lu %lu\n", jiffies, my_timer.expires);
	add_timer(&my_timer);
}

/* set up the timer the first time */
struct timer_list my_timer;
init_timer(&my_timer);
my_timer.function = my_timer_func;
my_timer.data = (unsigned long)&helloplusstatus;
my_timer.expires = jiffies + DELAY*secs2hello;
add_timer(&my_timer);

/* reinstall the timer */
del_timer(&my_timer);
my_timer.function = my_timer_func;
my_timer.data = (unsigned long)&helloplustatus;
my_timer.expires = jiffies+DELAY*secs2hello;
add_timer(&my_timer);
