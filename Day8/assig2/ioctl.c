#include<linux/module.h>
#include<linux/kfifo.h>
#include<linux/device.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include "pchar_ioctl.h"

static int pchar_open(struct inode *, struct file *);
static int pchar_close(struct inode *, struct file *);
static ssize_t pchar_read(struct file *, char *, size_t, loff_t *);
static ssize_t pchar_write(struct file *, const char *, size_t, loff_t *);
static long pchar_ioctl(struct file *, unsigned int, unsigned long);

#define MAX 32

static struct kfifo buf;
static  dev_t devno;
static int major;
static struct class *pclass;
static struct cdev cdev;
static struct file_operations pchar_fops={
      .owner=THIS_MODULE,
	  .read=pchar_read,
	  .write=pchar_write,
	  .release=pchar_close,
	  .open=pchar_open,
	  .unlocked_ioctl = pchar_ioctl
	  };

static __init int pchar_init(void)
{
   struct device *pdevice;
   int ret,minor;

   printk(KERN_INFO"%s: pchar_init() is called\n",THIS_MODULE->name);
   ret=kfifo_alloc(&buf,MAX,GFP_KERNEL);
   if(ret!=0)
   {
      printk(KERN_ERR"%s:kfifo_alloc() failed\n",THIS_MODULE->name);
	  goto kfifo_alloc_failed;
   }
   
   printk(KERN_INFO"%s: kfifo_alloc() is completed\n",THIS_MODULE->name);
   
   ret=alloc_chrdev_region(&devno,0,1,"pchar");
   if(ret!=0)
   {
       printk(KERN_ERR"%s: alloc_chrdev_region() is failed\n",THIS_MODULE->name);
	   goto alloc_chrdev_region_failed;
   }
   minor=MINOR(devno);
   major=MAJOR(devno);
   printk(KERN_INFO"%s: alloc_chrdev_region() is completed %d/%d\n",THIS_MODULE->name,major,minor);

   pclass=class_create(THIS_MODULE,"pchar_class");
   if(IS_ERR(pclass))
   {
       printk(KERN_ERR"%s: class_create() failed\n",THIS_MODULE->name);
	   goto class_create_failed;
   }
   printk(KERN_INFO"%s: class_create() completed\n",THIS_MODULE->name);
    
   pdevice=device_create(pclass,NULL,devno,NULL,"pchar%d",0);
   if(IS_ERR(pdevice))
   {
      printk(KERN_INFO"%s:device_create() failed\n",THIS_MODULE->name);
	  goto device_create_failed;
   }
   printk(KERN_INFO"%s: device_create() is completed\n",THIS_MODULE->name);
   cdev_init(&cdev,&pchar_fops);
   ret=cdev_add(&cdev,devno,1);
   if(ret!=0)
   {
      printk(KERN_INFO"%s: cdev_add() is failed\n",THIS_MODULE->name);
	  goto cdev_add_failed;
   }
   printk(KERN_INFO"%s: pchar_init() is end\n",THIS_MODULE->name);
   return 0;
cdev_add_failed:
   device_destroy(pclass,devno);
device_create_failed:
   class_destroy(pclass);
class_create_failed:
   unregister_chrdev_region(devno,1);
alloc_chrdev_region_failed:
   kfifo_free(&buf);
kfifo_alloc_failed:
   return ret;
}

static __exit void pchar_exit(void)
{
   printk(KERN_INFO"%s: pchar_exit() is called\n",THIS_MODULE->name);
   cdev_del(&cdev);
   printk(KERN_INFO"%s: cdev_del() is completed\n",THIS_MODULE->name);
   device_destroy(pclass,devno);
   printk(KERN_INFO"%s: device_destroy() is completed\n",THIS_MODULE->name);
   class_destroy(pclass);
   printk(KERN_INFO"%s: class_destroy() is completed\n",THIS_MODULE->name);
   unregister_chrdev_region(devno,1);
   printk(KERN_INFO"%s unregister_chrdev_region() is completed\n",THIS_MODULE->name);
   kfifo_free(&buf);
   printk(KERN_INFO"%s: kfifo_free() is complete\n",THIS_MODULE->name);
   printk(KERN_INFO"%s: pchar_exit() is end\n",THIS_MODULE->name);
}

