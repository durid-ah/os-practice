#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// Call when loading module
int simple_init(void) {
   printk(KERN_INFO "Loading Module\n");
   return 0;
}

// Call when module is removed
void simple_exit(void) {
   printk(KERN_INFO "Loading Module\n");
}

// Register Entry and Exit
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");