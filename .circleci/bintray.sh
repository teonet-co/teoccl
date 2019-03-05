#!/bin/bash
# 
# File:   bintray.sh
# Author: Kirill Scherba
#
# Created on Mar 4, 2019, 7:17:25 PM
#


# Create package
curl -vvf -X POST -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 -H "Content-Type: application/json" https://api.bintray.com/packages/teonet-co/u --data '{"name":"libteoccl","licenses": ["Apache-2.0", "GPL-3.0"],"vcs_url": "https://github.com/neonet-co/teoccl.git"}'

# Read version
curl -X GET -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474  https://api.bintray.com/packages/teonet-co/u/libteoccl/versions/0.0.4-1

# Delete version
curl -X DELETE -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474  https://api.bintray.com/packages/teonet-co/u/libteoccl/versions/0.0.4-1

# Create version
curl -vvf -X POST -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 -H "Content-Type: application/json" https://api.bintray.com/packages/teonet-co/u/libteoccl/versions --data "{\"name\":\"0.0.4-1\",\"desc\":\"v0.0.4-1\"}"

# Put file
curl -X PUT -T libteoccl_0.0.4-1_amd64.deb -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 "https://api.bintray.com/content/teonet-co/u/libteoccl/0.0.4-1/pool/main/l/libteoccl/libteoccl_0.0.4-1_amd64.deb;deb_distribution=wheezy;deb_component=main;deb_architecture=amd64"

# or

curl -X PUT -T libteoccl_0.0.4-1_amd64.deb -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 "https://api.bintray.com/content/teonet-co/u/pool/main/l/libteoccl_0.0.4-1_amd64.deb;deb_distribution=wheezy;deb_component=main;deb_architecture=amd64;override=1;publish=1;bt_package=libteoccl;bt_version=0.0.4-1"

#curl -umyid:mybintraykey https://api.bintray.com/repos/myid/deb -H "Content-Type: application/json" -d '{"name":"deb","type":"debian","default_debian_architecture":"amd64","default_debian_distribution":"all","default_debian_component":"main","private":false,"desc":"This repo...","business_unit":"businessUnit1","labels":["label1","label2"],"gpg_sign_metadata":false,"gpg_sign_files":false,"gpg_use_owner_key":false}' -v


sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61