#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stddef.h>

typedef struct {
    char *memory;
    size_t size;

} MemoryBuffer;

MemoryBuffer install_data_url(const char *url);

void clear_buffer(MemoryBuffer *buffer);

#endif