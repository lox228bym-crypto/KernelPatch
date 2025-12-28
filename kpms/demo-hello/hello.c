#include <linux/kernel.h>
#include <linux/module.h>

// Тип функции для ядра 4.19
typedef int (*module_sig_check_t)(void *info, int flags);

int kpm_init(void) {
    unsigned long addr = (unsigned long)kallsyms_lookup_name("module_sig_check");
    if (!addr) return -1;

    // Прямая перезапись начала функции инструкцией RET 0 (ARM64)
    // mov x0, #0 (0xd2800000) | ret (0xd65f03c0)
    uint32_t patch[] = { 0xd2800000, 0xd65f03c0 };
    
    // В KPM на APatch память ядра обычно уже доступна для записи
    memcpy((void *)addr, patch, sizeof(patch));
    
    return 0;
}

void kpm_exit(void) {}
