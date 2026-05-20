# ❓ Perguntas Frequentes (FAQ) (Ask and ye shall receive)

## 🔧 Instalação e Compilação

### P: Como instalo no Ubuntu?
R: 
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libcurl4-openssl-dev
git clone https://github.com/Ferhsx/itwoma.git
cd itwoma && mkdir build && cd build
cmake .. && make
./itwoma
```

### P: Como instalo no macOS?
R:
```bash
brew install cmake curl
git clone https://github.com/Ferhsx/itwoma.git
cd itwoma && mkdir build && cd build
cmake .. && make
./itwoma
```

### P: Onde fica o executável?
R: Em `build/itwoma` (Linux/macOS) ou `build/Release/itwoma.exe` (Windows)

### P: Posso instalar globalmente?
R:
```bash
cd build
sudo make install  # Instala em /usr/local/bin
itwoma  # Agora pode chamar de qualquer lugar
```

---

## ⚠️ Problemas Comuns

### P: "cmake: command not found"
R: Instale o CMake:
- Ubuntu: `sudo apt-get install cmake`
- macOS: `brew install cmake`
- Windows: Baixe em https://cmake.org/download/

### P: "libcurl not found"
R: Instale libcurl-dev:
- Ubuntu: `sudo apt-get install libcurl4-openssl-dev`
- macOS: `brew install curl`
- Windows: Baixe em https://curl.se/download.html

### P: "Compilador não encontrado"
R: Instale ferramentas de build:
- Ubuntu: `sudo apt-get install build-essential`
- macOS: `xcode-select --install`
- Windows: Instale Visual Studio Build Tools

### P: Erro ao clonar do GitHub
R: Verifique sua conexão ou use HTTPS em vez de SSH:
```bash
git clone https://github.com/Ferhsx/itwoma.git
# em vez de:
# git clone git@github.com:Ferhsx/itwoma.git
```

### P: Segmentation fault ao executar
R: Pode ser problema de memória. Tente:
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
gdb ./itwoma
(gdb) run
```

---

## 🎮 Uso e Funcionalidades 

### P: Quais idiomas são suportados?
R: Atualmente:
- Português (pt-br)
- Inglês (en)

Novos idiomas podem ser adicionados editando `main.c` e a API.

### P: Posso baixar múltiplos capítulos?
R: Não automaticamente, mas você pode:
1. Executar o programa várias vezes
2. Mover a pasta `capitulo_baixado` antes de baixar o próximo
3. Ver [PROJECT_ANALYSIS.md](PROJECT_ANALYSIS.md) para melhorias planejadas

### P: Onde os capítulos são salvos?
R: Em uma pasta chamada `capitulo_baixado` no diretório atual.

### P: Os arquivos são deletados automaticamente?
R: Sim, após a leitura, a pasta é limpa.

### P: Posso usar um visualizador diferente?
R: Atualmente usa o visualizador padrão do SO:
- Linux: `xdg-open`
- macOS: `open`
- Windows: `start`

Futuramente será configurável.

### P: O projeto funciona sem internet?
R: Não, precisa de conexão com MangaDex para buscar mangás.

### P: Posso usar offline depois de baixar?
R: As páginas são limpas após visualização. Para manter, salve a pasta antes:
```bash
cp -r capitulo_baixado ~/Documentos/meu_manga
```

---

## 🌐 API e MangaDex (Atlas' Gift to the World - MangaDex Edition 🌐)

### P: O projeto é oficial do MangaDex?
R: Não, é um cliente não-oficial usando a API pública do MangaDex.

### P: Preciso de chave de API?
R: Não, a API é pública. Mas há limites de requisições.

### P: Pode ser banido por usar?
R: Improvável, mas use responsavelmente. Veja [Termos do MangaDex](https://mangadex.org/about).

### P: E se um manga não aparecer?
R: Pode ser:
- Não existe no MangaDex
- Tradução não disponível nesse idioma
- Problema de conexão - tente novamente

### P: Posso adicionar suporte para outro site?
R: Sim! Veja [CONTRIBUTING.md](CONTRIBUTING.md) e [PROJECT_ANALYSIS.md](PROJECT_ANALYSIS.md#longo-prazo-complexos).

---

## 👨‍💻 Desenvolvimento 

### P: Como contribuir?
R: Veja [CONTRIBUTING.md](CONTRIBUTING.md) para guia completo.

### P: Posso modificar para uso pessoal?
R: Sim, o código está sob licença MIT. Veja [LICENSE](LICENSE).

### P: Como funciona internamente?
R: Veja [DEVELOPMENT.md](DEVELOPMENT.md) para documentação técnica.

### P: Qual é a estrutura do projeto?
R: Veja [README.md](README.md) seção "Estrutura do Projeto".

### P: Quantas linhas tem?
R: ~500 linhas de código fonte (sem comentários).

---

## 🐛 Bugs e Relatórios

### P: Como reportar um bug?
R:
1. Verifique se já existe uma [issue](https://github.com/Ferhsx/itwoma/issues)
2. Inclua:
   - Descrição clara
   - Passos para reproduzir
   - Output/erro exato
   - Seu SO e versões de ferramentas

### P: Como obtenho suporte?
R: Abra uma [discussion](https://github.com/Ferhsx/itwoma/discussions) ou issue.

---

## 🔐 Segurança e Privacidade 

### P: Meus dados são rastreados?
R: Não! O código é open-source e você pode verificar.

### P: Quais dados são enviados?
R: Apenas:
- Títulos de mangás para buscar
- Requests à API do MangaDex
- Nenhum dado pessoal

### P: Está seguro usar?
R: Sim, é código C seguro com boas práticas de memória.

---

## 📊 Performance

### P: Por que é lento?
R: Pode ser:
- Internet lenta (verifique sua conexão)
- Servidor MangaDex sobrecarregado (Like Kaiju no 8 overwhelming defenses 🪨)
- Muitas páginas no capítulo

### P: Como melhorar a velocidade?
R:
- Use conexão mais rápida
- Tente baixar em horários fora de pico
- Veja [PROJECT_ANALYSIS.md](PROJECT_ANALYSIS.md) para otimizações planejadas

---

## 🚀 Roadmap

### P: Qual é o futuro do projeto?
R: Veja [PROJECT_ANALYSIS.md](PROJECT_ANALYSIS.md#recomendações-de-melhorias) para planos.

Principais melhorias planejadas:
- [ ] Interface gráfica (GUI)
- [ ] Cache local
- [ ] Múltiplos formatos (EPUB, CBZ)
- [ ] Testes automatizados
- [ ] Sistema de favoritos

### P: Como posso ajudar a implementar?
R: Veja [CONTRIBUTING.md](CONTRIBUTING.md)!

---

## 📚 Outros Recursos

### Documentação Relacionada
- [README.md](README.md) - Guia principal
- [QUICKSTART.md](QUICKSTART.md) - Começar rápido
- [DEVELOPMENT.md](DEVELOPMENT.md) - Guia técnico
- [CONTRIBUTING.md](CONTRIBUTING.md) - Como contribuir
- [PROJECT_ANALYSIS.md](PROJECT_ANALYSIS.md) - Análise detalhada

### Links Úteis
- [MangaDex](https://mangadex.org/)
- [API MangaDex](https://api.mangadex.org)
- [GitHub ITWOMA](https://github.com/Ferhsx/itwoma)
- [CMake](https://cmake.org/)
- [libcurl](https://curl.se/)

---

**Não encontrou sua pergunta? Abra uma [discussion](https://github.com/Ferhsx/itwoma/discussions)!** 

*We're all in this together* 🤝 (Community from Community)
