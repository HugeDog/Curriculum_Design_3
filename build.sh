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

function checkos(){
    if [[ -f /etc/redhat-release ]]; then
        osRelease="centos"
        osSystemPackage="yum"
        osSystemMdPath="/usr/lib/systemd/system/"
        osReleaseVersionCodeName=""
    elif cat /etc/issue | grep -Eqi "debian|raspbian"; then
        osRelease="debian"
        osSystemPackage="apt-get"
        osSystemMdPath="/lib/systemd/system/"
        osReleaseVersionCodeName="buster"
    elif cat /etc/issue | grep -Eqi "ubuntu"; then
        osRelease="ubuntu"
        osSystemPackage="apt-get"
        osSystemMdPath="/lib/systemd/system/"
        osReleaseVersionCodeName="bionic"
    elif cat /etc/issue | grep -Eqi "centos|red hat|redhat"; then
        osRelease="centos"
        osSystemPackage="yum"
        osSystemMdPath="/usr/lib/systemd/system/"
        osReleaseVersionCodeName=""
    elif cat /proc/version | grep -Eqi "debian|raspbian"; then
        osRelease="debian"
        osSystemPackage="apt-get"
        osSystemMdPath="/lib/systemd/system/"
        osReleaseVersionCodeName="buster"
    elif cat /proc/version | grep -Eqi "ubuntu"; then
        osRelease="ubuntu"
        osSystemPackage="apt-get"
        osSystemMdPath="/lib/systemd/system/"
        osReleaseVersionCodeName="bionic"
    elif cat /proc/version | grep -Eqi "centos|red hat|redhat"; then
        osRelease="centos"
        osSystemPackage="yum"
        osSystemMdPath="/usr/lib/systemd/system/"
        osReleaseVersionCodeName=""
    fi
    blue "Your System: $osRelease"
    blue "Package: $osSystemPackage"
}

function pkgs(){
    if ! dpkg -l | grep -qw $1; then
        red "$1 NOT Installed !"
        read -p "Install? [Y/n]:" isContinueInput
	    isContinueInput=${isContinueInput:-Y}
        if [[ $isContinueInput == [Yy] ]]; then
	 	    ${osSystemPackage} -y install $1
	    else 
	 	    red "Install Cancelled!"
	    fi
    else
        green "$1 Installed !"
	fi
}

function builds(){
    build_dir="./build"
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
    chmod 777 ./*
    green "Leave Directory..."
    green "==================== ENDS! ======================"
    green "Done!"
    blue "-----Jinqi Li and Chenchu Zhang Build Shell-----"
}

################################################################
yellow "--------------------------------"
checkos
yellow "--------------------------------"
yellow "Attention Please:\nRUN IN ROOT!\nIf \"Inline Variable ERROR\" occurs, please check the version of g++ !"
yellow "Before you start, you should ensure that \"sudo $osSystemPackage update \" command has already been executed!"
blue "Press 'ENTER' to Continue..."
read temp
yellow "================== Check Package ================="
pkgs gcc
pkgs g++
pkgs cmake
pkgs libssl-dev
yellow "===================== Build ======================"
builds
################################################################
