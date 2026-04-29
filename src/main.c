#include <stdio.h>
#include "../include/manga.h"
#include "../include/http_client.h"
#include "../include/parser.h"

int main() {
    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");

    const char *url_manga = "https://api.mangadex.org/manga?title=Berserk&limit=1";
    
    // --- 1. BUSCA O MANGÁ ---
    MemoryBuffer res_manga = install_data_url(url_manga);
    if (res_manga.memory == NULL) return 1;

    Manga *manga = parse_manga_json(res_manga.memory);
    clear_buffer(&res_manga); // Já podemos limpar o balde

    if (manga != NULL) {
        printf("\n>> Manga Encontrado: %s\n", manga->title);
        
        // --- 2. BUSCA OS CAPÍTULOS DESSE MANGÁ ---
        // Cria um texto com 256 espaços para montar a URL
        char url_capitulos[256]; 
        
        // Monta a URL passando o manga->id. Limitamos a 5 capítulos, idioma Inglês, em ordem crescente.
        snprintf(url_capitulos, sizeof(url_capitulos), 
            "https://api.mangadex.org/manga/%s/feed?translatedLanguage[]=en&limit=5&order[chapter]=asc", 
            manga->id);

        printf("\nBuscando capitulos em: %s\n", url_capitulos);
        MemoryBuffer res_caps = install_data_url(url_capitulos);
        
        if (res_caps.memory != NULL) {
            ChapterList lista = parse_chapters_json(res_caps.memory);
            
            printf("\n--- LISTA DE CAPITULOS ---\n");
            for (int i = 0; i < lista.count; i++) {
                printf("[Capitulo %s] %s \n   ID: %s\n", 
                    lista.chapters[i]->chapter_number, 
                    lista.chapters[i]->title,
                    lista.chapters[i]->id);
            }
            printf("--------------------------\n");

            // Faxina da Lista
            destruct_chapter_list(&lista);
        }
        clear_buffer(&res_caps);
        
        // Faxina do Manga
        destruct_manga(manga);
    }
    
    printf("\nMemoria limpa. Encerrando programa.\n");
    return 0;
}