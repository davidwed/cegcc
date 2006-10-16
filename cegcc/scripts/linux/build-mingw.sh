#!/bin/sh
#
# HACK
# export TGT_ARCH=arm-wince-mingw32ce
#
# Read the settings
#
if [ -r settings.sh ]; then
	. settings.sh
else
	. scripts/linux/settings.sh
fi
#
# Put the cleanup here instead of in the calling script
#
if [ -d $BUILD_DIR/profile ]; then
	rm -rf $BUILD_DIR/profile
fi
#
mkdir -p $BUILD_DIR/profile || exit 1
cd $BUILD_DIR/profile || exit 1
#
$TOP_SRCDIR/src/mingw/configure \
	--prefix=$PREFIX \
	--target=$TGT_ARCH --host=$TGT_ARCH --build=$MY_HOST_ARCH || exit 1
#
make || exit 1
exit 0
