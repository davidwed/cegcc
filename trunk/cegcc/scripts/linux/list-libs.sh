#!/bin/sh
#
# Set up a list of DLL proxies to make.
#
LIST="coredll winsock aygshell commctrl iphlpapi ws2"
# LIST="coredll winsock aygshell commctrl fileopen"
#
# List of libraries to squash into once libcegcc.a
#
LIBS_CEGCC_LIB="c winsock"
