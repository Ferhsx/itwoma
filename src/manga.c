#include <stdlib.h>
#include <string.h>
#include "../include/manga.h"

Manga* creat_manga(const char *id_texto, const char *titulo_texto) {
    Manga *novo_manga = (Manga*) malloc(sizeof(Manga));

    novo_manga->id = (char*) malloc(strlen(id_texto) + 1);
    strcpy(novo_manga->id, id_texto);
    novo_manga->title = (char*) malloc(strlen(titulo_texto) + 1);
    strcpy(novo_manga->title, titulo_texto);

    return novo_manga;
}

void destruct_manga(Manga *m) {
    if (m != NULL) {
        free(m->id);
        free(m->title);
        free(m);
    }
}