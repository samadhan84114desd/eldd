#include<linux/module.h>
#include<linux/kfifo.h>

struct kfifo mykfifo;

struct __init int mykfifo_init(void)
{
  char alpha[]="SAMADHANCHANDRAKANTWAGHMODE";
  char digits[]="123456789";

  int ret=kfifo_alloc(&mykfifo,32,GFP_KERNEL);
  if(ret<0)
  {
    printk(KERN_INFO"%s: kfifo_alloc() is failed\n",THIS_MODULE->name);
	return -1;
  }

  printk(KERN_INFO"%s Size of myfifo=%u\n",THIS_MODULE->name,
