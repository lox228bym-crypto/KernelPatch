// Никаких #include! Определяем функции вручную
extern unsigned long kallsyms_lookup_name(const char *name);

int kpm_init(void) {
    unsigned long addr = kallsyms_lookup_name("module_sig_check");
    if (!addr) return -1;

    // Записываем RET 0 прямо в память
    unsigned int *p = (unsigned int *)addr;
    p[0] = 0xd2800000; // mov x0, #0
    p[1] = 0xd65f03c0; // ret
    return 0;
}

void kpm_exit(void) {}
