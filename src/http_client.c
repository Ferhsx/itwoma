#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/http_client.h"

//malditos tutorias do youtube que nao ensinam a usar o curl em C, so mostram como usar em python ou JS, e quando tem um tutorial de C, ele é tão complexo que parece que o cara tá tentando te ensinar a fazer um navegador inteiro, e não só pegar os dados de uma URL, é tão difícil achar um exemplo simples que eu tive que ler a documentação do curl e entender como funciona pra conseguir fazer isso funcionar, mas enfim, aqui está o código para pegar os dados de uma URL usando curl em C.

static size_t WriteMemoryCallback (void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size*nmemb;
    MemoryBuffer *mem = (MemoryBuffer *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

MemoryBuffer install_data_url(const char *url) {
    MemoryBuffer chunk;

    chunk.memory = malloc(1);

    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl_handle = curl_easy_init();

    if(curl_handle){
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "itwoma-terminal-reader/1.0");

        printf("Fetching data from URL: %s\n", url);
        CURLcode res = curl_easy_perform(curl_handle);
    
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Data fetched successfully, size: %zu bytes\n", chunk.size);
        }

        curl_easy_cleanup(curl_handle);

    }
    curl_global_cleanup();

    return chunk;
}

void clear_buffer(MemoryBuffer *buffer) {
    if (buffer->memory) {
        free(buffer->memory);
        buffer->memory = NULL;
        buffer->size = 0;
    }
}