<h1 align="center">teoccl - c library of containers data structs and algorithms</h1>

<p align="center">
<a href="https://www.codacy.com/manual/angelskieglazki/teoccl?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=teonet-co/teoccl&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/c7cb5f48aa82488c87c1d301fe5c30b7"/></a>
<a href="https://www.codefactor.io/repository/github/teonet-co/teoccl"><img src="https://www.codefactor.io/repository/github/teonet-co/teoccl/badge" alt="CodeFactor" /></a>
<a href="https://github.com/teonet-co/teoccl/blob/master/COPYING"><img src="https://img.shields.io/badge/license-MIT-orange" alt="License" /></a>
</p>

<p align="center">
<a href="https://circleci.com/gh/teonet-co/workflows/teoccl"><img src="https://img.shields.io/circleci/build/github/teonet-co/teoccl.svg?label=circleci" alt="CircleCI Status" /></a>
<a href="https://teonet-co.github.io/teoccl/"><img src="https://codedocs.xyz/teonet-co/teoccl.svg" alt="Docs Status" /></a>
<a href='https://bintray.com/teonet-co/u/libteoccl0/_latestVersion'><img src='https://api.bintray.com/packages/teonet-co/u/libteoccl0/images/download.svg'></a>
</p>


## 1. Description

The Teonet CCL is a library processed basic containers at C language. The Map and Queue containers are used in [Teonet TR-UDP Library](https://github.com/teonet-co/teonet/wikis/tr-udp).




## 2. Installation from sources

### Install dependencies

    sudo apt install libcunit1-dev libcpputest-dev

### Install project with submodules

    git clone git@github.com:teonet-co/teoccl.git
    cd teoccl
    git submodule update --init


### Install Dependences

There is not dependences


### First time, after got sources from subversion repository

    ./autogen.sh


## 3. Make your application 

    make


## 3.1 Using autoscan to Create configure.ac

After make some global changes in sources code use ```autoscan``` to update projects 
configure.ac


## 4. Installation from repository

### UBUNTU

    http://repo.ksproject.org/ubuntu/
    https://dl.bintray.com/teonet-co/u

### Add repository

KSProject:

    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8CC88F3BE7D6113C
    sudo apt-get install -y software-properties-common
    sudo add-apt-repository "deb http://repo.ksproject.org/ubuntu/ teonet main"
    sudo apt-get update

Bintray:

    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61
    echo "deb https://dl.bintray.com/teonet-co/u bionic main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update

### Install

    sudo apt-get install -y libteoccl

## 5. Run example

See example [README.md](examples/README.md)


## 6. Teo ccl documentation

See libteoccl documentation at: https://teonet-co.github.io/teoccl/
