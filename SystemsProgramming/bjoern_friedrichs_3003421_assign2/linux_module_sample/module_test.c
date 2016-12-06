
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/interrupt.h>
#include <asm/io.h>

#include <linux/time.h>

#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("B. Friedrichs");

static irqreturn_t my_interrupt(int irq, void *dev_id, struct pt_regs *regs) {
  // get scancode
  unsigned char scancode;
  scancode = inb(0x60);

  // print scancode to log
  printk(KERN_INFO "XXX: Scancode %d.\n", scancode);
  return IRQ_HANDLED;
}

static int __init sampleModuleInit(void){
  printk(KERN_INFO "XXX: sample module initialized.\n");

  //request irq with my_interrupt handler and shared flag on interrupt lane 1 for keyboard
  if(request_irq(1, (irq_handler_t) my_interrupt, IRQF_SHARED, "sample_module", (void *) my_interrupt)) {
      printk(KERN_INFO "XXX: 1 can't get assigned.\n");
  }

  return 0; /* no error */
}

static void __exit  sampleModuleExit(void){
  printk(KERN_INFO "XXX: sample module exit.\n");
  // free lane 1 from my interrupt
  free_irq(1, (void *) my_interrupt);
}

module_init(sampleModuleInit);
module_exit(sampleModuleExit);
