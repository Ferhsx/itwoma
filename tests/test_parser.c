#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/manga.h"

void test_formatar_url(void) {
    char buffer[100];
    formatar_texto_url(buffer, "One Piece\n");
    assert(strcmp(buffer, "One%20Piece") == 0);

    formatar_texto_url(buffer, "Chainsaw Man\r\n");
    assert(strcmp(buffer, "Chainsaw%20Man") == 0);

    printf("[PASS] test_formatar_url\n");
}

void test_parse_manga_valido(void) {
    const char *mock_json = "{\n"
        "  \"data\": [{\n"
        "    \"id\": \"mock-id-12345\",\n"
        "    \"attributes\": {\n"
        "      \"title\": {\"en\": \"Berserk Test\"}\n"
        "    }\n"
        "  }]\n"
        "}";

    Manga *manga = parse_manga_json(mock_json);

    assert(manga != NULL);
    assert(strcmp(manga->id, "mock-id-12345") == 0);
    assert(strcmp(manga->title, "Berserk Test") == 0);

    destruct_manga(manga); // Garante que a limpeza funciona
    printf("[PASS] test_parse_manga_valido\n");
}

void test_parse_manga_vazio(void) {
    const char *mock_json_vazio = "{\"data\": []}";

    Manga *manga = parse_manga_json(mock_json_vazio);
    assert(manga == NULL); // Deve retornar NULL com segurança

    printf("[PASS] test_parse_manga_vazio\n");
}

int main(void) {
    printf("=== EXECUTANDO TESTES UNITARIOS DO ITWOMA ===\n\n");
    test_formatar_url();
    test_parse_manga_valido();
    test_parse_manga_vazio();
    printf("\n>>> TODOS OS TESTES PASSARAM COM SUCESSO! <<<\n");
    return 0;
}