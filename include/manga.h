//
// Created by ferna on 12/04/2026.
//

#ifndef ITWOMA_MANGA_H
#define ITWOMA_MANGA_H

typedef struct {
    char *id;
    char *title;
} Manga;

Manga* creat_manga(const char* id, const char* title);
void destruct_manga(Manga* m);

#endif //ITWOMA_MANGA_H
