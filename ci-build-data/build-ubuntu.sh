#!/bin/sh

sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y autoconf intltool libtool libglib2.0-dev doxygen make gcc g++ checkinstall
sudo apt-get install -y libcunit1-dev libcpputest-dev