static int pchar_open(struct inode *pinode,struct file *pfile)
{
   printk(KERN_INFO"%s: pchar_open() is called\n",THIS_MODULE->name);
   return 0;
}

static int pchar_close(struct inode *pinode,struct file *pfile)
{
   printk(KERN_INFO"%s: pchar_close() is called\n",THIS_MODULE->name);
   return 0;
}

static ssize_t pchar_read(struct file *pfile,char *ubuf,size_t size,loff_t *poffset)
{
   int nbytes,ret;
   printk(KERN_INFO"%s: pchar_read() is called\n",THIS_MODULE->name);
   
   ret=kfifo_to_user(&buf,ubuf,size,&nbytes);
   if(ret<0)
   {
     printk(KERN_INFO"%s: pchar_read() is failed to copy the data from kernel db\n",THIS_MODULE->name);
	 return ret;
   }
   printk(KERN_INFO"%s: pchar_read() is copied %d bytes to user space\n",THIS_MODULE->name,nbytes);
   return nbytes;
}

static ssize_t pchar_write(struct file *pfile, const char *ubuf,size_t size,loff_t *poffset)
{
   int ret ,nbytes;
   printk(KERN_INFO"%s: pchar_write() is called\n",THIS_MODULE->name);
   
   ret=kfifo_from_user(&buf,ubuf,size,&nbytes);
   if(ret<0)
   {
      printk(KERN_INFO"%s pckar_write() is failed to copy data from user space to kernel db\n",THIS_MODULE->name);
	  return ret;
   }
   printk(KERN_INFO"%s: pchar_write() copied %d bytes from user space to kernel db\n",THIS_MODULE->name,nbytes);
   return nbytes;
}

static long pchar_ioctl(struct file *pfile,unsigned int cmd,unsigned long param)
{
   info_t info;
   unsigned int new_size;
   char *temp_buf;
   int ret, copied;
   switch(cmd)
   {
      case FIFO_CLEAR:
	     printk(KERN_INFO"%s:pchar_ioctl() fifo clear\n",THIS_MODULE->name);
		 kfifo_reset(&buf);
		 break;
	  
	  case FIFO_INFO:
	     printk(KERN_INFO"%s pchar_ioctl() get fifo info\n",THIS_MODULE->name);
		 info.size=kfifo_size(&buf);
		 info.avail=kfifo_avail(&buf);
		 info.len=kfifo_len(&buf);
		 copy_to_user((void*)param,&info,sizeof(info_t));
		 break;

	  case FIFO_RESIZE:
	      printk(KERN_INFO"%s: pchar_ioctl() resize fifo\n",THIS_MODULE->name);
		   printk(KERN_INFO "%s: pchar_ioctl() resize fifo\n", THIS_MODULE->name);
            if (copy_from_user(&new_size, (void *)param, sizeof(new_size))) {
                return -EFAULT;
            }

            
            temp_buf = kmalloc(kfifo_len(&buf), GFP_KERNEL);
            if (!temp_buf) {
                printk(KERN_ERR "%s: pchar_ioctl() kmalloc() failed\n", THIS_MODULE->name);
                return -ENOMEM;
            }

            
            copied = kfifo_out(&buf, temp_buf, kfifo_len(&buf));

            
            kfifo_free(&buf);

           
            ret = kfifo_alloc(&buf, new_size, GFP_KERNEL);
            if (ret != 0) {
                printk(KERN_ERR "%s: pchar_ioctl() kfifo_alloc() failed\n", THIS_MODULE->name);
                kfree(temp_buf);
                return -ENOMEM;
            }
		  break;
	  default:
	      printk(KERN_INFO"%s: pchar_ioctl() unsupported cmd\n",THIS_MODULE->name);

		  return -EINVAL;
	}
	return 0;
}
   
module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMMY");
MODULE_DESCRIPTION("IOCTL IMPLEMENTED !!");

