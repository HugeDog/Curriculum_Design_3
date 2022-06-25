#!/bin/bash
# 我先顽皮一哈子

build_dir="./build"

#########################################
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
##########################################

blue "-----Jinqi Li and Chenchu Zhang Build Shell-----"

if [ -e $build_dir ]
then 
    green "Directory Exists!"
    blue "Deleting..."
    rm -rf $build_dir
else
    red "Directory NOT Exists!"
fi

blue "Make Dir..."
mkdir $build_dir
green "Make Dir Successfully !!"

blue "================= BUILDING... ==================="
blue "Enter Directory..."

cd $build_dir

blue "============= CMAKE ==============="
cmake ..

blue "============= MAKE ==============="
make

green "Leave Directory..."
green "==================== ENDS! ======================"
green "Done!"