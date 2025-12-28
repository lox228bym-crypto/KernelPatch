#include <linux/kernel.h>
#include "../../kernel/patch/include/kpatch.h"

static int hook_sig(void *info, int flags) {
    return 0;
}

int kpm_init(void) {
    unsigned long addr = (unsigned long)kallsyms_lookup_name("module_sig_check");
    if (addr) {
        return kpatch_add_hook((void *)addr, (void *)hook_sig, NULL);
    }
    return -1;
}

void kpm_exit(void) {
}
