#!/bin/bash

results=`tempfile`.txt

count_cycles()
{
	lib=$1
	source_command="${TOOLCHAIN}/${CC_PREFIX}objdump -d $lib"
 	sink_command="$ROOT/scripts/count-cycles.py -"
	$source_command | $sink_command
}

measure_size()
{
	lib=$1
	command="${TOOLCHAIN}/${CC_PREFIX}size -t $lib"
	$command
}

measure_lib()
{
	path=$1
	name=`basename $path`
	lib="lib${name}.a"

	echo "building $lib" >> $results
	cd $ROOT/$path
	make all MEASURE=true

	measure_size $lib >> $results 2>&1
	count_cycles $lib >> $results 2>&1
	echo >> $results
}

measure_lib "src/application/collect_and_forward/event-based"
measure_lib "src/application/collect_and_forward/generated"
measure_lib "src/operating_system/tinyos/ec_pal"

cat $results
echo "results are in $results"
