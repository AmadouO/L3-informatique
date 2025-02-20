#!/bin/bash
echo $1
if [[ $1 -gt 0 ]]; then
let n=$1-1
bash $0 $n
fi

