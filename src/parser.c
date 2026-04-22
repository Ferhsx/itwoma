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