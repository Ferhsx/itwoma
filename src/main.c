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

            if(lista.count > 0){
                Chapter *primeiro_capitulo = lista.chapters[0];
                printf("\n>> Capitulo Encontrado: %s - %s\n", primeiro_capitulo->chapter_number, primeiro_capitulo->title);

                char url_paginas[256];
                snprintf(url_paginas, sizeof(url_paginas), "https://api.mangadex.org/at-home/server/%s", primeiro_capitulo->id);

                printf("Conectando no MangaDex@Home...\n");
                MemoryBuffer res_pages = install_data_url(url_paginas);

                if(res_pages.memory != NULL){
                    PageList paginas = parse_pagelist_json(res_pages.memory);

                    if(paginas.page_count > 0){
                        printf("\n[Servidor alocado] Base URL: %s\n", paginas.base_url);
                        printf("Paginas disponiveis: %d\n", paginas.page_count);

                        int limite_print = (paginas.page_count < 5) ? paginas.page_count : 5; // Limita a impressão a 5 páginas

                        for(int i = 0; i < limite_print; i++){
                            printf("Link Pagina %d: %s/data/%s/%s\n", 
                                i+1, 
                                paginas.base_url, 
                                paginas.chapter_hash, 
                                paginas.page_filenames[i]);
                        }
                        printf("... (e mais %d paginas)\n", paginas.page_count - limite_print);
                    }
                    destruct_page_list(&paginas);
                }
                clear_buffer(&res_pages);
            }
            destruct_chapter_list(&lista);
        }
        clear_buffer(&res_caps);
        
        // Faxina do Manga
        destruct_manga(manga);
    }
    
    printf("\nMemoria limpa. Encerrando programa.\n");
    return 0;
}