#include <stdio.h>
#include "../include/manga.h"
#include "../include/http_client.h"


int main() {
    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");

    const char *url = "https://api.mangadex.org/manga?title=Vagabond&limit=1";

    MemoryBuffer resposta_api = install_data_url(url);

    if(resposta_api.memory != NULL){
        printf("\n--- Inicio dos dados ---\n");
        printf("%s\n", resposta_api.memory);
        printf("--- Fim dos dados ---\n\n");
    }

    clear_buffer(&resposta_api);
    printf("\nMemoria limpa com sucesso. Encerrando...\n");
    return 0;
}