#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../lib/cJSON/cJSON.h"

Manga* parse_manga_json(const char *json_string){
    cJSON *json_root = cJSON_Parse(json_string);
    if(json_root==NULL){
        printf("ERRO: texto recebido nao e um json valido\n");
        return NULL;
    }

    cJSON *data_array = cJSON_GetObjectItemCaseSensitive(json_root, "data");
    if(!cJSON_IsArray(data_array) || cJSON_GetArraySize(data_array) == 0){
        printf("Erro: Nenhum manga na resposta.\n");
        cJSON_Delete(json_root);
    }

    cJSON *primeiro_manga = cJSON_GetArrayItem(data_array, 0);
    cJSON *id_node = cJSON_GetObjectItemCaseSensitive(primeiro_manga, "id");
    cJSON *attributes = cJSON_GetObjectItemCaseSensitive(primeiro_manga, "attributes");
    cJSON *title_node = cJSON_GetObjectItemCaseSensitive(attributes, "title");
    cJSON *title_en = cJSON_GetObjectItemCaseSensitive(title_node, "en");

    Manga *meu_manga_limpo = NULL;
    
    if (cJSON_IsString(id_node) && cJSON_IsString(title_en)) {
        meu_manga_limpo = creat_manga(id_node->valuestring, title_en->valuestring);
    }

    cJSON_Delete(json_root);

    return meu_manga_limpo;
}
