#include <stdio.h>
#include "../include/ui.h"
#include "../include/manga.h"

int main() {
    exibir_banner();

    char lang_code[10];
    configurar_idioma(lang_code, sizeof(lang_code));

    while (1) {
        printf("======================================================\n");
        Manga *manga = buscar_manga_interativo();
        if (manga == NULL) {
            printf("Saindo do ITWOMA... Ate a proxima leitura!\n");
            break;
        }

        Chapter *capitulo = selecionar_capitulo_interativo(manga, lang_code);
        if (capitulo != NULL) {
            baixar_e_ler_capitulo(capitulo);
            destruct_chapter(capitulo);
        }

        destruct_manga(manga);
        printf("\n");
    }

    printf("\nMemoria limpa. Encerrando programa.\n");
    return 0;
}