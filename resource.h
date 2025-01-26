// resource.h
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#define NRESOURCE 5
#define MAXTHREAD 100

struct resource {
    int acquired;
    void *startaddr;
};

// تعاریح توابع
int requestresource(int Resource_ID);
int releaseresource(int Resource_ID);
int writeresource(int Resource_ID, void *buffer, int offset, int size);
int readresource(int Resource_ID, int offset, int size, void *buffer);

#endif