#!/bin/bash
set -eu
cd "$(dirname "$0")"

# --- Unpack Arguments --------------------------------------------------------
for arg in "$@"; do declare $arg='1'; done
# --- Compilers ---

# --- Build Modes ---
#   this project follows zig build modes
# 	                | Runtime Safety   | Optimizations
#   Debug	        | Yes	           | No
#   ReleaseSafe	    | Yes	           | Yes, Speed
#   ReleaseSmall	| No	           | Yes, Size
#   ReleaseFast	    | No	           | Yes, Speed
if [ -v bm:debug ];            then echo "[debug mode]"; fi
if [ -v bm:releaseSafe ];      then echo "[release safe mode]"; fi
if [ -v bm:releaseSmall ];     then echo "[release small mode]"; fi
if [ -v bm:releaseFast ];      then echo "[release fast mode]"; fi

# --- Prep Directories --------------------------------------------------------
mkdir -p build
mkdir -p local

# --- Debug Flags -------------------------------------------------------------
# debug_flags="-g3 -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined"

# --- Build & Run Program -----------------------------------------------------
# zig cc src/app.c -o build/rayghast -lX11 -lXrandr -lGL $debug_flags
zig cc src/app.c -o build/rayghast -lX11 -lXrandr -lGL
build/rayghast
