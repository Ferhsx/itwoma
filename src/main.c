#include <stdio.h>
#include "../include/manga.h"

int main() {
    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");

    Manga *meu_manga = creat_manga("d1a15d2b-f838...", "Vagabond");

    printf("Manga carregado dinamicamente:\n");
    printf("Titulo: %s\n", meu_manga->title);

    destruct_manga(meu_manga);

    printf("\nMemoria limpa com sucesso. Encerrando...\n");
    return 0;
}