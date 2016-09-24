#!/bin/ksh

# simple-minded test of instructions
# call via:   insn-tests path-to-build-root
#      ala:   src/sim/testsuite/sim/epiphany/insn-tests.sh obj/
srcdir=$(dirname $0)
tardir=$PWD
tooldir=${1:-~/adapteva/src/obj}
filelist=${2:-$srcdir/*.cgs}
if [ ! -e $tooldir/gas/as-new ]; then
    echo "as-new not found";
    exit 1
else
as=$tooldir/gas/as-new
fi
if [ ! -e $tooldir/ld/ld-new ]; then
    echo "ld-new not found";
    exit 1
else
ld=$tooldir/ld/ld-new
fi

if [ ! -e $tooldir/sim/epiphany/run ]; then
    echo "epiphany/run not found";
    exit 1
else
run=$tooldir/sim/epiphany/run
fi

date > cgs.log
date > cgs.sum
	
for f in $filelist; do
    n=$(basename $f)
    print "**************************\n"	     >>cgs.log
    print "* $n *********************\n" 	     >>cgs.log
    print "**************************\n"       >>cgs.log
    $as -o $n.o -I${srcdir} $srcdir/$n	2>&1 >>cgs.log
    $ld -o $n.x $n.o 			2>&1 >>cgs.log
    out=$($run $n.x 2>&1)
    print "$n:\t$out\n"  	 		     >>cgs.log
    print "$n:\t$out\n" 	 		     
done
