#include<linux/module.h>

int var=10;

void function(void)
{
   printk(KERN_INFO"%s my_function() called\n",THIS_MODULE->name);
   printk(KERN_INFO"%s my_function() var=%d\n",THIS_MODULE->name,var);
}

static __init int export_init(void)
{
   printk(KERN_INFO"%s export init():\n",THIS_MODULE->name);
   function();
   printk(KERN_INFO"%s eport init() complete\n",THIS_MODULE->name);
   return 0;
}

static __exit void export_exit(void)
{
   printk(KERN_INFO"%s export_exit()\n",THIS_MODULE->name);
   function();
   printk(KERN_INFO"%s export_exit() complete\n",THIS_MODULE->name);
}
EXPORT_SYMBOL(var);
EXPORT_SYMBOL_GPL(function);

module_init(export_init);
module_exit(export_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMMY");
MODULE_DESCRIPTION("MY MODULE");
