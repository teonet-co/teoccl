#!/bin/sh
# 
# File:   make_rpm_inc.sh
# Author: Kirill Scherba <kirill@scherba.ru>
#
# Created on Aug 31, 2015, 2:39:11 PM
#

# Include make functions
# PWD=`pwd`
. "$PWD/ci-build/make_inc.sh"

# Parameters:
# @param $1 Version (required)
# @param $2 Library HI version
# @param $3 Library version
# @param $4 Release (default 1)
# @param $5 Architecture (default x86_64)
# @param $6 RPM subtype (default deb)
# @param $7 Package name (default libteonet)
# @param $8 Package description (default ...)
# Set global variables:
# VER=$1
# LIBRARY_HI_VERSION=$2
# LIBRARY_VERSION=$3
# RELEASE=$4
# ARCH=$5
# INST="yum install -y "
# RPM_SUBTYPE=$6
# RPM_DEV="rpm-build"
# VER=$1-$RELEASE
# PACKET_NAME=$7
# PACKET_DESCRIPTION=$8
check_param()
{    
    # The first parameter is required
    # $1
    if [ -z "$1" ]; then    
        echo The first parameter is required
        exit 1
    fi
    VER=$1

    # $2
    if [ -z "$2" ]; then
        LIBRARY_HI_VERSION=0
    else
        LIBRARY_HI_VERSION=$2
    fi

    # $3
    if [ -z "$3" ]; then
        LIBRARY_VERSION=0
    else
        LIBRARY_VERSION=$3
    fi

    # $4
    if [ -z "$4" ]; then
        RELEASE=1
      else
        RELEASE=$4
    fi

    # $5
    if [ -z "$5" ]; then
        ARCH="x86_64"
      else
        ARCH=$5
    fi

    # $6
    if [ -z "$6" ]; then
        # Default - Ubuntu
        RPM_SUBTYPE="deb"
        INST="sudo apt-get install -y "
        RPM_DEV="rpm"
      else
        # Default - Ubuntu
        RPM_SUBTYPE=$6
        INST="sudo apt-get install -y "
        RPM_DEV="rpm"
        # Rehl
        if [ "$RPM_SUBTYPE" = "yum" ]; then
            INST="yum install -y "
            RPM_DEV="rpm-build"
        fi
        # Suse
        if [ "$RPM_SUBTYPE" = "zyp" ]; then
            INST="zypper install -y "
            RPM_DEV="rpm-devel"
        fi
    fi

    # $7
    if [ -z "$7" ]; then
        PACKET_NAME="teoroom"
    else
        PACKET_NAME=$7
    fi

    # $8
    if [ -z "$8" ]; then
        PACKET_SUMMARY="Teonet room controller version $VER"
    else
        PACKET_SUMMARY=$8
    fi
}

# Update and upgrade build host
# Parameters:
# @param $1 RPM_SUBTYPE="deb"
update_host()
{
    #echo $ANSI_BROWN"Update and upgrade build host:"$ANSI_NONE
    #echo ""
    #if [ RPM_SUBTYPE="deb" ]; then
        #sudo apt-get update
        #sudo apt-get -y upgrade
    #fi
    echo ""
}

# Set RPM build environment
# Parameters:
# @param $1 RPMBUILD
set_rpmbuild_env()
{
    if [ -d "$1" ]; then
        rm -fr $1
    fi
    mkdir $1 #/{RPMS,SRPMS,BUILD,SOURCES,SPECS,tmp}
    mkdir $1/RPMS
    mkdir $1/SRPMS
    mkdir $1/BUILD
    mkdir $1/SOURCES
    mkdir $1/SPECS
    mkdir $1/tmp

    cat <<EOF >~/.rpmmacros
%_topdir   %(echo $HOME)/rpmbuild
%_tmppath  %{_topdir}/tmp
EOF
}

# Create binary tarball and remove source folder
# Parameters:
# @param $1 tarball name
build_rpm_tarball()
{
    echo $ANSI_BROWN"Create binary tarball:"$ANSI_NONE
    echo ""
    tar -zcvf $1.tar.gz $1/
    rm -rf $1/
    echo ""
}

# Copy tarball to the sources folder and create spec file
# @param $1 RPMBUILD
# @param $2 Tarball name
# @param $3 PACKET_NAME
# @param $4 VER
# @param $5 RELEASE
# @param $6 PACKET_SUMMARY
# @param $7 FILES
create_rpm_control()
{
    echo $ANSI_BROWN"Create spec and copy files to the rpmbuild sources folder:"$ANSI_NONE
    echo ""

    # Move tarball file to the rpmbuild folder
    mv -f $2.tar.gz $1/SOURCES

    # Create spec file
    cat <<EOF > $1/SPECS/$3.spec
# Don't try fancy stuff like debuginfo, which is useless on binary-only
# packages. Don't strip binary too
# Be sure buildpolicy set to do nothing
%define        __spec_install_post %{nil}
%define          debug_package %{nil}
%define        __os_install_post %{_dbpath}/brp-compress

Summary: $6
Name: $3
Version: $4
Release: $5
License: GPL+
Group: Development/Tools
SOURCE0 : %{name}-%{version}.tar.gz
URL: http://repo.ksproject.org/

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
%{summary}

%prep
%setup -q

%build
# Empty section.

%install
rm -rf %{buildroot}
mkdir -p  %{buildroot}

# in builddir
cp -a * %{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
$7
#%config(noreplace) %{_sysconfdir}/%{name}/%{name}.conf

%changelog
#* Thu Apr 24 2009  Elia Pinto <devzero2000@rpm5.org> 1.0-1
#- First Build

EOF
    echo "done"
    echo ""
}

# Build the source and the binary RPM
# Parameters:
# @param $1 $INST$RPM_DEV
# @param $2 RPMBUILD
# @param $3 PACKET_NAME
build_rpm()
{
    echo $ANSI_BROWN"Build the source and the binary RPM:"$ANSI_NONE
    echo ""
    echo $1
    $1
    rpmbuild -ba $2/SPECS/$3.spec
    echo ""
}

# Create RPM repository and add packages to this repository
# Parameters:
# @param $1 RPMBUILD
# @param $2 Repository folder with sub-folder
# @param $3 ARCH
# @param $4 INST
create_rpm_repo()
{
    echo $ANSI_BROWN"Add REP package to local repository:"$ANSI_NONE
    echo ""
    if [ ! -d "$2/" ]; then
    mkdir $2/
    fi
    if [ ! -d "$2/$3/" ]; then
    mkdir $2/$3/
    fi
    cp $1/RPMS/$3/* $2/$3/
    cp -r $1/SRPMS/ $2/
    $4"createrepo"
    createrepo $2/$3/
    echo ""
}
