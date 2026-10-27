cmake_minimum_required(VERSION 3.20)
project(ed1_linked_list_cpp)

# Configuração para compilação estrita em C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclui o diretório de headers para facilitar o include
include_directories(include)

# Define o executável de testes
add_executable(LinkedListTest src/LinkedListTest.cpp)