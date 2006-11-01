#!/bin/sh
if [ -x ./list-libs.sh ]; then
	SCRIPTDIR=`pwd`
	cd ../..
	TOP_SRCDIR=`pwd`
else
	TOP_SRCDIR=`pwd`
	SCRIPTDIR=$TOP_SRCDIR/scripts/linux
fi
#
export SCRIPTDIR TOP_SRCDIR
#
# Check whether we're running under "rpmbuild".
# If we do, use a temporary directory as prefix.
#
if [ x$MY_RPM_PREFIX != x ]; then
	PREFIX=$MY_RPM_PREFIX
	mkdir -p $PREFIX
else
	PREFIX=/usr/ppc
fi
export PREFIX
#
if [ "x$SCRIPT_DEBUG" != x ]; then
	echo "###"
	echo "### setting PREFIX to $PREFIX"
	echo "###"
fi
#
MY_HOST_ARCH=`$TOP_SRCDIR/src/gcc/config.guess`
export MY_HOST_ARCH
#
# Only set the target environment variable if it isn't already set.
#
if [ "x$TGT_ARCH" == "x" ]; then
	#
	# Choose the target environment here.
	#
	TGT_ARCH=arm-wince-cegcc
	#
	MINGW_TGT_ARCH=arm-wince-mingw32ce
	MINGW_BUILD_DIR=$TOP_SRCDIR/build/$MY_HOST_ARCH/$MINGW_TGT_ARCH
	#
	export TGT_ARCH MINGW_BUILD_DIR MINGW_TGT_ARCH
fi
#
BUILD_DIR=$TOP_SRCDIR/build/$MY_HOST_ARCH/$TGT_ARCH
export BUILD_DIR
#
# This set of scripts relies on the fact that $PREFIX/bin is in your path.
# Make sure it is ...
#
export PATH=${PREFIX}/bin:${PATH}
#
# The name of this release
#
CEGCC_RELEASE=0.10
export CEGCC_RELEASE
#
# The debugging stub
#
export STUB_SRC=${TOP_SRCDIR}/src/gdb/gdb/wince-stub.c
export STUB_EXE=${BUILD_DIR}/gdb/${TGT_ARCH}-stub.exe

