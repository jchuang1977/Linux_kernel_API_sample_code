#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x4061a14b, "module_layout" },
	{ 0x5702a4ae, "add_timer" },
	{ 0xee421be0, "init_timer_key" },
	{ 0x7d11c268, "jiffies" },
	{ 0xb72397d5, "printk" },
	{ 0xe910b532, "del_timer_sync" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "982427E94037170525E2D2D");
