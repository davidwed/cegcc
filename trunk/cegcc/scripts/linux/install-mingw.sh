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
cd $BUILD_DIR/mingw-runtime
#
make install prefix=${PREFIX}/${TGT_ARCH} || exit 1
exit 0
