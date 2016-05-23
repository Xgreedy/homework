#!/bin/bash

# Weiwei Jia <wj47@njit.edu>

# compile and install kernel on Ubuntu 15.04
# http://www.cyberciti.biz/tips/compiling-linux-kernel-26.html
# http://mitchtech.net/compile-linux-kernel-on-ubuntu-12-04-lts-detailed/

#3-part dependencies
sudo apt-get install git-core libncurses5 libncurses5-dev libelf-dev asciidoc binutils-dev build-essential gcc
sudo apt-get install linux-source libncurses5 libncurses5-dev fakeroot build-essential crash kexec-tools makedumpfile kernel-wedge kernel-package
sudo apt-get install libssl-dev

wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.4.1.tar.xz
sudo cp linux-4.4.1.tar.xz /usr/src && cd /usr/src
tar xvf linux-4.4.1.tar.xz
cd linux-4.4.1

sudo cp -vi /boot/config-`uname -r` .config
sudo make oldconfig
sudo make localmodconfig

sudo make menuconfig
sudo make -j5
sudo make modules
sudo make modules_install
sudo make install

# This may be changed for different distros.
sudo update-grub2

sudo reboot
