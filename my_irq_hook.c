#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>

/*
	Test inturrupt hook
*/

/*IRQ_NUM --> cat /proc/interrupts/  , I use 56 : xhci_hcd */
#define IRQ_NUM 56

static irqreturn_t Jinyo_intr(int irq,void *dev_id)
{
	printk("irq %d dev_id %p (%s)\n",irq,dev_id,__func__);
	return IRQ_NONE;
}

static void Jinyo_init(void)
{
	printk("@Jinyo driver loaded \n");
	if(request_irq(IRQ_NUM,Jinyo_intr,
				IRQF_SHARED,
				"Jinyo_intr",
				(void*)Jinyo_intr)){
	}

	return 0;
}

static void Jinyo_exit(void)
{
	free_irq(IRQ_NUM,(void*)Jinyo_intr);
	printk(KERN_ALERT "@Jinyo driver unloaded\n");
}

module_init(Jinyo_init);
module_exit(Jinyo_exit);
MODULE_LICENSE("Dual BSD/GPL");
