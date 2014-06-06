#include <linux/module.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

int irq_number;

static irqreturn_t gpio_reset_interrupt(int irq, void *dev_id)
{
	printk(KERN_ERR "module-1: IRQ %d event.\n",irq_number);
	return(IRQ_HANDLED);
}

static int __init mymodule_init(void)
{
	irq_number = gpio_to_irq(25);

	if (request_irq(irq_number, gpio_reset_interrupt, IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "gpio_reset", NULL))
	{
		printk(KERN_ERR "module-1: error requesting IRQ %d.\n", irq_number);
		return(-EIO);
	}
	else
	{
		printk(KERN_ERR "module-1: success requesting IRQ %d.\n", irq_number);
	}

	return 0;
}

static void __exit mymodule_exit(void)
{
	free_irq(irq_number, NULL);
	printk("module-1: module unloaded.\n");
	return;
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
