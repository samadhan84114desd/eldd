#include<linux/module.h>
#include"header.h"

static __exit void d_exit(void)
{
  my_function();
  printk(KERN_INFO"%s :dinit(): state=%d\n",THIS_MODULE->name,THIS_MODULE->state);
  printk(KERN_INFO "%s : desd_exit() : deinit is completed successfully\n", THIS_MODULE->name);
}
module_exit(d_exit);
