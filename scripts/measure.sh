#!/bin/bash

if [ $# -eq 1 -a $1 == "-o" ]; then
	options="OPTIMIZE=true"
else
	options=
fi

detailed_results=`tempfile --suffix .cvs --prefix det-`
total_results=`tempfile --suffix .cvs --prefix tot-`

lib_section_size()
{
	lib=$1
    echo "# sections' size for $lib"
	${TOOLCHAIN}/${CC_PREFIX}size -t $lib #| perl -ne '@parts = split; print "$parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

app_section_size()
{
	app=$1
    echo "# sections' size for $app"
	${TOOLCHAIN}/${CC_PREFIX}size $app | perl -ne '@parts = split; print "$parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

total_text_size()
{
    objectfile=$1
    echo "# total text size for $objectfile"
	${TOOLCHAIN}/${CC_PREFIX}objdump -d $objectfile | $ROOT/scripts/sum-text-size.py - -t
    [ $? -eq 0 ] || exit 1
    echo
}

detailed_text_size()
{
    objectfile=$1
    echo "# detailed text size for $objectfile"
	${TOOLCHAIN}/${CC_PREFIX}objdump -d $objectfile | $ROOT/scripts/sum-text-size.py -
    [ $? -eq 0 ] || exit 1
    echo 
}

detailed_cycles()
{
	app=$1
    echo "# number of cycles per function for $app"
	${TOOLCHAIN}/${CC_PREFIX}objdump -d $app | $ROOT/scripts/count-cycles.py -
    [ $? -eq 0 ] || exit 1
    echo
}

measure_app()
{
	path=$1
	app=$path/`basename $path`

    (
    app_section_size $app 
    total_text_size $app
    ) >> $total_results 2>&1

    (
    detailed_text_size $app 
    detailed_cycles $app
    ) >> $detailed_results 2>&1
}

measure_lib()
{
	path=$1
	lib=$path/lib`basename $path`.a

    (
    lib_section_size $lib 
    total_text_size $lib
    ) >> $total_results 2>&1

    (
    detailed_text_size $lib 
    detailed_cycles $lib
    ) >> $detailed_results 2>&1
}

cd $ROOT
make distclean MEASURE=true
make all MEASURE=true $options

[ $? -eq 0 ] || exit 1

echo "building with $options" >> $total_results
echo "building with $options" >> $detailed_results


measure_app "src/application/collect_and_forward/event-based"
measure_app "src/application/collect_and_forward/generated"

measure_lib "src/application/collect_and_forward/event-based"
measure_lib "src/application/collect_and_forward/generated"
measure_lib "src/operating_system/tinyos/ec_pal"

echo "all done. press any key..."
read dummy

editor -O $total_results $detailed_results
echo "results are in $total_results and in $detailed_results"
