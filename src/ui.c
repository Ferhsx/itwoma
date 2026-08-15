#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/http_client.h"
#include "../include/parser.h"
#include "../include/utils.h"

void exibir_banner(void) {
    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");
}

void configurar_idioma(char *lang_code, size_t max_len) {
    strncpy(lang_code, "en", max_len);

    printf("Escolha o idioma de preferencia para os capitulos:\n");
    printf("[1] Portugues (pt-br)\n");
    printf("[2] Ingles (en)\n");
    printf("Opcao: ");

    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (buffer[0] == '1') {
            strncpy(lang_code, "pt-br", max_len);
        } else if (buffer[0] == '2') {
            strncpy(lang_code, "en", max_len);
        } else {
            printf("Opcao invalida. Usando Ingles (en) como padrao.\n");
        }
    }
    printf("Idioma configurado para: %s\n\n", lang_code);
}

Manga* buscar_manga_interativo(void) {
    char nome_digitado[100];
    printf("Digite o nome do manga (ou digite 'sair' para fechar): ");

    if (fgets(nome_digitado, sizeof(nome_digitado), stdin) == NULL) return NULL;
    if (strncmp(nome_digitado, "sair", 4) == 0) return NULL;

    char nome_formatado[300];
    formatar_texto_url(nome_formatado, nome_digitado);
    if (strlen(nome_formatado) == 0) return NULL;

    char url_manga[512];
    snprintf(url_manga, sizeof(url_manga),
             "https://api.mangadex.org/manga?title=%s&limit=1&order[relevance]=desc",
             nome_formatado);

    printf("\nProcurando por '%s'...\n", nome_digitado);

    MemoryBuffer res = install_data_url(url_manga);
    if (res.memory == NULL) {
        fprintf(stderr, "Erro de conexao ao buscar manga.\n");
        return NULL;
    }

    Manga *manga = parse_manga_json(res.memory);
    clear_buffer(&res);

    if (manga == NULL) {
        printf("Aviso: Nenhum manga encontrado.\n");
        return NULL;
    }

    printf("\n>> Manga Encontrado: %s\n", manga->title);
    return manga;
}

Chapter* selecionar_capitulo_interativo(const Manga *manga, const char *lang_code) {
    if (manga == NULL || manga->id == NULL) return NULL;

    char url_capitulos[256];
    snprintf(url_capitulos, sizeof(url_capitulos),
             "https://api.mangadex.org/manga/%s/feed?translatedLanguage[]=%s&limit=20&order[chapter]=asc",
             manga->id, lang_code);

    printf("\nBuscando capitulos...\n");
    MemoryBuffer res = install_data_url(url_capitulos);
    if (res.memory == NULL) {
        fprintf(stderr, "Erro de conexao ao buscar capitulos.\n");
        return NULL;
    }

    ChapterList lista = parse_chapters_json(res.memory);
    clear_buffer(&res);

    if (lista.count == 0 || lista.chapters == NULL) {
        printf("\nNenhum capitulo encontrado para este manga no idioma selecionado!\n");
        destruct_chapter_list(&lista);
        return NULL;
    }

    printf("\n--- CAPITULOS DISPONIVEIS ---\n");
    for (size_t i = 0; i < lista.count; i++) {
        printf("[%zu] Cap: %s - %s\n", i,
               lista.chapters[i]->chapter_number,
               lista.chapters[i]->title);
    }
    printf("-----------------------------\n");

    printf("\nDigite o numero entre colchetes [ ] do capitulo: ");
    char buffer[10];
    int escolha = -1;
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        escolha = atoi(buffer);
    }

    Chapter *escolhido = NULL;
    if (escolha >= 0 && (size_t)escolha < lista.count) {
        Chapter *temp = lista.chapters[escolha];
        escolhido = creat_chapter(temp->id, temp->chapter_number, temp->title);
    } else {
        printf("\nOpcao invalida. O numero digitado nao existe na lista.\n");
    }

    destruct_chapter_list(&lista);
    return escolhido;
}

void baixar_e_ler_capitulo(const Chapter *capitulo) {
    if (capitulo == NULL || capitulo->id == NULL) return;

    printf("\n==========================================\n");
    printf("LENDO O CAPITULO: %s - %s\n", capitulo->chapter_number, capitulo->title);
    printf("==========================================\n");

    char url_paginas[256];
    snprintf(url_paginas, sizeof(url_paginas),
             "https://api.mangadex.org/at-home/server/%s", capitulo->id);

    printf("Conectando no MangaDex@Home...\n");
    MemoryBuffer res = install_data_url(url_paginas);
    if (res.memory == NULL) return;

    PageList paginas = parse_pagelist_json(res.memory);
    clear_buffer(&res);

    if (paginas.page_count <= 0 || paginas.base_url == NULL) {
        printf("\n[AVISO DA API] Nenhuma pagina encontrada para este capitulo!\n");
        printf("-> Motivo provavel: Link oficial externo (MangaPlus) ou capitulo indisponivel.\n");
        destruct_page_list(&paginas);
        return;
    }

    printf("\n[Servidor Alocado]: %s\n", paginas.base_url);
    printf("[Total de Paginas]: %d\n", paginas.page_count);

    const char *pasta = "capitulo_baixado";
    if (!criar_pasta(pasta)) {
        printf("Erro fatal ao criar a pasta de downloads.\n");
        destruct_page_list(&paginas);
        return;
    }

    printf("Iniciando download do capitulo para a pasta '%s'...\n", pasta);
    for (int i = 0; i < paginas.page_count; i++) {
        char url_imagem[512];
        snprintf(url_imagem, sizeof(url_imagem), "%s/data/%s/%s",
                 paginas.base_url, paginas.chapter_hash, paginas.page_filenames[i]);

        char caminho_local[256];
        snprintf(caminho_local, sizeof(caminho_local), "%s/%03d.jpg", pasta, i + 1);

        printf("Baixando pagina %d de %d... ", i + 1, paginas.page_count);
        fflush(stdout);

        if (install_files(url_imagem, caminho_local)) {
            printf("[OK]\n");
        } else {
            printf("[FALHA]\n");
        }
    }

    printf("\n=== DOWNLOAD CONCLUIDO ===\n");
    ler_manga(pasta);
    limpar_pasta_downloads(pasta);
    printf("Leitura finalizada e HD limpo.\n");

    destruct_page_list(&paginas);
}