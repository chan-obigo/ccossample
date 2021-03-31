#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/home/obigo/obigo-sdk/target/hyundai/ccos-tcc8053/aarch64-gnu-linux-tcc8053/sysroots/aarch64-gnu-linux
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/home/obigo/obigo-sdk/target/hyundai/ccos-tcc8053/aarch64-gnu-linux-tcc8053/sysroots/aarch64-agl-linux/ccos/lib/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
