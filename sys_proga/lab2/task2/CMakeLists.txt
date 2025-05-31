cmake_minimum_required(VERSION 3.22)
project(Laba_2_2)

set(CMAKE_CXX_STANDARD 20)


add_executable(Laba_2_2 main.cpp
        analyzer.cpp
        analyzer.hpp
        generator.cpp
        generator.hpp
        ip_st.hpp
        logger.cpp
        logger.hpp
        ts_queue.hpp
        utils.hpp)

       
