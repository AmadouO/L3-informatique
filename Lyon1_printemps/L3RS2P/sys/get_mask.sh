#!/bin/bash
echo $(ip addr show  $1 | head -n 3 | tail -n 1 | cut -d '/' -f2 | cut -c 1,2)
