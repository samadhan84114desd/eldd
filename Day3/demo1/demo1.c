#include<linux/module.h>

static __init int f_init(void)
{
   printk(KERN_INFO"%s:f_init():state:%d\n",THIS_MODULE->name,THIS_MODULE->state);
   printk(KERN_INFO"%s:f_init():init_successful\n",THIS_MODULE->name);
   return 0;
}

static __exit void f_exit(void)
{
   printk(KERN_INFO"%s:f_exit():state:%d\n",THIS_MODULE->name,THIS_MODULE->state);
   printk(KERN_INFO"%s:f_exit():dinit_successful\n",THIS_MODULE->name);
}
module_init(f_init);
module_exit(f_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMMYA");
MODULE_DESCRIPTION("MY MODULE");
