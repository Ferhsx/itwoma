# 📚 ITWOMA - I'm Tired Of Web Manga Ads

Um cliente de linha de comando (CLI) eficiente e sem anúncios para buscar, baixar e ler mangás diretamente do [MangaDex](https://mangadex.org/). Desenvolvido em C com integração completa à API oficial do MangaDex.

> *"Is this better? Cleaner?" - ITWOMA, removing ads like it's Arcane removing Chem-barons* 🌟

![Status](https://img.shields.io/badge/status-active-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-green)

---

## 🎯 Características

- ✅ **Busca em tempo real** de mangás pelo título usando a API oficial do MangaDex
- ✅ **Suporte multilíngue** - Baixe capítulos em português, inglês e outros idiomas
- ✅ **Download automático** de capítulos completos em alta qualidade
- ✅ **Visualizador integrado** - Abre as páginas automaticamente no visualizador padrão
- ✅ **Limpeza automática** de arquivos após a leitura
- ✅ **Interface intuitiva** e fácil de usar
- ✅ **Sem anúncios** - Experiência limpa e rápida
- ✅ **Multiplataforma** - Funciona em Linux, macOS e Windows

---

## 📋 Pré-requisitos

### Dependências do Sistema

Antes de compilar o projeto, certifique-se de ter instalado:

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libcurl4-openssl-dev
```

**macOS (com Homebrew):**
```bash
brew install cmake curl
```

**Windows:**
- Instale o [CMake](https://cmake.org/download/) (versão 3.28 ou superior)
- Instale o [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) ou MinGW
- Instale o [libcurl](https://curl.se/download.html)

### Requisitos Técnicos

- **CMake** ≥ 3.28
- **Compilador C** com suporte a C11 (gcc, clang, MSVC)
- **libcurl** (desenvolvimento)

---

## 🚀 Instalação e Compilação (The Cycle Continues - Evangelion AT Fields of Build Systems)

### 1. Clonar o Repositório

```bash
git clone https://github.com/Ferhsx/itwoma.git
cd itwoma
```

### 2. Configurar o Build com CMake

```bash
mkdir -p build
cd build
cmake ..
```

### 3. Compilar o Projeto

```bash
make
```

Ou, alternadamente:
```bash
cmake --build .
```

### 4. Executar o Programa

```bash
./itwoma
```

---

## 💻 Como Usar

### Iniciar o Programa

```bash
./itwoma
```

### Fluxo de Uso (Decode the Protocol - Like Jinx :p)

1. **Selecione o idioma** de preferência para os capítulos (Português ou Inglês)
2. **Digite o nome do mangá** que deseja buscar
3. **Escolha o capítulo** desejado da lista exibida
4. O programa irá:
   - Conectar ao servidor MangaDex@Home
   - Baixar todas as páginas do capítulo
   - Abrir automaticamente em seu visualizador padrão
   - Limpar os arquivos após a leitura

### Exemplo de Uso

```
=== ITWOMA (I'm Tired Of Web Manga Ads) ===

Escolha o idioma de preferencia para os capitulos:
[1] Portugues (pt-br)
[2] Ingles (en)
Opcao: 1
Idioma configurado para: pt-br

======================================================
Digite o nome do manga (ou digite 'sair' para fechar): Attack on Titan

Procurando por 'Attack on Titan'...

>> Manga Encontrado: Shingeki no Kyojin

--- CAPITULOS DISPONIVEIS ---
[0] Cap: 1 - COLOSSUS
[1] Cap: 2 - That Day
...
-----------------------------

Digite o numero entre colchetes [ ] do capitulo que deseja ler: 0
```

### Comando para Sair

Digite `sair` quando solicitado o nome do mangá para fechar o programa.

---

## 📁 Estrutura do Projeto (The Perfect Hierarchy - God of War's Yggdrasil would be proud)

```
itwoma/
├── CMakeLists.txt              # Configuração de build
├── README.md                   # Este arquivo
├── .gitignore                  # Arquivos a ignorar no git
├── build/                      # Diretório de build (gerado)
├── include/                    # Headers (.h)
│   ├── manga.h                 # Estruturas de dados para mangás
│   ├── http_client.h           # Cliente HTTP com libcurl
│   ├── parser.h                # Parser JSON (cJSON)
│   └── utils.h                 # Utilitários gerais
├── lib/                        # Bibliotecas externas
│   └── cJSON/                  # Parser JSON (incluído)
│       ├── cJSON.c
│       └── cJSON.h
└── src/                        # Código-fonte
    ├── main.c                  # Ponto de entrada e lógica principal
    ├── manga.c                 # Implementação de estruturas de mangá
    ├── http_client.c           # Implementação do cliente HTTP
    ├── parser.c                # Parser JSON
    ├── utils.c                 # Funções utilitárias
    └── capitulo_baixado/       # Pasta temporária de downloads
```

### Descrição dos Módulos

| Arquivo | Responsabilidade |
|---------|------------------|
| `main.c` | Interface de usuário, fluxo principal da aplicação |
| `http_client.c` | Requisições HTTP à API do MangaDex |
| `parser.c` | Parsing de respostas JSON |
| `manga.c` | Gerenciamento de estruturas de dados de mangás |
| `utils.c` | Funções utilitárias (pasta, visualização, limpeza) |
| `cJSON.c` | Biblioteca JSON (dependência externa) |

---

## 🔧 Troubleshooting (Domain Expansion Required)

### Erro: "cmake: command not found"
**Solução:** Instale o CMake
```bash
sudo apt-get install cmake      # Linux
brew install cmake              # macOS
```

### Erro: "libcurl not found"
**Solução:** Instale libcurl-dev
```bash
sudo apt-get install libcurl4-openssl-dev   # Linux
brew install curl                            # macOS
```

### Erro: "Compilador C não encontrado"
**Solução:** Instale as ferramentas de build
```bash
sudo apt-get install build-essential         # Linux (gcc)
xcode-select --install                       # macOS (clang)
```

### Problema: "Nenhum capítulo encontrado para este manga"
**Possíveis causas:**
- O MangaDex não hospeda tradução nesse idioma
- O mangá não existe na plataforma
- Problema de conexão com a API
- Tente novamente em alguns minutos

### Problema: "Falha no download de imagens"
**Possíveis causas:**
- Conexão de internet instável
- Servidor MangaDex indisponível
- Capítulo foi removido da plataforma
- Tente novamente mais tarde

### Problema: "Pasta de downloads não foi criada"
**Solução:** Verifique permissões de escrita no diretório atual
```bash
ls -ld .
chmod u+w .
```

---

## 🌐 API do MangaDex

Este projeto utiliza a **API oficial v5 do MangaDex** (v2):

- **Endpoint de Busca:** `https://api.mangadex.org/manga`
- **Endpoint de Capítulos:** `https://api.mangadex.org/manga/{id}/feed`
- **Endpoint de Páginas:** `https://api.mangadex.org/at-home/server/{id}`

Para mais informações: [Documentação da API MangaDex](https://api.mangadex.org)

---

## 📝 Licença

Este projeto está sob a licença **MIT**. Veja o arquivo [LICENSE](LICENSE) para detalhes.

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Para contribuir:

1. **Fork** o repositório
2. **Crie uma branch** para sua feature (`git checkout -b feature/AmazingFeature`)
3. **Commit** suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. **Push** para a branch (`git push origin feature/AmazingFeature`)
5. **Abra um Pull Request**

### Diretrizes para Contribuições

- Mantenha a compatibilidade com C11
- Adicione comentários em código complexo
- Teste em múltiplos ambientes se possível
- Siga o estilo de código existente
- Atualize este README se adicionar novas features

---

## 📞 Suporte

Se encontrar problemas ou tiver sugestões:

- **Abra uma Issue** no repositório
- **Envie um Pull Request** com a solução
- Consulte a seção [Troubleshooting](#-troubleshooting)

---

## 🔐 Aviso Legal

Este projeto é um cliente não-oficial do MangaDex. Respeite os termos de serviço do MangaDex e use responsavelmente. O autor não se responsabiliza pelo uso inadequado deste software.


---

## 🎓 Aprendizados Principais (Knowledge is Power)

Este projeto demonstra:

- ✅ Integração com APIs REST em C puro
- ✅ Parsing de JSON com cJSON
- ✅ Requisições HTTP com libcurl
- ✅ Build system moderno com CMake
- ✅ Gerenciamento de memória em C
- ✅ Desenvolvimento multiplataforma
- ✅ Boas práticas de CLI

---

**Desenvolvido com [L.O.V.E] (sim uma referência a undertale) por [Ferhsx](https://github.com/Ferhsx)**

> *"It's dangerous to go alone!" - But with this documentation, you won't be.*

*Última atualização: 20 de Maio de 2026* (With Easter Eggs Sprinkled Throughout )
