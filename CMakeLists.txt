cmake_minimum_required(VERSION 3.28)
project(itwoma C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(itwoma src/main.c
        src/manga.c
        src/http_client.c
        src/parser.c
        lib/cJSON/cJSON.c
        src/utils.c
        src/ui.c
)

target_link_libraries(itwoma PRIVATE CURL::libcurl)

enable_testing()

# 3. Executável dos Testes Unitários (Não precisa de UI nem de internet!)
add_executable(unit_tests
        tests/test_parser.c
        src/manga.c
        src/parser.c
        src/utils.c
        lib/cJSON/cJSON.c
)

# 4. Registra o teste no CTest
add_test(NAME RunAllUnitTests COMMAND unit_tests)