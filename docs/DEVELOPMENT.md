# 🔬 Guia de Desenvolvimento 

Documentação técnica para desenvolvedores que desejam entender e estender o ITWOMA.

## 📚 Arquitetura Geral 

```
┌─────────────────────────────────────────────┐
│         Interface do Usuário (main.c)       │
├─────────────────────────────────────────────┤
│                                             │
│  ┌──────────────┐      ┌──────────────┐    │
│  │ HTTP Client  │──────│   Parser     │    │
│  │              │      │ (cJSON)      │    │
│  └──────────────┘      └──────────────┘    │
│         │                      │            │
│         └──────────┬───────────┘            │
│                    │                       │
│         ┌──────────▼─────────┐             │
│         │  Manga Structures  │             │
│         └────────────────────┘             │
│                    │                       │
│         ┌──────────▼──────────┐            │
│         │  Utils (Save/View)  │            │
│         └─────────────────────┘            │
│                                             │
└─────────────────────────────────────────────┘
```

## 🗂️ Módulos Principais

### 1. **main.c** - Orquestrador Principal

**Responsabilidade:** Lógica de interface com o usuário e fluxo da aplicação.

**Funções principais:**
- Loop principal de interface
- Seleção de idioma
- Busca de mangá
- Seleção de capítulo
- Chamada dos módulos subordinados

**Fluxo:**
```
Início
  ├─> Selecionar idioma
  ├─> Loop de busca
  │   ├─> Buscar mangá (http_client + parser)
  │   ├─> Listar capítulos (http_client + parser)
  │   ├─> Selecionar capítulo
  │   ├─> Buscar páginas (http_client + parser)
  │   ├─> Baixar imagens (http_client + utils)
  │   ├─> Visualizar (utils)
  │   └─> Limpar (utils)
  └─> Fim
```

### 2. **http_client.c** - Cliente HTTP

**Responsabilidade:** Todas as requisições HTTP à API do MangaDex.

**Estrutura `MemoryBuffer`:**
```c
typedef struct {
    char *memory;      // Dados recebidos
    size_t size;       // Tamanho dos dados
} MemoryBuffer;
```

**Funções principais:**

```c
// Fazer requisição e retornar dados em memória
MemoryBuffer install_data_url(const char *url);

// Fazer requisição e salvar em arquivo
int install_files(const char *url, const char *caminho_destino);

// Liberar memória do buffer
void clear_buffer(MemoryBuffer *buffer);
```

**Callback Interno (não exportado):**
```c
// Função callback do libcurl para receber dados
static size_t WriteMemoryCallback(void *contents, size_t size,
                                  size_t nmemb, void *userp);
```

**Exemplo de Uso:**
```c
// Buscar dados
MemoryBuffer response = install_data_url("https://api.mangadex.org/manga?title=One%20Piece");

if (response.memory != NULL) {
    // Processar resposta
    printf("Recebido %zu bytes\n", response.size);
    
    // Liberar
    clear_buffer(&response);
}
```

### 3. **parser.c** - Parser JSON

**Responsabilidade:** Extrair informações JSON das respostas da API.

**Estruturas usadas (do manga.h):**

```c
typedef struct {
    char *id;                    // ID único do mangá
    char *title;                 // Título do mangá
} Manga;

typedef struct {
    char *id;                    // ID do capítulo
    char *chapter_number;        // Número do capítulo
    char *title;                 // Título do capítulo
} Chapter;

typedef struct {
    Chapter **chapters;          // Array de ponteiros
    size_t count;                // Quantidade de capítulos
} ChapterList;

typedef struct {
    char *base_url;              // URL base do servidor
    char *chapter_hash;          // Hash do capítulo
    char **page_filenames;       // Array de nomes de arquivos
    int page_count;              // Total de páginas
} PageList;
```

**Funções de Parsing:**

```c
// Fazer parse da resposta de busca de mangá
Manga* parse_manga_json(const char *json_string);

// Fazer parse da resposta de capítulos
ChapterList parse_chapters_json(const char *json_string);

// Fazer parse da resposta de páginas
PageList parse_pagelist_json(const char *json_string);
```

**Exemplo:**
```c
MemoryBuffer response = install_data_url(url);
ChapterList chapters = parse_chapters_json(response.memory);

for (size_t i = 0; i < chapters.count; i++) {
    printf("Capítulo %s: %s\n", 
           chapters.chapters[i]->chapter_number,
           chapters.chapters[i]->title);
}

destruct_chapter_list(&chapters);
```

### 4. **manga.c** - Gerenciamento de Estruturas

**Responsabilidade:** Criar e destruir estruturas de dados.

**Construtores:**
```c
Chapter* creat_chapter(const char* id, 
                       const char* chapter_number, 
                       const char* title);

Manga* creat_manga(const char* id, 
                   const char* title);

PageList creat_pagelist(int count);
```

