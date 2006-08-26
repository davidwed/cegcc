#!/bin/sh
set -x
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
if [ -d $BUILD_DIR/gdb ]; then
	rm -rf $BUILD_DIR/gdb
fi
#
mkdir -p $BUILD_DIR/gdb || exit 1
cd $BUILD_DIR/gdb
#
CFLAGS="-I$TOP_SRCDIR/src/w32api/include -D__USE_W32_SOCKETS"
export CFLAGS
#
$TOP_SRCDIR/src/gdb/configure \
	--prefix=$PREFIX \
	--target=$TARGET_ARCH || exit 1
make || exit 1
exit 0
