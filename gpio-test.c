#include "tiny-python.h"
#include <stdio.h>

static int pins[64];

static int test_gpio_mode(int pin, int mode, void *user_data) {
    (void)user_data;
    printf("mode %d %d\n", pin, mode);
    return pin >= 0 && pin < 64;
}

static int test_gpio_write(int pin, int value, void *user_data) {
    (void)user_data;
    if (pin < 0 || pin >= 64) {
        return 0;
    }
    pins[pin] = value ? 1 : 0;
    printf("write %d %d\n", pin, pins[pin]);
    return 1;
}

static int test_gpio_read(int pin, int *value, void *user_data) {
    (void)user_data;
    if (pin < 0 || pin >= 64 || value == NULL) {
        return 0;
    }
    *value = pins[pin];
    return 1;
}

int main(void) {
    py_t py;

    py_init(&py);
    py_use_stdio(&py);
    py_set_gpio_callbacks(&py, test_gpio_mode, test_gpio_write, test_gpio_read, NULL);

    if (!py_run_source(&py,
        "pinMode(2, OUTPUT)\n"
        "digitalWrite(2, HIGH)\n"
        "print(digitalRead(2))\n",
        NULL,
        0)) {
        printf("python error: %s\n", py.error);
        py_deinit(&py);
        return 1;
    }

    py_deinit(&py);
    return 0;
}
