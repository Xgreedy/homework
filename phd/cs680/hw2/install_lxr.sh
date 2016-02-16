# Install lxr to read source codes.
# Weiwei Jia <wj47@njit.edu>
# 02/05/2016

# References
#
# https://github.com/tpruvot/LXR/blob/master/lxr/doc/INSTALL
# http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install1tools.php

# $ lsb_release -a
# No LSB modules are available.
# Distributor ID:	Ubuntu
# Description:	Ubuntu 15.04
# Release:	15.04
# Codename:	vivid

# Install 3 part libraries and softwares

sudo apt-get install flex apache2 mysql-server exuberant-ctags perl

sudo apt-get install libdbi-perl libdbd-mysql-perl libfile-mmagic-perl libapache2-mod-perl2

# Install glimpse

wget http://webglimpse.net/trial/glimpse-latest.tar.gz
tar xvf glimpse-latest.tar.gz
# you may need to change to your glimpse dir
cd glimpse-4.18.6
./configure
make
sudo make install

# Config install lxr
wget http://tcpdiag.dl.sourceforge.net/project/lxr/stable/lxr-2.0.3.tgz
sudo mv lxr-2.0.3.tgz /usr/local/share
cd /usr/local/share
sudo tar xvf lxr-2.0.3.tgz
sudo mv lxr-2.0.3 lxr

# config lxr here http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install3config.php
# config server for Ubuntu here http://lxr.sourceforge.net/en/Tips/tipubuntu.php
echo "Please config & install LXR by doc (https://github.com/tpruvot/LXR/blob/master/lxr/doc/INSTALL)..."


