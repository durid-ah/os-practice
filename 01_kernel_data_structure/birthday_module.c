#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct birthday {
   int day;
   int month;
   int year;
   struct list_head list;
};

// Call when loading module
int simple_init(void) {
   printk(KERN_INFO "Loading Module\n");
   printk(KERN_INFO "Number: %d\n", 10);
   return 0;
}

// Call when module is removed
void simple_exit(void) {
   printk(KERN_INFO "Remove Module\n");
}

// Register Entry and Exit
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");