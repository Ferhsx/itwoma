#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stddef.h>

typedef struct {
    char *memory;
    size_t size;

} MemoryBuffer;

MemoryBuffer install_data_url(const char *url);

int install_files(const char *url, const char *caminho_destino);

void clear_buffer(MemoryBuffer *buffer);

#endif