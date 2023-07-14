#!/bin/bash
EXE_NAME="$1"

SCRIPT_DIR_PATH=$(cd $(dirname $0) && pwd)
PROJECT_DIR_PATH="${SCRIPT_DIR_PATH}/.."
BUILD_DIR_PATH="${PROJECT_DIR_PATH}/build"
DIST_DIR_PATH="${PROJECT_DIR_PATH}/dist"

rm -rf "${DIST_DIR_PATH}"; mkdir "${DIST_DIR_PATH}"
cp "${BUILD_DIR_PATH}/${EXE_NAME}" "${DIST_DIR_PATH}/${EXE_NAME}"
chmod +x  "${DIST_DIR_PATH}/${EXE_NAME}"
