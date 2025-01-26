#include "types.h"
#include "user.h"
#include "stat.h"

// Shared variables for synchronization
int ready = 0;
Lock lock; // Use user-level Lock type (not spinlock)

void thread_func(void *arg1, void *arg2) {
    int tid = *(int*)arg2;

    if (tid == 2) {
        printf(1, "first:%d\n", requestresource(1));
        sleep(15);
        printf(1, "fifth:%d\n", requestresource(2));
        sleep(11);
        releaseresource(1);
        releaseresource(2); // Release resources
    }
    else if (tid == 3) {
        printf(1, "second:%d\n", requestresource(2));
        sleep(14);
        printf(1, "sixth:%d\n", requestresource(1));
        sleep(10);
        releaseresource(2);
        releaseresource(1); // Release resources
    }
    else if (tid == 4) {
        printf(1, "third:%d\n", requestresource(3));
        sleep(13);  
        releaseresource(3); // Release resources
    }
    else if (tid == 1) {
        printf(1, "forth:%d\n", requestresource(0));
        sleep(12);  
        releaseresource(0); // Release resources
    }

    sleep(100);
    exit();
}

int main() {
    int tids[4] = {1, 2, 3, 4};
    Lock_Init(&lock); // Initialize user-level lock

    // Create four threads
    for (int i = 0; i < 4; i++) {
        thread_create(&thread_func, 0, (void*)&tids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 4; i++) { // Wait for all threads
        join(tids[i]);
    }

    exit();
}