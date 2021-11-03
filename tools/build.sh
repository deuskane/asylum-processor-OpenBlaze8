#!/bin/bash

#-----------------------------------------------------------------------------
# Title      : Build script
# Project    : OpenBlaze8
#-----------------------------------------------------------------------------
# File       : build.sh
# Author     : mrosiere
#-----------------------------------------------------------------------------
# Description: 
#-----------------------------------------------------------------------------
# Copyright (c) 2021
#-----------------------------------------------------------------------------
# Revisions  :
# Date        Version  Author   Description
# 2021-10-26  1.0      mrosiere Created
# 2021-11-03  1.1      mrosiere Use generator
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# build_add_target
#-----------------------------------------------------------------------------
# Argument 1 : ROM file (VHDL file)
# Argument 2 : test name
# Argument 3 : Target name
#-----------------------------------------------------------------------------
# Append 3 files with argument information
# -> update core file (filesets section and targets section)
# -> update Makfile 
#-----------------------------------------------------------------------------
function build_add_target()
{
    file_name=${1}
    file_type=${2}
    target_name=${3}

    cat <<EOT >> /tmp/test_core_generate.txt
  gen_${target_name}:
    generator : pbcc_gen
    parameters:
      file: ${file_name}
      type: ${file_type}

EOT

	cat <<EOT >> /tmp/test_core_targets.txt
  sim_${target_name}:
    << : *sim
    description     : Simulation tof the test ${file_name}
    filesets_append :
      - files_sim
      - pbcc_dep
    generate : [gen_${target_name}]

EOT

	cat <<EOT >> /tmp/test_make.txt
TARGETS += sim_${target_name}
EOT
}

#-----------------------------------------------------------------------------
# build_sdcc
#-----------------------------------------------------------------------------
# Argument 1 : SDCC source  directory
# Argument 2 : SDCC install directory
#-----------------------------------------------------------------------------
# Build SDCC tool
#-----------------------------------------------------------------------------
function build_sdcc()
{
    local dir_src=$1
    local dir_install=$2
    local dir_build=${dir_src}/build.sdcc

    mkdir -p ${dir_build}
    cd       ${dir_build}

    chmod +x ${dir_src}/configure
    chmod +x ${dir_src}/sim/ucsim/mkecho

    echo "[SDCC] Configure"
    ${dir_src}/configure \
	--prefix=${dir_install} \
	--disable-{pic14,pic16,hc08,stm8,ds390,ds400,z80,mcs51,s08,z180,r2k,r3ka,gbz80,tlcs90}-port \
	--disable-sdbinutils  \
	--disable-device-lib  \
	--disable-ucsim       \
	--disable-sdcdb       \
	--disable-packihx

    echo "[SDCC] Build"
    make -j

    echo "[SDCC] Install"
    make -j install

    cd -
}

#-----------------------------------------------------------------------------
# build_picoasm
#-----------------------------------------------------------------------------
# Argument 1 : PICOASM Source directory
# Argument 2 : PICOASM install directory
#-----------------------------------------------------------------------------
# Build PICOASM tool
#-----------------------------------------------------------------------------
function build_picoasm()
{
    local dir_src=$1
    local dir_install=$2

    echo "[PICOASM] Build"
    make -C ${dir_src} -j

    echo "[PICOASM] Install"
    mkdir -p   ${dir_install}/bin
    mkdir -p   ${dir_install}/share/picoasm/xilinx
    mkdir -p   ${dir_install}/share/picoasm/generic

    cp ${dir_src}/picoasm ${dir_install}/bin

    cp ${dir_src}/ROM_form.v      ${dir_install}/share/picoasm/xilinx
    cp ${dir_src}/ROM_form.vhd    ${dir_install}/share/picoasm/xilinx
    cp ${dir_src}/../ROM_form.vhd ${dir_install}/share/picoasm/generic

}

