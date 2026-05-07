cmake_minimum_required(VERSION 3.20)
project(http-beastie LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(http-beastie
    src/main.cpp
    src/utils.cpp
)

target_include_directories(http-beastie PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(http-beastie PRIVATE
    Boost::system
)
