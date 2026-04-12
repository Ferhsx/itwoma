#include <stdio.h>
#include "../include/manga.h"

int main(void) {
//abobura, so um inicio, não vou levar nada a serio ainda ><....><

    printf("=== ITWOMA (I'm Tired Of Web Manga Ads) ===\n\n");
    Manga m;

    m.title = "Vagabond";
    m.id = "d1a15d2b-f838-4e97-b412-4d275eb65b0f";

    printf("Manga carregado com sucesso:\n");
    printf("titulo do manga: %s\n", m.title);
    printf("hash ID: %s\n", m.id);

    return 0;
}
