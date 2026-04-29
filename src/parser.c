#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../lib/cJSON/cJSON.h"

Manga* parse_manga_json(const char *json_string) {
    cJSON *json_root = cJSON_Parse(json_string);
    if (json_root == NULL) {
        printf("[DEBUG] Falha ao decodificar o texto. Nao e um JSON valido.\n");
        return NULL;
    }

    cJSON *data_array = cJSON_GetObjectItemCaseSensitive(json_root, "data");
    if (!cJSON_IsArray(data_array) || cJSON_GetArraySize(data_array) == 0) {
        printf("[DEBUG] Nenhum resultado na array 'data'.\n");
        cJSON_Delete(json_root);
        return NULL;
    }

    cJSON *primeiro_manga = cJSON_GetArrayItem(data_array, 0);
    cJSON *id_node = cJSON_GetObjectItemCaseSensitive(primeiro_manga, "id");
    cJSON *attributes = cJSON_GetObjectItemCaseSensitive(primeiro_manga, "attributes");
    cJSON *title_node = cJSON_GetObjectItemCaseSensitive(attributes, "title");
    
    cJSON *first_title = (title_node != NULL) ? title_node->child : NULL;

    Manga *meu_manga_limpo = NULL;

    if (cJSON_IsString(id_node) && cJSON_IsString(first_title)) {
        meu_manga_limpo = creat_manga(id_node->valuestring, first_title->valuestring);
    } else {
        printf("[DEBUG] Falha ao extrair ID ou Titulo dos atributos do JSON.\n");
    }

    cJSON_Delete(json_root);
    return meu_manga_limpo;
}

ChapterList parse_chapters_json(const char *json_string) {
    ChapterList lista;
    lista.chapters = NULL;
    lista.count = 0;

    cJSON *json_root = cJSON_Parse(json_string);
    if (json_root == NULL) return lista;

    cJSON *data_array = cJSON_GetObjectItemCaseSensitive(json_root, "data");
    if (!cJSON_IsArray(data_array)) {
        cJSON_Delete(json_root);
        return lista;
    }

    int total_capitulos = cJSON_GetArraySize(data_array);
    lista.count = total_capitulos;

    lista.chapters = (Chapter**) malloc(total_capitulos * sizeof(Chapter*));

    for (int i = 0; i < total_capitulos; i++) {
        cJSON *item = cJSON_GetArrayItem(data_array, i);
        
        cJSON *id_node = cJSON_GetObjectItemCaseSensitive(item, "id");
        cJSON *attributes = cJSON_GetObjectItemCaseSensitive(item, "attributes");
        
        cJSON *chapter_node = cJSON_GetObjectItemCaseSensitive(attributes, "chapter");
        cJSON *title_node = cJSON_GetObjectItemCaseSensitive(attributes, "title");

        // Extrai os textos (lidando com campos que podem vir vazios na API)
        const char *id_str = cJSON_IsString(id_node) ? id_node->valuestring : "";
        const char *cap_num_str = cJSON_IsString(chapter_node) ? chapter_node->valuestring : NULL;
        const char *titulo_str = cJSON_IsString(title_node) ? title_node->valuestring : NULL;

        // Cria o capítulo e guarda no nosso array
        lista.chapters[i] = creat_chapter(id_str, cap_num_str, titulo_str);
    }

    cJSON_Delete(json_root);
    return lista;
}