#-----------------------------------------------------------------------------
# build_main
#-----------------------------------------------------------------------------
# Argument 1 : ROM file (VHDL file)
# Argument 2 : test name
# Argument 3 : Target name
#-----------------------------------------------------------------------------
# Generate all tools and ROM
#-----------------------------------------------------------------------------
function build_main()
{
    BUILD_SDCC=false
    BUILD_PICOASM=false
    GENERATE_ROM=false

    # Directory
    dir_tools=`/bin/pwd`
    dir_ip=${dir_tools}/..
    dir_picoasm=${dir_tools}/picoasm
    dir_sdcc=${dir_tools}/pbccv2-src-20110901/sdcc3
    dir_install=${dir_tools}/install
    dir_test_asm=${dir_ip}/sim/testbench-asm
    dir_test_c=${dir_ip}/sim/testbench-c

    # File
    file_core=${dir_ip}/OpenBlaze8.core
    file_make=${dir_ip}/mk/targets.mk
    
    # SDCC Compilation
    if ${BUILD_SDCC};
    then
	build_sdcc    ${dir_sdcc} ${dir_install}
    fi

    # Picoasm Compilation
    if ${BUILD_PICOASM};
    then
	build_picoasm ${dir_picoasm} ${dir_install}
    fi

    # Delete previous ROM
    rm -f ${dir_test_asm}/*.v
    rm -f ${dir_test_asm}/*.vhd
    rm -f ${dir_test_asm}/*.hex
    rm -f ${dir_test_asm}/*.log

    rm -f ${dir_test_c}/*.psm
    rm -f ${dir_test_c}/*.v
    rm -f ${dir_test_c}/*.vhd
    rm -f ${dir_test_c}/*.hex
    rm -f ${dir_test_c}/*.log


    if ${GENERATE_ROM};
    then
	# Compilation of all C files
	for f in `find ${dir_test_c}/*.c`; do
	    ${dir_install}/bin/sdcc -I ${dir_install}/share/sdcc/include -V -S --dialect=kcpsm3 ${f} -o ${f/.c/.psm}

    	    if test $? -ne 0; then exit; fi
	done

	# Translate all PSM file
	for f in `find ${dir_test_c}/*.psm`; do
	    
	    ${dir_install}/bin/picoasm -i $f -t ${dir_install}/share/picoasm/generic/ROM_form.vhd -v -m OpenBlaze8_ROM -a kcpsm3

	    if test $? -ne 0; then break; fi
	    
	done

	for f in `find ${dir_test_asm}/*.psm`; do
	    
	    ${dir_install}/bin/picoasm -i $f -t ${dir_install}/share/picoasm/generic/ROM_form.vhd -v -m OpenBlaze8_ROM -a pblazeide

	    if test $? -ne 0; then break; fi
	    
	done
    fi
	
    rm -f /tmp/test_core_filesets.txt
    rm -f /tmp/test_core_generate.txt
    rm -f /tmp/test_core_targets.txt
    rm -f /tmp/test_make.txt

    touch /tmp/test_core_filesets.txt
    touch /tmp/test_core_generate.txt
    touch /tmp/test_core_targets.txt
    touch /tmp/test_make.txt

    dir_ip=${dir_ip}/
    for f in `find ${dir_test_asm}/*.psm`; do

	file_name=${f/${dir_ip}/}
	test_name=`basename ${f/.psm/}`
	target_name=asm_${test_name}
	
	build_add_target ${file_name} "pblazeide" ${target_name}
	
    done

    for f in `find ${dir_test_c}/*.c`; do

	file_name=${f/${dir_ip}/}
	test_name=`basename ${f/.c/}`
	target_name=c_${test_name}

	build_add_target ${file_name} "c" ${target_name}
	
    done

    # Edit Core File
    sed -i '/<FILESETS_BEGIN>/,/<FILESETS_END>/{/<FILESETS_BEGIN>/!{/<FILESETS_END>/!d}}' ${file_core}
    sed -i '/<GENERATE_BEGIN>/,/<GENERATE_END>/{/<GENERATE_BEGIN>/!{/<GENERATE_END>/!d}}' ${file_core}
    sed -i '/<TARGETS_BEGIN>/,/<TARGETS_END>/{/<TARGETS_BEGIN>/!{/<TARGETS_END>/!d}}'     ${file_core}

    sed -i '/<FILESETS_BEGIN>/r /tmp/test_core_filesets.txt'                              ${file_core}
    sed -i '/<GENERATE_BEGIN>/r /tmp/test_core_generate.txt'                              ${file_core}
    sed -i '/<TARGETS_BEGIN>/r  /tmp/test_core_targets.txt'                               ${file_core}

    # Edit Targets
    cp /tmp/test_make.txt ${file_make}
}

build_main $*
