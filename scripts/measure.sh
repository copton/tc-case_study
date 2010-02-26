#!/bin/bash

if [ $# -eq 1 -a $1 == "-o" ]; then
	options="OPTIMIZE=true"
else
	options=
fi

results=`tempfile --suffix .cvs`

lib_section_size()
{
    echo "# sections' size for $1"
	${TOOLCHAIN}/${CC_PREFIX}size -t $1 #| perl -ne '@parts = split; print "$parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

app_section_size()
{
    echo "# sections' size for $1"
	${TOOLCHAIN}/${CC_PREFIX}size $1 #| perl -ne '@parts = split; print "$parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

avrora_cycles()
{
    echo "# cycles for the the event $1" 
    java avrora.Main -monitors=calls -seconds=2 $1 | $ROOT/scripts/avrora-cycles-diff.py -
    [ $? -eq 0 ] || exit 1
    echo
}

avrora_stack()
{
	echo "# max. stack size for event $1"
	java avrora.Main -action=analyze-stack -seconds=2 $1 | awk '/Maximum stack depth/ {print $5}'
    [ $? -eq 0 ] || exit 1
    echo
}

cd $ROOT
make distclean MEASURE=true
make all MEASURE=true $options

[ $? -eq 0 ] || exit 1

(
echo "building with '$options'"

echo "# measuring code size"
lib_section_size src/application/collect_and_forward/event-based/libevent-based.a
lib_section_size src/application/collect_and_forward/generated/libgenerated.a
lib_section_size src/operating_system/tinyos/ec_pal/libec_pal.a

echo "# measuring memory consumption"
app_section_size src/application/collect_and_forward/event-based/event-based
app_section_size src/application/collect_and_forward/generated/generated

echo "# measuring cycles"
avrora_cycles src/application/collect_and_forward/avrora/event-based/event-based.od
avrora_cycles src/application/collect_and_forward/avrora/generated/generated.od

echo "# measuring stack"
#avrora_stack src/application/collect_and_forward/avrora/event-based/event-based.od
avrora_stack src/application/collect_and_forward/avrora/generated/generated.od
) > $results 2>&1

echo "all done. press any key..."
read dummy

editor $results
echo "results are in $results"
