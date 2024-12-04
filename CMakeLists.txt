cmake_minimum_required(VERSION 3.26)
project(Project3_43)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(Project3_43
        resources/images/code.png
        resources/images/image.jpg
        resources/images/NOTES.md
        resources/MARKDOWN.md
        src/CleaningCSV.R
        src/main.cpp
        src/Methods.cpp
        src/Methods.h
        src/User.cpp
        src/User.h
        src/B.cpp
        archive/Unordered_Map.h
        archive/Unordered_Map.cpp)
