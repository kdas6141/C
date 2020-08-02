#include <linux/interrupt.h>

static int dev_open(struct net_device *dev) {
	int retval;
	struct dev_private *tp = dev->priv;

	/* get the IRQ. second arg is interrupt handler, third is flag,
	0 means no IRQ sharing */
	retval = request_irq(dev->irq, dev_interrupt, 0, dev->name, dev);
	if (retval)
		return retval;

	tp->tx_bufs = pci_alloc_consistent(tp->pci_dev, TOTAL_TX_BUF_SIZE, 
		&tp->tx_bufs_dma);
	if(!tp->tx_bufs){
		free_irq(dev->irq, dev);
		return -ENOMEM;
	}
	tp->tx_flag = 0;
	return 0
}

static void dev_interrupt(int irq, void *dev_instance, struct pt_regs *regs) {
	struct net_device *dev =(struct net_device *)dev_instance;
	struct drv_private *tp = dev->priv;
	void *ioaddr = tp->mmio_addr;
	wake_up_interruptable(&waitq);
	return IRQ_HANDLED;  
}

void __init dev_init() {
	open_softirq(dev_soft_irq, checksum_packet, NULL);
}

void checksum_packet() {
	/* process the packet */
}

static irqreturn_t dev_interrupt(int irq, void *dev_id){
	/* process interrupt */
	/* mark softirq is pending */
	raise_softirq(dev_soft_irq);
	return IRQ_HANDLED;
}


/* soft IRQ */
void my_drv_func() {
	
}

void __init drv_init(){
	open_softirq(MYDEVICE_SOFT_IRQ, my_drv_func, arg);
}

/* interrupt handler */
static irqreturn_t my_drv_interrupt(int irq, void *dev_id){
	/* mark soft irq as pending */
	raise_softirq(MYDEVICE_SOFT_IRQ);
}

/*Tasklet*/
struct my_device_struct {
	struct tasklet_struct tasklet;
}

void __init drv_init(){
	struct my_device_struct *dev;
	tasklet_init(&dev_struct->tasklet, myfunc, dev);
}

static irqreturn_t my_drv_interrupt(int irq, void *dev_id){
	tasklet_schedule(&dev_struct->tasklet);
	return IRQ_HANDLED;
}

void __init dev_init(){
	tasklet_init(&dev_struct->tsklt, checksum_packet, dev);
}

static irqreturn_t dev_interrupt(int irq, void *dev_id) {
	tasklet_schedule(&dev_struct->tsklt);
}