#!/usr/bin/env bash
set -euo pipefail

# Simple g++ build script — no CMake required.
# Usage: ./build.sh [Debug|Release]
# Produces: lms (executable) in project root.
# Make executable: chmod +x build.sh

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
OBJ_DIR="${BUILD_DIR}/obj"
CONFIG="${1:-Release}"

if [ "${CONFIG}" = "Debug" ]; then
  CXXFLAGS="-g -O0"
else
  CXXFLAGS="-O2"
fi

CXXFLAGS="${CXXFLAGS} -std=c++17 -Wall -Wextra -Wpedantic"
INCLUDES="-I${ROOT_DIR}/include"

mkdir -p "${OBJ_DIR}"

echo "Config: ${CONFIG}"
echo "Scanning for .cpp sources under ${ROOT_DIR}/src ..."

SRCS=()
# collect sources without blocking; works with bash
while IFS= read -r -d '' file; do
  SRCS+=("$file")
done < <(find "${ROOT_DIR}/src" -name '*.cpp' -print0)

if [ "${#SRCS[@]}" -eq 0 ]; then
  echo "No source files found in ${ROOT_DIR}/src"
  exit 1
fi

# compile each source to an object file; object names replace path separators with _
for src in "${SRCS[@]}"; do
  rel="${src#${ROOT_DIR}/}"
  objname="${rel//\//_}"
  objname="${objname%.cpp}.o"
  objpath="${OBJ_DIR}/${objname}"
  echo "Compiling: ${rel}"
  g++ -c "${src}" ${CXXFLAGS} ${INCLUDES} -o "${objpath}"
done

# Link step
echo "Linking objects..."
g++ "${OBJ_DIR}"/*.o -o "${ROOT_DIR}/lms" ${CXXFLAGS}

echo "Build complete: ${ROOT_DIR}/lms"
