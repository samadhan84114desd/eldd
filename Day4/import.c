#include<linux/module.h>
#include"export.h"


static __init int import_init(void)
{
   printk(KERN_INFO"%s fun import start\n",THIS_MODULE->name);
   function();
   var=20;
   printk(KERN_INFO"%s import init completed\n",THIS_MODULE->name);
   return 0;
}

static __exit void import_exit(void)
{
  printk(KERN_INFO"%s import_exit() start\n",THIS_MODULE->name);
  function();
  printk(KERN_INFO"%s import_exit() complete\n",THIS_MODULE->name);
}

module_init(import_init);
module_exit(import_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sammy");
MODULE_DESCRIPTION("dependent module");

