#!/bin/bash
ROOT_DIR=`dirname $0`
if [ ! -d "${ROOT_DIR}/i32/out" ]; then
  mkdir -p ${ROOT_DIR}/i32/out
fi

for file in ${ROOT_DIR}/i32/bin/*.sh
do
  ofile="$(basename  "${file%.sh}").out"
  "$file" > "${ROOT_DIR}/i32/out/$ofile"
done

exit 0
