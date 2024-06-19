#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>

struct student
{
    int rollno;
	char name[32];
	int marks;
	struct list_head slist;
};
struct list_head slist;

static __init int kern_list_init(void)
{
   struct student *ptr=NULL,*pos;
//   struct list_head *pos;

   printk(KERN_INFO"%s kernel list is called\n",THIS_MODULE->name);
   INIT_LIST_HEAD(&slist);

   ptr=kmalloc(sizeof(struct student),GFP_KERNEL);

   ptr->rollno=3;
   strcpy(ptr->name,"sam");
   ptr->marks=85;
   list_add(&ptr->slist,&slist);

   ptr=kmalloc(sizeof(struct student),GFP_KERNEL);
   ptr->rollno=5;
   strcpy(ptr->name,"ram");
   ptr->marks=76;
   list_add(&ptr->slist,&slist);

   ptr=kmalloc(sizeof(struct student),GFP_KERNEL);
   ptr->rollno=8;
   strcpy(ptr->name,"shyam");
   ptr->marks=81;
   list_add(&ptr->slist,&slist);

   ptr=kmalloc(sizeof(struct student),GFP_KERNEL);
   ptr->rollno=11;
   strcpy(ptr->name,"radha");
   ptr->marks=77;
   list_add(&ptr->slist,&slist);
 
   printk(KERN_INFO"%s Students List:\n",THIS_MODULE->name);
   list_for_each_entry(pos,&slist,slist)
   {
      printk(KERN_INFO"%s :name=%s ,rollno=%d, marks=%d\n",THIS_MODULE->name,pos->name,pos->rollno,pos->marks);
   }
   printk(KERN_INFO"%s : kernel_list_init is complete:\n",THIS_MODULE->name);
   return 0;
}

static __exit void kern_list_exit(void)
{
   struct student *pos,*n;
   //struct student *st;
   printk(KERN_INFO"%s kern_list_exit is called\n",THIS_MODULE->name);
   list_for_each_entry_safe(pos,n,&slist,slist)
   {
     // st=list_entry(pos,struct student,slist);
	  list_del(&pos->slist);
	  kfree(pos);
   }
   printk(KERN_INFO" %s kern_list_exit is completed\n",THIS_MODULE->name);
}

module_init(kern_list_init);
module_exit(kern_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMMY");
MODULE_DESCRIPTION("KERNEL_LINKED_LIST");



















