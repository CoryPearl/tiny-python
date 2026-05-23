#include "tiny-python.h"
#include <stdio.h>

int main(void) {
    py_t py;

    py_init(&py);
    py_use_stdio(&py);

    if (!py_run_file(&py, "example.py", NULL, 0)) {
        printf("python error: %s\n", py.error);
        py_deinit(&py);
        return 1;
    }

    py_deinit(&py);
    return 0;
}
