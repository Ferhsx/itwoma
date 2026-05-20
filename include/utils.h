#ifndef UTILS_H
#define UTILS_H

// Função para criar uma pasta no sistema operacional
int criar_pasta(const char *caminho);

// Função multiplataforma para ler o mangá
void ler_manga(const char *caminho_pasta);

// Função multiplataforma para apagar o HD
void limpar_pasta_downloads(const char *caminho_pasta);

void formatar_texto_url(char *texto_destino, const char *texto_origem);

#endif