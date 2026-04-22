#include <stdio.h>
#include <stdlib.h>
#include "../include/parse.h"
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
//TODO:fazer a extração do id
}
