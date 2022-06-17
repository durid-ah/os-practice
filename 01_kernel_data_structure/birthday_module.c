#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include<linux/slab.h>

struct birthday {
   int day;
   int month;
   int year;
   struct list_head list;
};

struct birthday *person;

// Call when loading module
int simple_init(void) {
   int i;
   struct birthday *ptr;

   // linked list with 5 elements
   // init first item


   person = kmalloc(sizeof(*person), GFP_KERNEL);
   person->day = 1;
   person->month = 8;
   person->year = 1995;
   INIT_LIST_HEAD(&person->list);

   for (i = 1; i < 5; i++) {
      struct birthday *new_tail;
      new_tail = kmalloc(sizeof(*new_tail), GFP_KERNEL);
      new_tail->day = i;
      new_tail->month = 8;
      new_tail->year = 1995;
      INIT_LIST_HEAD(&new_tail->list);
      
      list_add_tail(&new_tail->list, &person->list);
   }

   list_for_each_entry (ptr, &person->list, list) {
      printk(KERN_INFO "Day: %d\n", ptr->day);
   }


   printk(KERN_INFO "Loading Module\n");
   printk(KERN_INFO "Number: %d\n", 10);
   return 0;
}

// Call when module is removed
void simple_exit(void) {
   // delete the elements of the 
   struct birthday *ptr, *next;
   
   printk(KERN_INFO "Remove Module\n");

   list_for_each_entry_safe(ptr, next, &person->list, list) {
      printk(KERN_INFO "FREE: %d\n", ptr->day);
      list_del(&ptr->list);
      kfree(ptr);
   }
}

// Register Entry and Exit
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");