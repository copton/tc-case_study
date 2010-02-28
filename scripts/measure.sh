#!/bin/bash

buffer_size=30
optimize=O0
simulate=0
now=`date`

usage()
{
	(
	echo "Usage: $0 [-o] [-b buffer size] [-s]"
	echo "-o: set the optimization (default: O0)"
	echo "-b: set the I/O buffer size (default: 30)"
	echo "-s: run the simulations (default: no)"
	) >&2
	exit 1
}

while getopts b:o:sh o
do	case "$o" in
	b)	buffer_size="$OPTARG" ;;
	o)	optimize="$OPTARG" ;;
	s)  simulate=1 ;;
	h)  usage ;;
	[?]) usage ;;
	esac
done
shift $OPTIND-1

CFLAGS="$CFLAGS -DBUFFER_SIZE=$buffer_size -${optimize}"

measures=`tempfile --suffix .csv`
results=`tempfile --suffix .txt`

lib_section_size()
{
    echo "# sections' size for $1"
	echo -n "# "
	${TOOLCHAIN}/${CC_PREFIX}size $1 | perl -ne '@parts = split; print "$parts[5], $parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

app_section_size()
{
    echo "# sections' size for $1"
	echo -n "# "
	${TOOLCHAIN}/${CC_PREFIX}size $1 | perl -ne '@parts = split; print "$parts[5], $parts[0], $parts[1], $parts[2]\n"'
    [ $? -eq 0 ] || exit 1
    echo
}

avrora_cycles()
{
    echo "# cycles for the the event $1" 
	echo -n "# "
    java avrora.Main -monitors=calls -seconds=1 $1 | $ROOT/scripts/avrora-cycles-diff.py -
    [ $? -eq 0 ] || exit 1
    echo
}

avrora_stack()
{
	echo "# max. stack size for event $1"
	echo -n "# "
	java avrora.Main -action=analyze-stack -seconds=1 $1 | awk '/Maximum stack depth/ {print $5}'
    [ $? -eq 0 ] || exit 1
    echo
}

header()
{
	echo "# timestamp: $now"
	echo "# building with CFLAGS '$CFLAGS'"
}

header
cd $ROOT
make distclean MEASURE=true
make all MEASURE=true $options

[ $? -eq 0 ] || exit 1

(
header

echo "# measuring code size"
lib_section_size src/application/collect_and_forward/event-based/libevent-based.a
lib_section_size src/application/collect_and_forward/generated/libgenerated.a
lib_section_size src/operating_system/tinyos/ec_pal/libec_pal.a

echo "# measuring memory consumption"
app_section_size src/application/collect_and_forward/event-based/event-based
app_section_size src/application/collect_and_forward/generated/generated

if [ $simulate -eq 1 ]; then 
	echo "# measuring cycles"
	avrora_cycles src/application/collect_and_forward/avrora/event-based/event-based.od
	avrora_cycles src/application/collect_and_forward/avrora/generated/generated.od

	echo "# measuring stack"
	#avrora_stack src/application/collect_and_forward/avrora/event-based/event-based.od
	avrora_stack src/application/collect_and_forward/avrora/generated/generated.od
else
	echo "# skipping simluations as requested"
fi
) > $measures 2>&1

(
header
echo "# measures taken from $measures"
$ROOT/scripts/aggregate.py < $measures 
) > $results 2>&1

echo "all done. press any key..."
read dummy

editor $results
