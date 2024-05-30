cmake_minimum_required(VERSION 3.28)
project(crypto)

set(CMAKE_CXX_STANDARD 17)

add_executable(crypto main.cpp
        rsa.h
        module_math.h
        primes.h
        number_theory.h)
