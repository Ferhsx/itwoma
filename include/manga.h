//
// Created by ferna on 12/04/2026.
//

#ifndef ITWOMA_MANGA_H
#define ITWOMA_MANGA_H

typedef struct {
    char *base_url;
    char *chapter_hash;
    char **page_filenames;
    int page_count;
} PageList;

typedef struct{
    char *id;
    char *chapter_number;
    char *title;
} Chapter;

typedef struct{
    Chapter **chapters;
    size_t count;
} ChapterList;

typedef struct {
    char *id;
    char *title;
} Manga;

Chapter* creat_chapter(const char* id, const char* chapter_number, const char* title);
void destruct_chapter_list(ChapterList* lista);

Manga* creat_manga(const char* id, const char* title);
void destruct_manga(Manga* m);

PageList creat_pagelist(int count);
void destruct_page_list(PageList* lista);

#endif //ITWOMA_MANGA_H