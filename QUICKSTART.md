# 🚀 Guia Rápido de Início 

Para começar a usar o ITWOMA em 5 minutos!

## Linux/macOS (Rápido)

```bash
# 1. Clonar (Shimmer in the light)
git clone https://github.com/Ferhsx/itwoma.git
cd itwoma

# 2. Instalar dependências
# Ubuntu/Debian
sudo apt-get install -y build-essential cmake libcurl4-openssl-dev

# macOS
brew install cmake curl

# 3. Compilar
mkdir build && cd build
cmake ..
make

# 4. Executar
./itwoma
```

## Windows

```powershell
# 1. Clonar
git clone https://github.com/Ferhsx/itwoma.git
cd itwoma

# 2. Instalar (se ainda não tiver):
#    - CMake: https://cmake.org/download/
#    - Visual Studio Build Tools: https://visualstudio.microsoft.com/
#    - libcurl: https://curl.se/download.html

# 3. Compilar
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release

# 4. Executar
Release\itwoma.exe
```

## Solução de Problemas Rápida

| Erro | Solução |
|------|---------|
| `cmake: command not found` | Instale CMake |
| `libcurl not found` | `apt-get install libcurl4-openssl-dev` |
| `Compilador não encontrado` | Instale build-essential ou MSVC |
| Build falha | Limpe: `rm -rf build && mkdir build` |

---

📖 Para guia completo, veja [README.md](README.md)
