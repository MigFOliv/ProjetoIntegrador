cmake_minimum_required(VERSION 3.15)
project(exercises)

set(COMMON_FLAGS "-g -Wall -pedantic -Wuninitialized -Werror -fsanitize=address -fsanitize=undefined")
set(COMMON_CXX_FLAGS "-std=c++17")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${COMMON_CXX_FLAGS} ${EXTRA}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${EXTRA}")

link_libraries(m)

# Corrigindo a inclusão correta de `accounts_data.cpp`
add_executable(user user.cpp account.cpp accounts_data.cpp)
add_executable(transactions transactions.cpp account.cpp accounts_data.cpp)
