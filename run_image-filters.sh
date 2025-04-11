#!/bin/bash
ITER="${1:-5}"
echo "Running image-filters with $ITER iterations"

application_list=("canny" "gaussian_noise3" "gaussian_noise5" "gaussian_noise7" "grayscale" "sepia" "sobel" "sobel5" "threshold")

for app in "${application_list[@]}";
do
    echo "Running $app"
    ./$app -l 2 -o ${app}_log -d 1 -p 1 -t $ITER -b "inputs/vga.bmp $app.bmp"
done

calculate_statiscics() {
    line_number=1
    schedulability=0.0
    avg_execution_time=0.0
    avg_elapsed_clocks=0.0

    while IFS= read -r line; do
        IFS=',' read -r -a array <<< "$line"
        line_number=$((line_number+1))

        if (($line_number <= 2)); then
            continue
        fi

        length=${#array[@]}

        float_elapsed_clocks=$(awk -v num="${array[4]}" 'BEGIN {printf "%.4f", num}' | tr -d '[:space:]')
        avg_elapsed_clocks=$(echo "scale=4; $avg_elapsed_clocks + $float_elapsed_clocks" | bc)

        float_schedulability=$(awk -v num="${array[$length-3]}" 'BEGIN {printf "%.4f", num}' | tr -d '[:space:]')
        schedulability=$(echo "scale=4; $schedulability + $float_schedulability" | bc)

        float_execution_time=$(awk -v num="${array[$length-4]}" 'BEGIN {printf "%.4f", num}' | tr -d '[:space:]')
        avg_execution_time=$(echo "scale=4; $avg_execution_time + $float_execution_time" | bc)
    done < "$1"

    schedulability=$(echo "scale=4; $schedulability / ($line_number - 2)" | bc)
    avg_execution_time=$(echo "scale=4; $avg_execution_time / ($line_number - 2)" | bc)
    avg_elapsed_clocks=$(echo "scale=4; $avg_elapsed_clocks / ($line_number - 2)" | bc)
    clock_time_ratio=$(echo "scale=4; $avg_elapsed_clocks / $avg_execution_time" | bc)
    echo "[$1] Schedulability: $schedulability   Avg. Execution Time: $avg_execution_time   Avg. Elapsed Clocks: $avg_elapsed_clocks   Clock/Time Ratio: $clock_time_ratio"
    echo "--------------------------------"
}

main() {
    for app in "${application_list[@]}";
    do
        calculate_statiscics ${app}_log.csv
    done
}

main
