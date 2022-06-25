cmake_minimum_required(VERSION 3.0.0)
project(SheJi)

include(CTest)
enable_testing()

add_definitions(-w)

include_directories(./include)

add_executable(1-server ./src/1.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(1-client ./src/2.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)

add_executable(2-server ./src/11.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(2-client ./src/22.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(2-thief ./src/33.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)

add_executable(3-server ./src/111.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(3-client ./src/222.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(3-thief_cli ./src/333cli.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(3-thief_ser ./src/333ser.cpp ./src/diff1.cpp ./src/de.cpp ./src/en.cpp)
add_executable(rsa1 ./src/rsa.c)


target_link_libraries(1-server ssl crypto)
target_link_libraries(1-client ssl crypto)
target_link_libraries(2-server ssl crypto)
target_link_libraries(2-client ssl crypto)
target_link_libraries(2-thief ssl crypto)
target_link_libraries(3-server ssl crypto)
target_link_libraries(3-client ssl crypto)
target_link_libraries(3-thief_cli ssl crypto)
target_link_libraries(3-thief_ser ssl crypto)
target_link_libraries(rsa1 ssl crypto)


