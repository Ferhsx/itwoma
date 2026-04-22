#include <stdio.h>
#include "../include/manga.h"
#include "../include/http_client.h"
#include "../include/parser.h"


int main() {
    printf("ITWOMA (I'm Tired Of Web Manga Ads)\n\n");

    const char *url = "https://api.mangadex.org/manga?title=Vagabond&limit=1";

    MemoryBuffer resposta_api = install_data_url(url);

    if(resposta_api.memory != NULL){

        printf("\nInicio dos dados\n");
        
        Manga *manga_encontrado = parse_manga_json(resposta_api.memory);

        if(manga_encontrado!=NULL){
        
            printf(">> Titulo: %s\n", manga_encontrado->title);
            printf(">> ID Hash: %s\n", manga_encontrado->id);
            destruct_manga(manga_encontrado);
        
        }
        
        printf("Fim dos dados\n\n");
    }

    clear_buffer(&resposta_api);
    printf("\nMemoria limpa com sucesso. Encerrando...\n");
    return 0;
}