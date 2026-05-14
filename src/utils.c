#include <stdio.h>
#include <sys/stat.h> // Biblioteca do Linux
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