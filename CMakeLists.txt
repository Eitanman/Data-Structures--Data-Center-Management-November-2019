cmake_minimum_required(VERSION 3.13)
project(ds_wet)

set(CMAKE_CXX_STANDARD 14)

add_executable(ds_wet main1.cpp Keys.cpp Keys.h DataCenter.cpp DataCenter.h
        DS.cpp DS.h List.cpp List.h Node.cpp Node.h Server.cpp Server.h Tree.h library.cpp library1.h)