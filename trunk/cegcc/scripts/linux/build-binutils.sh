#!/bin/sh
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
if [ -d $BUILD_DIR/binutils ]; then
	rm -rf $BUILD_DIR/binutils
fi
#
mkdir -p $BUILD_DIR/binutils || exit 1
cd $BUILD_DIR/binutils || exit 1
#
export CFLAGS=""
export LDFLAGS=""
#
$TOP_SRCDIR/src/binutils/configure --prefix=$PREFIX \
	--exec-prefix=$PREFIX \
	--target=${TGT_ARCH} \
	--disable-nls \
	--includedir=$PREFIX/include || exit 1
make || exit 1
exit 0
