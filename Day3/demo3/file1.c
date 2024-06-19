#include<linux/module.h>
#include"header.h"

static __init int initialize(void)
{
  my_function();
  my_var=20;
  printk(KERN_INFO"%s init() my_var=%d\n",THIS_MODULE->name,my_var);
  printk(KERN_INFO"%s init() my_var=%d\n",THIS_MODULE->name,THIS_MODULE->state);
  printk(KERN_INFO"%s init() initialization completed\n",THIS_MODULE->name);
  return 0;
}
module_init(initialize);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("sammy");
MODULE_DESCRIPTION("my module");
