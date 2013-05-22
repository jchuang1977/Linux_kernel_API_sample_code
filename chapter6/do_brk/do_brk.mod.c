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
	{ 0x9eecde16, "do_brk" },
	{ 0xb72397d5, "printk" },
	{ 0x3f39b162, "up_write" },
	{ 0xdb488209, "do_munmap" },
	{ 0xb13c4dba, "down_write" },
	{ 0x8cd5eba7, "per_cpu__current_task" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "4C977961D254249F8F13626");
