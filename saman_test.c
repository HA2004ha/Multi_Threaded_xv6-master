#include "types.h"
#include "user.h"
#include "stat.h"

void thread1_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r0 = requestresource(0);
    sleep(100);
    int r1 = requestresource(1);

    if (r1 == 0 && r0 == 0)
    {
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(100);
        releaseresource(1);
        releaseresource(0);
    }
    else
    {
        if (r1 == 0)
            releaseresource(0);
        if (r0 == 0)
            releaseresource(1);
        printf(2, "Thread %d resource acquire failed: r1=%d, r0=%d\n", *tid, r1, r0);
    }
    exit();
}

void thread2_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r1 = requestresource(1);
    sleep(200);
    int r0 = requestresource(0);

    if (r1 == 0 && r0 == 0)
    {
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(100);
        releaseresource(0);
        releaseresource(1);
    }
    else
    {
        if (r1 == 0)
            releaseresource(1);
        if (r0 == 0)
            releaseresource(0);
        printf(2, "Thread %d resource acquire failed: r1=%d, r0=%d\n", *tid, r1, r0);
    }
    exit();
}

int main()
{
    int tid1 = 1, tid2 = 2;

    int th1 = thread_create(&thread1_func, 0, (void *)&tid1);
    int th2 = thread_create(&thread2_func, 0, (void *)&tid2);

    printf(2, "Thread 1 creation: %d, Thread 2 creation: %d\n", th1, th2);

    if (th1 < 0 || th2 < 0)
    {
        printf(2, "Thread creation failed\n");
        exit();
    }

    join(tid1);
    join(tid2);

    printf(0, "Deadlock test completed\n");
    exit();
}