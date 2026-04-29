#ifndef PARSER_H
#define PARSER_H

#include "manga.h"
Manga* parse_manga_json(const char *json_string);

ChapterList parse_chapters_json(const char *json_string);

#endif
