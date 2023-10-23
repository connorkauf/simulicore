#!/bin/bash
ROOT_DIR=`dirname $0`
if [ ! -d "${ROOT_DIR}/out" ]; then
  mkdir ${ROOT_DIR}/out
fi

for file in ${ROOT_DIR}/bin/*.sh
do
  ofile="$(basename  "${file%.sh}").out"
  "$file" > "${ROOT_DIR}/out/$ofile"
done

exit 0

