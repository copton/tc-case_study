#!/bin/bash

if [ $# -eq 1 -a $1 == "-o" ]; then
    options="OPTIMIZE=true"
else
    options=
fi

results=`tempfile --suffix .txt`


avrora_cycles_pure_app()
{
    if [ $# -eq 2 -a $1 == "-gen" ]; then
	echo "# cycles without pal for generated $2"
    elif [ $# -eq 2 -a $1 == "-evt" ]; then
	echo "# cycles without raw for event-based $2"
    fi
    java avrora.Main -monitors=calls -seconds=2 $2 | sed 's/\[....m//g' | $ROOT/scripts/avrora-cycles-pure-app.py - $1
}

avrora_count_cycles()
{
    mytmp=`tempfile`
    avr-objdump -d $2 | $ROOT/scripts/count-cycles.py - >$mytmp
    echo ""
    if [ $# -eq 2 -a $1 == "-gen" ]; then
        echo "# count cycles for generated $2"
        cat  $mytmp | sed '/^ec_sub/!d'

        cat  $mytmp | sed '/^ec_sub/!d' |
        awk 'BEGIN{sum=0} {sum+=$2} END {print "total count cycles gen: " sum}'
    elif [ $# -eq 2 -a $1 == "-evt" ]; then
        echo "# count cycles for event-based $2"
        cat $mytmp | sed '/^function/d; /^collect_init/d; /^receive_init/d; /^send_init#1/d; /^main/d'

        cat $mytmp | sed '/^function/d; /^collect_init/d; /^receive_init/d; /^send_init#1/d; /^main/d' |
        awk 'BEGIN{sum=0} {sum+=$2} END {print "total count cycles evt: " sum}'
    fi
    rm -rf $mytmp
}

summary_report()
{
    cat $1 | awk -F: 'BEGIN{evt_cycles = 0.0; gen_cycles = 0.0} /^total cycles of app evt/ { evt_cycles = $2 } /^total cycles of app gen/ {gen_cycles = $2} END{ print "cycle ratio: ", gen_cycles/evt_cycles}'
}

cd $ROOT
make distclean MEASURE=true
make all MEASURE=true $options

[ $? -eq 0 ] || exit 1

(
echo "# building with '$options'"

avrora_cycles_pure_app -gen src/application/collect_and_forward/avrora/generated/generated.od
avrora_cycles_pure_app -evt src/application/collect_and_forward/avrora/event-based/event-based.od

#avrora_count_cycles -gen src/application/collect_and_forward/generated/libgenerated.a 
#avrora_count_cycles -evt src/application/collect_and_forward/event-based/libevent-based.a 
) > $results 2>&1

(
echo ""
echo "# summary"
summary_report $results
) >> $results 2>&1

echo "all done. press any key..., check the $results"
read dummy

editor $results
#cat $results 
