#!/bin/bash
# 我先顽皮一哈子
echo -e "Jinqi Li and Chenchu Zhang Build Shell"

options="-lcrypto -lssl"
build_dir="./build"

if [ -e $build_dir ]
then 
    echo -e "Directory Exists! \nBuilding..."
else
    echo -e "Directory NOT Exists! \nMake Dir... \nBuilding..."
    mkdir $build_dir
fi
echo -e "================= BUILDING... ==================="
g++ ./src/1.cpp -o ./build/1-server $options
g++ ./src/2.cpp -o ./build/1-client $options
g++ ./src/3.cpp -o ./build/2-thief $options
g++ ./src/11.cpp -o ./build/2-server $options
g++ ./src/22.cpp -o ./build/2-client $options

chmod 777 ./build/*

echo -e "Done, But U Need To Check If There Has No ERROR!"