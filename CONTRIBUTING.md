# 🤝 Guia de Contribuição

Obrigado por considerar contribuir ao ITWOMA! Este guia ajudará você a entender nosso processo de desenvolvimento.

## 📋 Antes de Começar

- Leia o [README.md](README.md) para entender o projeto
- Verifique as [Issues](https://github.com/Ferhsx/itwoma/issues) para não duplicar trabalho
- Faça um fork do repositório

## 🔄 Processo de Contribuição

### 1. **Prepare seu Ambiente**

```bash
# Clone seu fork
git clone https://github.com/SEU_USUARIO/itwoma.git
cd itwoma

# Configure o upstream
git remote add upstream https://github.com/Ferhsx/itwoma.git

# Crie uma branch para sua feature
git checkout -b feature/sua-feature
```

### 2. **Faça suas Alterações**

- Mantenha commits limpos e descritivos
- Uma feature por pull request
- Siga o estilo de código existente

### 3. **Teste Sua Alteração**

```bash
# Limpe build anterior
rm -rf build

# Compile e teste
mkdir build && cd build
cmake ..
make

# Execute o programa
./itwoma
```

### 4. **Push e Pull Request**

```bash
# Push para seu fork
git push origin feature/sua-feature

# Abra um PR no repositório original
# Inclua:
# - Descrição clara da feature
# - Motivo da alteração
# - Qualquer contexto relevante
```

## 💎 Padrões de Código

### Estilo C

- Use **C11** como padrão mínimo
- Nomes de variáveis em `snake_case`
- Nomes de constantes em `UPPER_SNAKE_CASE`
- Nomes de funções em `snake_case`
- Máximo 100 caracteres por linha (se possível)

### Exemplo

```c
#define MAX_BUFFER_SIZE 256

typedef struct {
    char *buffer;
    size_t size;
} Buffer;

void process_buffer(Buffer *buf) {
    if (buf == NULL) return;
    // implementação
}
```

### Comentários

```c
// Use comentários claros em seções importantes
// Uma linha: //

/* Para blocos maiores
   use /* */
```

### Gerenciamento de Memória

```c
// Sempre verifique alocações
char *str = malloc(size);
if (str == NULL) {
    fprintf(stderr, "Erro ao alocar memória\n");
    return -1;
}

// Sempre libere memória alocada
free(str);
str = NULL;
```

## 🐛 Reportando Bugs

Ao abrir uma issue de bug, inclua:

1. **Descrição clara** do problema
2. **Passos para reproduzir**
3. **Comportamento esperado**
4. **Comportamento atual**
5. **Ambiente** (SO, versão do CMake, gcc, etc.)
6. **Logs** (se aplicável)

### Exemplo

```markdown
## Bug: Falha ao buscar mangás em português

### Descrição
Quando seleciono português (pt-br), o programa falha com segmentation fault.

### Passos para Reproduzir
1. Executar `./itwoma`
2. Selecionar opção [1] Português
3. Digitar qualquer nome de mangá

### Esperado
Deve listar mangás em português

### Atual
Segmentation fault

### Ambiente
- OS: Ubuntu 22.04
- CMake: 3.24
- GCC: 11.2
```

## 💡 Sugestões de Melhorias

Para sugerir features:

1. Verifique se já existe uma issue similar
2. Descreva a feature claramente
3. Explique o caso de uso
4. Mostre exemplos se possível

## 🎯 Áreas para Contribuição

### Bem-vindo Para

- 🐛 Correção de bugs
- ✨ Novas features
- 📖 Melhorias na documentação
- 🌐 Suporte para novos idiomas
- ⚡ Otimizações de performance
- 🧪 Testes e melhoraria de robustez
- 🐧 Melhor suporte multiplataforma

### Ideias Específicas

- [ ] Interface GUI (usando GTK ou Qt)
- [ ] Suporte para outros sites de mangá
- [ ] Cache de mangás baixados
- [ ] Integração com ebooks (EPUB)
- [ ] Dark mode/modo noturno
- [ ] Histórico de leitura
- [ ] Favoritos
- [ ] Testes automatizados

## 🚀 Após Seu PR (Your Redemption Arc - Red Dead Style)

1. Um mantenedor revisará seu PR
2. Pode haver solicitações de mudanças
3. Uma vez aprovado, será feito merge
4. Você será creditado nos releases!

## 📞 Dúvidas?

- Abra uma [discussion](https://github.com/Ferhsx/itwoma/discussions)
- Mencione @Ferhsx em issues se precisar de ajuda

---

**Obrigado por contribuir! 🎉** 
