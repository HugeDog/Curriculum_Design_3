#!/bin/bash
# 我先顽皮一哈子

red(){
    echo -e "\033[31m\033[01m$1\033[0m"
}
green(){
    echo -e "\033[32m\033[01m$1\033[0m"
}
yellow(){
    echo -e "\033[33m\033[01m$1\033[0m"
}
blue(){
    echo -e "\033[34m\033[01m$1\033[0m"
}
bold(){
    echo -e "\033[1m\033[01m$1\033[0m"
}

blue "Jinqi Li and Chenchu Zhang Build Shell"

options="-lcrypto -lssl"
build_dir="./build"

if [ -e $build_dir ]
then 
    green "Directory Exists! \nBuilding..."
else
    red "Directory NOT Exists! \nMake Dir... \nBuilding..."
    mkdir $build_dir
fi
yellow "================= BUILDING... ==================="
g++ ./src/1.cpp -o ./build/1-server $options
g++ ./src/2.cpp -o ./build/1-client $options
g++ ./src/222.cpp -o ./build/1-clientsave $options

g++ ./src/3.cpp -o ./build/2-thief $options
g++ ./src/11.cpp -o ./build/2-server $options
g++ ./src/22.cpp -o ./build/2-client $options
# 2-server   2-thief   2-client

chmod 777 ./build/*

green "Done, But U Need To Check If There Has No ERROR!"