#include<linux/module.h>

int init_module(void)
{
  printk(KERN_INFO"t_module\n");
  return 0;
}
void cleanup_module(void)
{
  printk(KERN_INFO"anup_module\n");
}
MODULE_INFO(license,"GPL");
MODULE_INFO(auther,"SAMADHAN");
MODULE_INFO(description,"My First Module");

