#include <stdio.h>
#include "../include/manga.h"
#include "../include/http_client.h"
#include "../include/parser.h"
#include "../include/utils.h" // AQUI: Corrigindo o Erro 1 (incluindo as utilidades)

int main() {
    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");

    const char *url_manga = "https://api.mangadex.org/manga?title=Berserk&limit=1";

    // --- 1. BUSCA O MANGÁ ---
    MemoryBuffer res_manga = install_data_url(url_manga);
    if (res_manga.memory == NULL) return 1;

    Manga *manga = parse_manga_json(res_manga.memory);
    clear_buffer(&res_manga);

    if (manga != NULL) {
        printf("\n>> Manga Encontrado: %s\n", manga->title);

        // --- 2. BUSCA OS CAPÍTULOS DESSE MANGÁ ---
        char url_capitulos[256];
        snprintf(url_capitulos, sizeof(url_capitulos),
            "https://api.mangadex.org/manga/%s/feed?translatedLanguage[]=en&limit=5&order[chapter]=asc",
            manga->id);

        printf("\nBuscando capitulos em: %s\n", url_capitulos);
        MemoryBuffer res_caps = install_data_url(url_capitulos);

        if (res_caps.memory != NULL) {
            ChapterList lista = parse_chapters_json(res_caps.memory);

            if (lista.count > 0) {
                Chapter *primeiro_cap = lista.chapters[0];
                printf("\n==========================================\n");
                printf("LENDO O CAPITULO: %s - %s\n", primeiro_cap->chapter_number, primeiro_cap->title);
                printf("==========================================\n");

                char url_paginas[256];
                snprintf(url_paginas, sizeof(url_paginas),
                    "https://api.mangadex.org/at-home/server/%s", primeiro_cap->id);

                printf("Conectando no MangaDex@Home...\n");
                MemoryBuffer res_pages = install_data_url(url_paginas);

                if (res_pages.memory != NULL) {
                    PageList paginas = parse_pagelist_json(res_pages.memory); // AQUI: Corrigindo o Erro 2

                    if (paginas.page_count > 0) {
                        printf("\n[Servidor Alocado]: %s\n", paginas.base_url);
                        printf("[Total de Paginas]: %d\n", paginas.page_count);

                        // 1. Criar a pasta de downloads do capítulo
                        const char *pasta_downloads = "capitulo_baixado";
                        if (!criar_pasta(pasta_downloads)) {
                            printf("Erro fatal ao criar a pasta de downloads.\n");
                            return 1;
                        }

                        printf("Iniciando download do capitulo para a pasta '%s'...\n", pasta_downloads);

                        // 2. Loop de Download
                        int limite_download = (paginas.page_count > 3) ? 3 : paginas.page_count;

                        for(int i = 0; i < limite_download; i++) {
                            char url_imagem[512];
                            snprintf(url_imagem, sizeof(url_imagem), "%s/data/%s/%s",
                                paginas.base_url, paginas.chapter_hash, paginas.page_filenames[i]);

                            char caminho_local[256];
                            snprintf(caminho_local, sizeof(caminho_local), "%s/%03d.jpg", pasta_downloads, i+1);

                            printf("Baixando pagina %d de %d... ", i+1, limite_download);
                            fflush(stdout);

                            // Chamando a sua função renomeada
                            if (install_files(url_imagem, caminho_local)) {
                                printf("[OK]\n");
                            } else {
                                printf("[FALHA]\n");
                            }
                        }

                        printf("\n=== DOWNLOAD CONCLUIDO ===\n");

                        // Chama a nossa função abstrata, que sabe se virar no Windows e no Linux
                        ler_manga(pasta_downloads);
                        limpar_pasta_downloads(pasta_downloads);

                        printf("Leitura finalizada e HD limpo.\n");
                    }

                    // IMPORTANTE: Faxina das páginas
                    destruct_page_list(&paginas); // Assumi que você traduziu o nome dessa função também!
                }
                clear_buffer(&res_pages);
            }

            destruct_chapter_list(&lista);
        }
        clear_buffer(&res_caps);

        destruct_manga(manga);
    }
    
    printf("\nMemoria limpa. Encerrando programa.\n");
    return 0;
}