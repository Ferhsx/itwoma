#include <stdio.h>
#include <sys/stat.h> // Biblioteca do Linux
#include <stdlib.h>
#include "../include/utils.h"

#ifdef _WIN32
    #include <direct.h> // Biblioteca nativa do Windows para diretórios
#endif

int criar_pasta(const char *caminho) {
    int status;

#ifdef _WIN32
    status = _mkdir(caminho); // Jeito Windows
#else
    status = mkdir(caminho, 0777); // Jeito Linux/Mac
#endif

    if (status == 0) {
        return 1; // Sucessfolei
    } else {
        struct stat st = {0};
        if (stat(caminho, &st) == 0) {

#ifdef _WIN32
            if (st.st_mode & _S_IFDIR) return 1; // Verifica no Windows
#else
            if (S_ISDIR(st.st_mode)) return 1;   // Verifica no Linux/Mac
#endif
        }
        return 0;
    }
}

void ler_manga(const char *caminho_pasta) {
    printf("\nAbrindo o leitor de manga...\n");

#ifdef _WIN32
    char comando[512];
    // explorer.exe abre a pasta nativamente no Windows
    snprintf(comando, sizeof(comando), "explorer.exe \"%s\"", caminho_pasta);
    system(comando);

    printf("\n[MODO WINDOWS]\n");
    printf("A pasta com as paginas foi aberta em uma nova janela.\n");
    printf(">> Pressione ENTER nesta tela preta quando terminar de ler para limpar o HD...");

    // Limpa o buffer do teclado e pausa o programa esperando o Enter
    fflush(stdin);
    getchar();
#else
    char comando[512];
    // O comando 'start' abre pastas, URLs e arquivos nativamente no CMD do Windows de forma segura
    snprintf(comando, sizeof(comando), "start \"\" \"%s\"", caminho_pasta);
    system(comando);
#endif
}

void limpar_pasta_downloads(const char *caminho_pasta) {
    printf("\nLimpando os arquivos temporarios no HD...\n");
    char comando[512];

#ifdef _WIN32
    // Comando do CMD do Windows para deletar pasta
    snprintf(comando, sizeof(comando), "rmdir /s /q \"%s\"", caminho_pasta);
#else
    // Comando do terminal Linux para deletar pasta
    snprintf(comando, sizeof(comando), "rm -rf \"%s\"", caminho_pasta);
#endif

    system(comando);
}