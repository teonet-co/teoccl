#!/bin/sh
# 
# File:   bintray.sh
# Author: Kirill Scherba
#
# Created on Mar 4, 2019, 7:17:25 PM
#

# Read version
curl -X GET -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474  https://api.bintray.com/packages/teonet-co/u/libteoccl/versions/0.0.4-1

# Delete version
curl -X DELETE -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474  https://api.bintray.com/packages/teonet-co/u/libteoccl/versions/0.0.4-1

# Create version
curl -vvf -X POST -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 -H "Content-Type: application/json" https://api.bintray.com/packages/teonet-co/u/libteoccl/versions --data "{\"name\":\"0.0.4-1\",\"desc\":\"v0.0.4-1\"}"

# Put file
curl -X PUT -ukirill-scherba:fc6f1cae3022da43a10350552028763343bc7474 "https://api.bintray.com/content/teonet-co/u/libteoccl/0.0.4-1/pool/main/l/libteoccl/libteoccl_0.0.4-1_amd64.deb;deb_distribution=wheezy;deb_component=main;deb_architecture=amd64"

#curl -umyid:mybintraykey https://api.bintray.com/repos/myid/deb -H "Content-Type: application/json" -d '{"name":"deb","type":"debian","default_debian_architecture":"amd64","default_debian_distribution":"all","default_debian_component":"main","private":false,"desc":"This repo...","business_unit":"businessUnit1","labels":["label1","label2"],"gpg_sign_metadata":false,"gpg_sign_files":false,"gpg_use_owner_key":false}' -v
