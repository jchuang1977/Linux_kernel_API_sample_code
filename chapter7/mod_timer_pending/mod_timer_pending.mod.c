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
	{ 0xf1c24d8e, "mod_timer_pending" },
	{ 0x5702a4ae, "add_timer" },
	{ 0xee421be0, "init_timer_key" },
	{ 0x7d11c268, "jiffies" },
	{ 0x8953bb27, "del_timer" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "89FFB55D0DE1A2475D8D15B");
