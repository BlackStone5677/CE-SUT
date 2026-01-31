#!/usr/bin/env bash

BASE_GREGORIAN_YEAR=2021

START_SHAMSI=1400
END_SHAMSI=1404

START_SET=6
END_SET=15

for set in $(seq $START_SET $END_SET); do
    mkdir -p "Set ${set}"
    for shamsi in $(seq $START_SHAMSI $END_SHAMSI); do
        for semester in 1 2; do

            if [ "$semester" -eq 1 ]; then
                GM="gm1"
                GREG_YEAR=$((BASE_GREGORIAN_YEAR + (shamsi - START_SHAMSI)))
            else
                GM="gm2"
                GREG_YEAR=$((BASE_GREGORIAN_YEAR + (shamsi - START_SHAMSI) + 1))
            fi

            if [ "$set" -lt 10 ]; then
                URL="http://calculus.math.sharif.edu/${GM}_${GREG_YEAR}/Exercises/GM1-0${set}.pdf"
                OUT="Set ${set}/GM1 - 0${set} - ${shamsi}${semester}.pdf"
            else
                URL="http://calculus.math.sharif.edu/${GM}_${GREG_YEAR}/Exercises/GM1-${set}.pdf"
                OUT="Set ${set}/GM1 - ${set} - ${shamsi}${semester}.pdf"
            fi
            echo "Downloading $URL -> $OUT"
            curl -f -L "$URL" -o "$OUT"

        done
    done
done