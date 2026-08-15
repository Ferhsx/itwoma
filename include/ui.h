#ifndef UI_H
#define UI_H

#include "manga.h"

void exibir_banner(void);
void configurar_idioma(char *lang_code, size_t max_len);
Manga* buscar_manga_interativo(void);
Chapter* selecionar_capitulo_interativo(const Manga *manga, const char *lang_code);
void baixar_e_ler_capitulo(const Chapter *capitulo);

#endif