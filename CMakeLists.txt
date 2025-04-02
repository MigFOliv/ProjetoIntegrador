cmake_minimum_required(VERSION 3.15)
project(exercises)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags recomendadas (boas práticas)
set(COMMON_FLAGS "-g -Wall -pedantic -Wuninitialized -Werror -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")

# Bibliotecas necessárias para ImGui
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Fontes ImGui
file(GLOB IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
)

# Diretórios do ImGui
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Ficheiros fonte do teu projeto (organizado claramente)
set(PROJECT_SOURCES
    user.cpp
    user_utils.cpp   
    account.cpp
    accounts_data.cpp
    transactions.cpp
    ${IMGUI_SOURCES}
)

# Executável final
add_executable(user ${PROJECT_SOURCES})

# Liga as bibliotecas necessárias
target_link_libraries(user PRIVATE glfw OpenGL::GL)
