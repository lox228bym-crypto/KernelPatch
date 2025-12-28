#include "../../kernel/include/kallsyms.h"

// Заглушка типов, так как linux/types.h не найден
typedef unsigned int uint32_t;

int kpm_init(void) {
    // Ищем адрес функции напрямую через kallsyms
    unsigned long addr = kallsyms_lookup_name("module_sig_check");
    if (!addr) return -1;

    // Машинный код ARM64: mov x0, #0; ret
    uint32_t patch[] = { 0xd2800000, 0xd65f03c0 };
    
    // Прямая запись в память (в KPM контексте разрешена)
    unsigned char *p = (unsigned char *)addr;
    unsigned char *src = (unsigned char *)patch;
    for (int i = 0; i < 8; i++) {
        p[i] = src[i];
    }
    
    return 0;
}

void kpm_exit(void) {}
