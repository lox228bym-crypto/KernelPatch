#include <linux/kernel.h>
#include <kpatch.h>

// Функция-заглушка: всегда возвращает 0 (успешная проверка подписи)
int bypass_sig(void *info, int flags) { return 0; }

int kpm_init(void) {
    // Ищем адрес функции проверки подписи в ядре
    unsigned long addr = kallsyms_lookup_name("module_sig_check");
    if (addr) {
        // Устанавливаем перехват (inline-hook)
        return kpatch_add_hook(addr, (void *)bypass_sig, NULL);
    }
    return -1; // Если символ не найден
}

void kpm_exit(void) {}
