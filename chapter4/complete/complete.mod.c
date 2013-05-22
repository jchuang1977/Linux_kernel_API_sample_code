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
	{ 0xe456bd3a, "complete" },
	{ 0x8733e9a3, "sleep_on_timeout" },
	{ 0x650fb346, "add_wait_queue" },
	{ 0xffd5a395, "default_wake_function" },
	{ 0x8cd5eba7, "per_cpu__current_task" },
	{ 0x64cd5d16, "init_waitqueue_head" },
	{ 0x7e9ebb05, "kernel_thread" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1F63A374C14F15DFF4780B3");
