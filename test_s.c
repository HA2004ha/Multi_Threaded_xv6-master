#include "types.h"
#include "user.h"
#include "resource.h"

int main() {
    // اختصاص منبع
    if (requestresource(0) != 0) {
        printf(1, "Acquire failed\n");
        exit();
    }

    // نوشتن داده
    char data[] = "XV6 Test";
    if (writeresource(0, data, 0, sizeof(data)) != 0) {
        printf(1, "Write failed\n");
        exit();
    }

    // خواندن داده
    char buffer[50];
    if (readresource(0, 0, sizeof(data), buffer) != 0) {
        printf(1, "Read failed\n");
        exit();
    }

    // چاپ داده‌های نوشته شده و خوانده شده
    printf(1, "Written data: %s\n", data);
    printf(1, "Read data: %s\n", buffer);

    // مقایسه داده‌ها
    if (strcmp(data, buffer) != 0) {
        printf(1, "Data mismatch: Written data and read data are not the same.\n");
        exit();
    }

    // آزادسازی منبع
    if (releaseresource(0) != 0) {
        printf(1, "Release failed\n");
        exit();
    }

    printf(1, "Success! Data written and read are identical.\n");
    exit();
}