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

Chapter* creat_chapter(const char *id_texto, const char *numero_texto, const char *titulo_texto) {
    Chapter *novo_chapter = (Chapter*) malloc(sizeof(Chapter));
    
    novo_chapter->id = (char*) malloc(strlen(id_texto) + 1);
    strcpy(novo_chapter->id, id_texto);

    if (numero_texto != NULL) {
        novo_chapter->chapter_number = (char*) malloc(strlen(numero_texto) + 1);
        strcpy(novo_chapter->chapter_number, numero_texto);
    } else {
        novo_chapter->chapter_number = (char*) malloc(2);
        strcpy(novo_chapter->chapter_number, "-");
    }

    if (titulo_texto != NULL) {
        novo_chapter->title = (char*) malloc(strlen(titulo_texto) + 1);
        strcpy(novo_chapter->title, titulo_texto);
    } else {
        novo_chapter->title = (char*) malloc(2);
        strcpy(novo_chapter->title, "-");
    }
    
    return novo_chapter;
}

void destruct_chapter_list(ChapterList *lista) {
    if (lista != NULL && lista->chapters != NULL) {
        for (int i = 0; i < lista->count; i++) {
            Chapter *c = lista->chapters[i]; 

            free(c->id);
            free(c->chapter_number);
            free(c->title);
            free(c); 
        }
        // Depois de limpar todos os capítulos, limpamos a lista que guardava eles
        free(lista->chapters); 
        lista->chapters = NULL;
        lista->count = 0;
    }
}