**Destrutores:**
```c
void destruct_chapter_list(ChapterList* lista);
void destruct_manga(Manga* m);
void destruct_page_list(PageList* lista);
```

**Nota:** Sempre libere as estruturas para evitar vazamento de memória!

### 5. **utils.c** - Funções Utilitárias (The Titan's Duty - Attack on Titan aesthetic 🗡️)

**Responsabilidade:** Operações de sistema e formatação.

**Funções principais:**

```c
// Criar pasta recursivamente (multiplataforma)
int criar_pasta(const char *caminho);

// Abrir mangá no visualizador padrão
void ler_manga(const char *caminho_pasta);

// Limpar pasta após leitura
void limpar_pasta_downloads(const char *caminho_pasta);

// Formatar texto para ser usado em URL
void formatar_texto_url(char *texto_destino, 
                        const char *texto_origem);
```

**Comportamento Multiplataforma:**

| Função | Linux | macOS | Windows |
|--------|-------|-------|---------|
| `criar_pasta` | `mkdir -p` | `mkdir -p` | `mkdir` |
| `ler_manga` | `xdg-open` | `open` | `start` |
| `limpar_pasta` | `rm -rf` | `rm -rf` | `rmdir /s` |

## 🔌 Integração com Dependências (Like AT's Piano - Evangelion style)

### libcurl

Usada para requisições HTTP:

```c
#include <curl/curl.h>

// No http_client.c
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, url);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
curl_easy_perform(curl);
curl_easy_cleanup(curl);
```

### cJSON

Usada para parsing JSON:

```c
#include "../lib/cJSON/cJSON.h"

// No parser.c
cJSON *json = cJSON_Parse(json_string);
cJSON *item = cJSON_GetObjectItem(json, "data");
// ... extrair dados
cJSON_Delete(json);
```

## 📡 API do MangaDex (v5)

### Endpoints Usados

#### 1. Busca de Mangá
```
GET https://api.mangadex.org/manga?title={query}&limit=1&order[relevance]=desc

Resposta:
{
  "data": [{
    "id": "uuid",
    "attributes": {
      "title": {"en": "Manga Title"}
    }
  }]
}
```

#### 2. Listagem de Capítulos
```
GET https://api.mangadex.org/manga/{id}/feed?translatedLanguage[]={lang}&limit=20&order[chapter]=asc

Resposta:
{
  "data": [{
    "id": "chapter-uuid",
    "attributes": {
      "chapter": "1",
      "title": "Chapter Title"
    }
  }]
}
```

#### 3. Servidor de Páginas
```
GET https://api.mangadex.org/at-home/server/{chapter_id}

Resposta:
{
  "baseUrl": "https://server-url",
  "chapter": {
    "hash": "abcd1234",
    "data": ["001.jpg", "002.jpg", ...]
  }
}
```

## 🧪 Checklist para Adicionar Novas Features

1. **Planeje a feature:**
   - Qual módulo afeta?
   - Precisa de novas estruturas de dados?
   - Como se integra com modules existentes?

2. **Implemente:**
   - Siga o estilo de código existente
   - Adicione comentários onde necessário
   - Gerencie memória corretamente

3. **Teste:**
   - Compile sem warnings: `make VERBOSE=1`
   - Teste em múltiplas plataformas
   - Verifique vazamento de memória com valgrind

4. **Documente:**
   - Atualize cabeçalhos das funções
   - Adicione exemplos se aplicável
   - Atualize este arquivo

## 🔎 Verificação de Qualidade

### Compilar com Warnings
```bash
cd build
cmake .. -DCMAKE_C_FLAGS="-Wall -Wextra -pedantic"
make
```

### Verificar Vazamento de Memória (Linux)
```bash
valgrind --leak-check=full --show-leak-kinds=all ./itwoma
```

### Formatar Código (opcional)
```bash
clang-format -i src/*.c include/*.h
```

## 🔍 Debug e Logging

### Adicionar Debug Prints

```c
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stderr, "[DEBUG] " fmt "\n", __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

// Uso
DEBUG_PRINT("Búffer recebido: %zu bytes", response.size);
```

### Compilar com Debug
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

## 📚 Referências Úteis

- [Documentação libcurl](https://curl.se/libcurl/c/)
- [cJSON no GitHub](https://github.com/DaveGamble/cJSON)
- [API MangaDex](https://api.mangadex.org)
- [Especificação C11](https://en.cppreference.com/w/c/11)

## 🎯 Próximas Melhorias

- [ ] Adicionar testes unitários
- [ ] Criar função para favoritos
- [ ] Implementar cache local
- [ ] Suporte para múltiplos formatos (CBZ, EPUB)
- [ ] Melhorar tratamento de erros
- [ ] Adicionar logs estruturados

---

**Dúvidas? Abra uma issue ou PR!** 🚀

*Built with passion and a little bit of chaotic energy* ✨
