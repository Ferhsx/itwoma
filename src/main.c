#include <stdio.h>
#include <string.h> 
#include "../include/manga.h"
#include "../include/http_client.h"
#include "../include/parser.h"

void prepare_text_url(char *texto) {
    texto[strcspn(texto, "\n")] = 0;

    for(int i = 0; texto[i] != '\0'; i++) {
        if(texto[i] == ' ') {
            texto[i] = '+';
        }
    }
}

int main() {
    //os printf foi feito por ia pq preguiça de formatar a saída, mas é só pra dar um charme mesmo, entao acho q n tem problema
    printf("===========================================\n");
    printf("   ITWOMA (I'm Tired Of Web Manga Ads)     \n");
    printf("===========================================\n\n");

    char busca_usuario[100];

    printf("Digite o nome do manga que deseja buscar: ");
    
    if (fgets(busca_usuario, sizeof(busca_usuario), stdin) != NULL) {
        
        prepare_text_url(busca_usuario);

        char url_dinamica[256];
        
        snprintf(url_dinamica, sizeof(url_dinamica), 
                 "https://api.mangadex.org/manga?title=%s&limit=1", busca_usuario);

        printf("\nBuscando na internet: %s\n", url_dinamica);

        MemoryBuffer resposta_api = install_data_url(url_dinamica);

        if (resposta_api.memory != NULL) {
            Manga *manga_encontrado = parse_manga_json(resposta_api.memory);
            
            if (manga_encontrado != NULL) {
                printf("\n--- RESULTADO DA BUSCA ---\n");
                printf("Titulo: %s\n", manga_encontrado->title);
                printf("ID Hash: %s\n", manga_encontrado->id);
                printf("--------------------------\n");
                
                destruct_manga(manga_encontrado);
            } else {
                printf("\nOps! Nenhum manga encontrado com esse nome.\n");
            }
            clear_buffer(&resposta_api);
        }
    }

    printf("\nEncerrando o programa.\n");
    return 0;
}