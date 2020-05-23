#!/bin/bash

for f in gnuplot; do
    P=`which $f`
    if [[ ! -x $P ]]; then
        echo "Depodan $f paketini yuklemeniz gerekiyor."
        exit 1
    fi
done

if [[ ! -f "./main" ]]; then
    ./build
fi

for i in $(ls -Sr kitap/*.txt); do
    SIZE=$(stat -c "%s" $i)
    SIZE=$(awk "BEGIN{print $SIZE / 1024}")
    echo $i
    echo -n "$SIZE " >> times.txt
    T=$(/usr/bin/time -f "%U" ./main "${i}" 2>&1> /dev/null)
    echo -n "$T" >> times.txt
    if [[ -f main_hash ]]; then
        T=$(/usr/bin/time -f "%U" ./main_hash "${i}" 2>&1> /dev/null)
        echo -n " $T" >> times.txt
    fi
    echo >> times.txt
done

CPU=$(cat /proc/cpuinfo | grep "model name" | awk -F": " '{ print $2 }' | head -n1)
CPU=$(echo $CPU)
MEM=$(free -gh | grep "^Mem" | awk -F" " '{ print $2 }')
ARCH=$(uname -m)
TITLE="$CPU || $MEM Bellek || $ARCH mimari"

gnuplot <<- EOF
    set term pdf font ",9"
    set output 'performans.pdf'
    set title '$TITLE'
    set xlabel 'Boyut (kB)'
    set ylabel 'Zaman (s)'
    set grid

    set yrange [-1:60]
    set key box
    set key spacing 1.5

    plot "times.txt" u 1:2 with lp lw 2 t 'Linked List', "times.txt" u 1:3 with lp lw 2 lc rgb "blue" t 'Hash'
EOF
echo "Grafik performans.pdf dosyasina kaydedildi."
rm -rf times.txt

