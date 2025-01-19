cmake_minimum_required(VERSION 3.0)
project(pchList2reabank)

set(CMAKE_CXX_STANDARD 20)

add_executable(pchList2reabank
    config.h
    main.cpp
    PchlistToReabankConverter.cpp
    PchlistToReabankConverter.h
)
