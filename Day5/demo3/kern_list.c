#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/init_task.h>
#include<asm/current.h>

static __init int kern_list_init(void)
{
   struct task_struct *trav;
   printk(KERN_INFO"%s:kern_list_init called:\n",THIS_MODULE->name);
   /*
   list_for_each_entry(trav,&init_task.tasks,tasks)
   {
     printk(KERN_INFO"%s: pid=%d,com=%s\n",THIS_MODULE->name,trav->pid,trav->comm);
   }*/
   list_for_each_entry(trav, &current->tasks, tasks)
	{
		printk(KERN_INFO "%s : pid = %d, cmd = %s\n", THIS_MODULE->name, trav->pid, trav->comm);
	}
   printk(KERN_INFO"%s: init complete\n",THIS_MODULE->name);
   return 0;
}

static __exit void kern_list_exit(void)
{
  printk(KERN_INFO"%s kern_list_exit is completed\n",THIS_MODULE->name);
}
module_init(kern_list_init);
module_exit(kern_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sammy");
MODULE_DESCRIPTION("kernel_linked_list");
