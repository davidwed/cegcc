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
cd $BUILD_DIR/newlib
#
make install || exit 1
exit 0
