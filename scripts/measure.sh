#!/bin/bash

results=`tempfile`.txt

measure_lib()
{
	path=$1
	name=`basename $path`
	lib="lib${name}.a"

	echo "building in directory $path"
	cd $ROOT/$path
	make all MEASURE=true
	command="${TOOLCHAIN}/${CC_PREFIX}size -t $lib"
	echo $command >> $results
	$command  >> $results
	echo >> $results
}

measure_lib "src/application/collect_and_forward/event-based"
measure_lib "src/application/collect_and_forward/generated"
measure_lib "src/operating_system/tinyos/ec_pal"

echo "results are in $results"
cat $results
