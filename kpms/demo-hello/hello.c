#include <linux/kernel.h>
#include <linux/module.h>
#include <kpatch.h> // Специфично для KernelPatch/APatch

int hook_module_sig_check(void *info, int flags) {
    return 0; // Всегда успех
}

int kpm_init(void) {
    unsigned long addr = (unsigned long)kallsyms_lookup_name("module_sig_check");
    if (addr) {
        // API для 2025 года в KernelPatch
        return kpatch_add_hook(addr, (void *)hook_module_sig_check, NULL);
    }
    return -1;
}

void kpm_exit(void) {}
