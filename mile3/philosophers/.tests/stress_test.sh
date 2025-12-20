#!/bin/bash

# Stress Test Runner for Philosophers
# Runs tests multiple times to detect race conditions and intermittent failures

# Get the directory where this script is located and navigate to project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
PHILO="$PROJECT_ROOT/philo"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

if [ $# -lt 1 ]; then
    echo "Usage: $0 <iterations> [test_config]"
    echo ""
    echo "Examples:"
    echo "  $0 10              - Run default tests 10 times"
    echo "  $0 50 \"5 800 200 200 7\" - Run specific config 50 times"
    exit 1
fi

# Check if philo exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: philo executable not found. Run 'make' first.${NC}"
    exit 1
fi

ITERATIONS=$1
TEST_CONFIG=${2:-"5 800 200 200 7"}

echo -e "${MAGENTA}=========================================="
echo "  PHILOSOPHERS STRESS TEST"
echo -e "==========================================${NC}"
echo ""
echo "Configuration: $TEST_CONFIG"
echo "Iterations: $ITERATIONS"
echo ""

# Parse config
read -r NUM_PHILOS TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP LIMIT_MEALS <<< "$TEST_CONFIG"

# Calculate timeout
if [ -n "$LIMIT_MEALS" ]; then
    TIMEOUT=$(((TIME_TO_DIE + TIME_TO_EAT + TIME_TO_SLEEP) * LIMIT_MEALS * NUM_PHILOS / 1000 + 5))
else
    TIMEOUT=5
fi

# Results tracking
declare -A meal_counts
declare -A death_times
total_runs=0
successful_runs=0
failed_runs=0
death_detected=0
timeout_count=0

# Progress bar function
show_progress() {
    local current=$1
    local total=$2
    local width=50
    local percentage=$((current * 100 / total))
    local filled=$((width * current / total))
    local empty=$((width - filled))

    printf "\r  Progress: ["
    printf "%${filled}s" | tr ' ' '▓'
    printf "%${empty}s" | tr ' ' '░'
    printf "] %3d%% (%d/%d)" $percentage $current $total
}

echo -e "${CYAN}Running stress test...${NC}"
echo ""

# Run iterations
for (( i=1; i<=$ITERATIONS; i++ )); do
    show_progress $i $ITERATIONS

    ((total_runs++))

    # Run simulation
    OUTPUT=$(timeout $TIMEOUT $PHILO $TEST_CONFIG 2>&1)
    EXIT_CODE=$?

    # Check for death
    if echo "$OUTPUT" | grep -q "died"; then
        ((death_detected++))
        DEATH_LINE=$(echo "$OUTPUT" | grep "died")
        DEATH_TIME=$(echo "$DEATH_LINE" | awk '{print $1}')
        death_times[$i]=$DEATH_TIME
        ((failed_runs++))
    elif [ $EXIT_CODE -eq 124 ]; then
        ((timeout_count++))
        ((failed_runs++))
    elif [ $EXIT_CODE -eq 0 ]; then
        ((successful_runs++))

        # Count meals for each philosopher
        for (( p=1; p<=$NUM_PHILOS; p++ )); do
            meals=$(echo "$OUTPUT" | grep "^ *[0-9]* $p is eating" | wc -l)

            # Initialize if first time
            if [ -z "${meal_counts[$p]}" ]; then
                meal_counts[$p]="$meals"
            else
                meal_counts[$p]="${meal_counts[$p]} $meals"
            fi
        done
    else
        ((failed_runs++))
    fi
done

# Clear progress bar
printf "\r%80s\r" " "

echo ""
echo -e "${CYAN}=========================================="
echo "  RESULTS"
echo -e "==========================================${NC}"
echo ""

# Overall statistics
echo -e "${BLUE}Overall Statistics:${NC}"
echo "  Total runs: $total_runs"
echo -e "  ${GREEN}Successful: $successful_runs ($((successful_runs * 100 / total_runs))%)${NC}"
echo -e "  ${RED}Failed: $failed_runs ($((failed_runs * 100 / total_runs))%)${NC}"

if [ $death_detected -gt 0 ]; then
    echo -e "  ${RED}Deaths detected: $death_detected${NC}"
fi
if [ $timeout_count -gt 0 ]; then
    echo -e "  ${YELLOW}Timeouts: $timeout_count${NC}"
fi

echo ""

# Meal statistics per philosopher
if [ $successful_runs -gt 0 ]; then
    echo -e "${BLUE}Meal Statistics (successful runs only):${NC}"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

    for (( p=1; p<=$NUM_PHILOS; p++ )); do
        if [ -n "${meal_counts[$p]}" ]; then
            # Calculate statistics
            meals="${meal_counts[$p]}"
            count=$(echo $meals | wc -w)
            sum=$(echo $meals | tr ' ' '+' | bc)
            avg=$((sum / count))

            # Find min and max
            min=$(echo $meals | tr ' ' '\n' | sort -n | head -1)
            max=$(echo $meals | tr ' ' '\n' | sort -n | tail -1)

            printf "  Philosopher %3d: avg=%-4d min=%-4d max=%-4d\n" $p $avg $min $max
        fi
    done

    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
fi

echo ""

# Death analysis
if [ $death_detected -gt 0 ]; then
    echo -e "${RED}Death Analysis:${NC}"
    echo "  Deaths occurred in $death_detected out of $total_runs runs"
    echo "  Reliability: $(( (total_runs - death_detected) * 100 / total_runs ))%"

    # List death times
    echo ""
    echo "  Death times (ms):"
    for key in "${!death_times[@]}"; do
        echo "    Run $key: ${death_times[$key]}ms"
    done | sort -t: -k1 -n
fi

echo ""

# Race condition detection
if [ $successful_runs -gt 0 ] && [ $failed_runs -gt 0 ]; then
    echo -e "${YELLOW}⚠ WARNING: Intermittent failures detected!${NC}"
    echo "  This suggests possible race conditions or timing issues."
    echo "  Success rate: $(( successful_runs * 100 / total_runs ))%"
elif [ $failed_runs -eq 0 ]; then
    echo -e "${GREEN}✓ EXCELLENT: No failures detected in $total_runs runs!${NC}"
    echo "  The implementation appears stable."
elif [ $successful_runs -eq 0 ]; then
    echo -e "${RED}✗ CRITICAL: All runs failed!${NC}"
    echo "  The implementation has serious issues."
fi

echo ""
echo -e "${MAGENTA}==========================================${NC}"
echo ""

# Summary recommendations
if [ $death_detected -gt 0 ]; then
    echo -e "${YELLOW}Recommendations:${NC}"
    echo "  • Check mutex protection for last_meal_time updates"
    echo "  • Verify death detection logic in monitor thread"
    echo "  • Ensure proper synchronization between eating and monitoring"
    echo ""
fi

if [ $timeout_count -gt 0 ]; then
    echo -e "${YELLOW}Timeout issues detected:${NC}"
    echo "  • Check for deadlocks in fork acquisition"
    echo "  • Verify all threads are properly terminating"
    echo "  • Review simulation_end flag usage"
    echo ""
fi

# Exit with appropriate code
if [ $failed_runs -eq 0 ]; then
    exit 0
else
    exit 1
fi
