#!/bin/bash

results=`tempfile --suffix .txt`

count_cycles()
{
	app=$1
	source_command="${TOOLCHAIN}/${CC_PREFIX}objdump -d $app"
 	sink_command="$ROOT/scripts/count-cycles.py -"
	$source_command | $sink_command
}

measure_size()
{
	app=$1
	command="${TOOLCHAIN}/${CC_PREFIX}size -t $app"
	$command
}

measure_app()
{
	path=$1
	app_name=`basename $path`
	app=$path/$app_name

	echo "measures for $app" >> $results
	measure_size $app >> $results 2>&1
	count_cycles $app >> $results 2>&1
	echo >> $results
}

cd $ROOT
make distclean MEASURE=true
make all MEASURE=true

measure_app "src/application/collect_and_forward/event-based"
measure_app "src/application/collect_and_forward/generated"

cat $results
echo "results are in $results"
