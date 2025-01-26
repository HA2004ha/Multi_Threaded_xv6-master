#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"

#define RESOURCE_COUNT 2

void thread_function_1(void *arg1, void *arg2) {
    int resource1 = 0, resource2 = 1;
    
   
    if (requestresource(resource1) == 0) {
        printf(1, "Thread 1 acquired resource %d\n", resource1);

        sleep(100);

        if (requestresource(resource2) == 0) {
            printf(1, "Thread 1 acquired resource %d\n", resource2);
            releaseresource(resource2);
        } else {
            printf(1, "Thread 1 failed to acquire resource %d\n", resource2);
        }

        releaseresource(resource1);
    } else {
        printf(1, "Thread 1 failed to acquire resource %d\n", resource1);
    }

    exit();
}

void thread_function_2(void *arg1, void *arg2) {
    int resource1 = 0, resource2 = 1;
    if (requestresource(resource2) == 0) {
        printf(1, "Thread 2 acquired resource %d\n", resource2);

        sleep(100); 

        if (requestresource(resource1) == 0) {
            printf(1, "Thread 2 acquired resource %d\n", resource1);
            releaseresource(resource1);
        } else {
            printf(1, "Thread 2 failed to acquire resource %d\n", resource1);
        }

        releaseresource(resource2);
    } else {
        printf(1, "Thread 2 failed to acquire resource %d\n", resource2);
    }

    exit();
}

int main() {
    printf(1, "*** Deadlock Test ***\n");

    
    thread_create(thread_function_1, 0, 0);
    thread_create(thread_function_2, 0, 0);

    join(1);
    join(2);

    printf(1, "*** Test Finished ***\n");
    exit();
}
