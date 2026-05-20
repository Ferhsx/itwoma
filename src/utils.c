#include <stdio.h>
#include <sys/stat.h> // Biblioteca do Linux
#include <stdlib.h>
#include "../include/utils.h"
#include <string.h>

#ifndef _WIN32
    #include <unistd.h>
    #include <sys/select.h>
#endif

#ifdef _WIN32
    #include <direct.h> // Biblioteca nativa do Windows para diretórios
#endif

#ifndef _WIN32
static int stdin_has_data(void) {
    struct timeval tv = {0, 0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    return select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv) > 0;
}
#endif

static void esperar_enter_usuario(void) {
    int c;

#ifndef _WIN32
    if (stdin_has_data()) {
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
#endif

    printf(">> Pressione ENTER quando terminar de ler para limpar o HD...");
    fflush(stdout);
    while ((c = getchar()) != '\n' && c != EOF) {}
}

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

    struct stat st = {0};
    if (stat(caminho_pasta, &st) != 0 ||
#ifndef _WIN32
        !S_ISDIR(st.st_mode)
#else
        !(st.st_mode & _S_IFDIR)
#endif
    ) {
        printf("Erro: o caminho '%s' nao existe ou nao e um diretorio.\n", caminho_pasta);
        return;
    }

#ifdef _WIN32
    // --- MODO WINDOWS ---
    char comando[512];
    snprintf(comando, sizeof(comando), "start \"\" \"%s\"", caminho_pasta);
    system(comando);
    
    printf("\n[MODO WINDOWS]\n");
    printf("A pasta com as paginas foi aberta em uma nova janela.\n");
    printf("Abra a pasta manualmente se necessario.\n");
    esperar_enter_usuario();
#else
    // --- MODO LINUX ---
    if (getenv("DISPLAY") == NULL && getenv("WAYLAND_DISPLAY") == NULL) {
        printf("Nenhum ambiente grafico detectado. Abra a pasta '%s' manualmente.\n", caminho_pasta);
        esperar_enter_usuario();
        return;
    }

    char comando[512];
    snprintf(comando, sizeof(comando), "xdg-open \"%s\" >/dev/null 2>&1", caminho_pasta);
    if (system(comando) != 0) {
        printf("Nao foi possivel abrir o leitor automaticamente. Abra a pasta '%s' manualmente.\n", caminho_pasta);
    }

    esperar_enter_usuario();
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

void formatar_texto_url(char *texto_destino, const char *texto_origem) {
    int i = 0, j = 0;
    while (texto_origem[i] != '\0') {
        // Remove a quebra de linha do ENTER
        if (texto_origem[i] == '\n' || texto_origem[i] == '\r') {
            i++;
            continue;
        }
        // Troca ESPAÇO por %20
        if (texto_origem[i] == ' ') {
            texto_destino[j++] = '%';
            texto_destino[j++] = '2';
            texto_destino[j++] = '0';
        } else {
            texto_destino[j++] = texto_origem[i];
        }
        i++;
    }
    texto_destino[j] = '\0'; // Fecha a string corretamente
}