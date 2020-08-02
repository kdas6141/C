/* spin lock */
/* function */
static increment_i(void) {
	unsigned long flags;
	spin_lock_irqsave(&i_lock, flags);
	i++;
	spin_lock_irqstore(&i_lock, flags);
}

/*IRQ handler*/
static irqreturn_t irq_handler() {
	increment_i();
}

/*Process context */
static void myfunc(void){
	increment_i();
}

int main() {

	struct semaphore my_sem;
	sema_init(&my_sem, 1);
	if (down_interruptible(&my_sem))
		exit(0);
	/* critical region */
	up(&my_sem);
}