#include <stdio.h>
#include "../include/manga.h"
#include "../include/http_client.h"
#include "../include/parser.h"
#include "../include/utils.h"
#include <stdlib.h>

int main() {
    while(1) {
        printf("\n======================================================\n");
        char nome_digitado[100];
        printf("Digite o nome do manga (ou digite 'sair' para fechar): ");

        if (fgets(nome_digitado, sizeof(nome_digitado), stdin) == NULL) {
            break; // Sai se der erro de leitura
        }

        // Verifica se o usuário quer sair do programa
        if (strncmp(nome_digitado, "sair", 4) == 0) {
            printf("Saindo do ITWOMA... Ate a proxima leitura!\n");
            break; // Quebra o laço infinito e encerra o programa
        }

        char nome_formatado[300];
        formatar_texto_url(nome_formatado, nome_digitado);

        // Se o usuário apertou Enter sem digitar nada, recomeça o laço
        if (strlen(nome_formatado) == 0) continue;

        char url_manga[512];
        snprintf(url_manga, sizeof(url_manga),
                 "https://api.mangadex.org/manga?title=%s&limit=1&order[relevance]=desc",
                 nome_formatado);

        printf("\nProcurando por '%s'...\n", nome_digitado);

    // --- 4. BUSCA O MANGÁ ---
        MemoryBuffer res_manga = install_data_url(url_manga);
    // ... Daqui pra baixo o seu código continua IGUALZINHO ao que já estava!
        if (res_manga.memory == NULL) return 1;

        Manga *manga = parse_manga_json(res_manga.memory);
        clear_buffer(&res_manga);

        if (manga != NULL) {
         printf("\n>> Manga Encontrado: %s\n", manga->title);

          // --- 2. BUSCA OS CAPÍTULOS DESSE MANGÁ ---
         char url_capitulos[256];
         snprintf(url_capitulos, sizeof(url_capitulos),
               "https://api.mangadex.org/manga/%s/feed?translatedLanguage[]=pt-br&translatedLanguage[]=en&limit=20&order[chapter]=asc",
               manga->id);

          printf("\nBuscando capitulos em: %s\n", url_capitulos);
          MemoryBuffer res_caps = install_data_url(url_capitulos);

         if (res_caps.memory != NULL) {
               ChapterList lista = parse_chapters_json(res_caps.memory);

             if (lista.count > 0) {
                    // --- NOVO: MENU INTERATIVO DE CAPÍTULOS ---
                   printf("\n--- CAPITULOS DISPONIVEIS ---\n");
                  for (int i = 0; i < lista.count; i++) {
                     printf("[%d] Cap: %s - %s\n", i,
                           lista.chapters[i]->chapter_number,
                           lista.chapters[i]->title);
                  }
                 printf("-----------------------------\n");

                 printf("\nDigite o numero entre colchetes [ ] do capitulo que deseja ler: ");
                 char escolha_str[10];
                 int escolha = -1;

                    if (fgets(escolha_str, sizeof(escolha_str), stdin) != NULL) {
                       escolha = atoi(escolha_str);
                    }

                    // Valida se o usuário digitou um número que existe na lista
                    if (escolha >= 0 && escolha < lista.count) {
                        Chapter *cap_escolhido = lista.chapters[escolha];

                        printf("\n==========================================\n");
                        printf("LENDO O CAPITULO: %s - %s\n", cap_escolhido->chapter_number, cap_escolhido->title);
                        printf("==========================================\n");

                        char url_paginas[256];
                        snprintf(url_paginas, sizeof(url_paginas),
                            "https://api.mangadex.org/at-home/server/%s", cap_escolhido->id);

                        printf("Conectando no MangaDex@Home...\n");
                        MemoryBuffer res_pages = install_data_url(url_paginas);

                        if (res_pages.memory != NULL) {
                            PageList paginas = parse_pagelist_json(res_pages.memory);

                            if (paginas.page_count > 0) {
                                printf("\n[Servidor Alocado]: %s\n", paginas.base_url);
                                printf("[Total de Paginas]: %d\n", paginas.page_count);

                                const char *pasta_downloads = "capitulo_baixado";
                                if (!criar_pasta(pasta_downloads)) {
                                    printf("Erro fatal ao criar a pasta de downloads.\n");
                                    return 1;
                                }

                                printf("Iniciando download do capitulo para a pasta '%s'...\n", pasta_downloads);

                                for(int i = 0; i < paginas.page_count; i++) {
                                    char url_imagem[512];
                                    snprintf(url_imagem, sizeof(url_imagem), "%s/data/%s/%s",
                                        paginas.base_url, paginas.chapter_hash, paginas.page_filenames[i]);

                                    char caminho_local[256];
                                    snprintf(caminho_local, sizeof(caminho_local), "%s/%03d.jpg", pasta_downloads, i+1);

                                    printf("Baixando pagina %d de %d... ", i+1, paginas.page_count);
                                    fflush(stdout);

                                    if (install_files(url_imagem, caminho_local)) {
                                        printf("[OK]\n");
                                    } else {
                                        printf("[FALHA]\n");
                                    }
                                }

                                printf("\n=== DOWNLOAD CONCLUIDO ===\n");
                                ler_manga(pasta_downloads);
                                limpar_pasta_downloads(pasta_downloads);
                                printf("Leitura finalizada e HD limpo.\n");

                            } else {
                                printf("\n[AVISO DA API] Nenhuma pagina encontrada para este capitulo!\n");
                                printf("-> Motivo provavel: O MangaDex nao hospeda este capitulo diretamente.\n");
                            }
                            destruct_page_list(&paginas);
                        }
                        clear_buffer(&res_pages);
                    } else {
                        printf("\nOpcao invalida. O numero digitado nao existe na lista.\n");
                    }
                } else {
                    printf("\nNenhum capitulo encontrado para este manga!\n");
                }

                destruct_chapter_list(&lista);
            }
            clear_buffer(&res_caps);
            destruct_manga(manga);
        }
    }
    printf("\nMemoria limpa. Encerrando programa.\n");
    return 0;
}