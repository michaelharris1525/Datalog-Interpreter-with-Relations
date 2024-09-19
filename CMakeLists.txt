cmake_minimum_required(VERSION 3.28)
project(proj5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj5
        Database.h
        Graph.h
        Interpreter.h
        main.cpp
        Node.h
        parser.h
        Relation.h
        scanner.h
        SCC.h
        Scheme.h
        token.h
        Tuple.h)
