#!/bin/bash

log=build/build.log
if [ ! -e build ]; then mkdir build; fi
if [ -e ${log} ]; then echo "Rebuilding!" >> ${log}; fi
(time make) 2>&1 | tee -a ${log}

