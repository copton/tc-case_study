#!/bin/bash

results=`tempfile --suffix .txt`

count_cycles()
{
	app=$1
	${TOOLCHAIN}/${CC_PREFIX}objdump -d $app | $ROOT/scripts/count-cycles.py -
}

measure_size()
{
	app=$1
	${TOOLCHAIN}/${CC_PREFIX}size $app | perl -ne '@parts = split; print "$parts[0], $parts[1], $parts[2]\n"'
}

measure_app()
{
	path=$1
	app_name=`basename $path`
	app=$path/$app_name

	echo "# memory consumption for $app" >> $results
	measure_size $app >> $results 2>&1
	echo >> $results

	echo "# cpu cycles for $app" >> $results
	count_cycles $app >> $results 2>&1
	echo >> $results
}

cd $ROOT
make distclean MEASURE=true
make all MEASURE=true

[ $? -eq 0 ] || exit 1

measure_app "src/application/collect_and_forward/event-based"
measure_app "src/application/collect_and_forward/generated"

editor $results
