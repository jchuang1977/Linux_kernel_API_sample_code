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
	{ 0x181b6ff2, "mempool_resize" },
	{ 0xf8b30e93, "mempool_create" },
	{ 0x183fa88b, "mempool_alloc_slab" },
	{ 0x8a99a016, "mempool_free_slab" },
	{ 0x6c1201c9, "kmem_cache_create" },
	{ 0xb72397d5, "printk" },
	{ 0x3ca90814, "kmem_cache_destroy" },
	{ 0xff708fd3, "mempool_destroy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E4FAB86C158AF5FEF517F92");
