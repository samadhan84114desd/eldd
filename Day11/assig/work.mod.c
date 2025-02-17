#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0x70e69df1, "cdev_del" },
	{ 0x6f915e6e, "device_destroy" },
	{ 0xbff14d94, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x35b1ec57, "gpio_to_desc" },
	{ 0xb02f33ca, "gpiod_get_raw_value" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xeebba815, "__class_create" },
	{ 0x2682110c, "device_create" },
	{ 0x5943b701, "cdev_init" },
	{ 0xe1173f12, "cdev_add" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x37aff350, "gpiod_direction_output_raw" },
	{ 0x5f6f5ff1, "gpiod_direction_input" },
	{ 0xc44882cb, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x2d3385d3, "system_wq" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x5078fab5, "gpiod_set_raw_value" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xf3d7e125, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "EB85AD8C2786B2777742F11");
