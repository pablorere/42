#!/bin/bash

# Script to count how many times each philosopher ate
# Usage: ./count_meals.sh <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [limit_meals]

PHILO="./philo"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

if [ $# -lt 4 ]; then
    echo "Usage: $0 <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [limit_meals]"
    echo "Example: $0 5 800 200 200 7"
    exit 1
fi

# Check if philo exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: philo executable not found. Run 'make' first.${NC}"
    exit 1
fi

NUM_PHILOS=$1
TIME_TO_DIE=$2
TIME_TO_EAT=$3
TIME_TO_SLEEP=$4
LIMIT_MEALS=${5:-"no limit"}

# Calculate reasonable timeout
if [ "$5" != "" ]; then
    # With meal limit
    TIMEOUT=$((($2 + $3 + $4) * $5 * $1 / 1000 + 5))
else
    # Without meal limit, run for fixed time
    TIMEOUT=10
fi

echo -e "${CYAN}=========================================="
echo "  MEAL COUNTER FOR PHILOSOPHERS"
echo -e "==========================================${NC}"
echo ""
echo "Configuration:"
echo "  Philosophers: $NUM_PHILOS"
echo "  Time to die: $TIME_TO_DIE ms"
echo "  Time to eat: $TIME_TO_EAT ms"
echo "  Time to sleep: $TIME_TO_SLEEP ms"
echo "  Meal limit: $LIMIT_MEALS"
echo "  Timeout: $TIMEOUT seconds"
echo ""
echo -e "${YELLOW}Running simulation...${NC}"
echo ""

# Run the simulation and capture output
OUTPUT=$(timeout $TIMEOUT $PHILO $@ 2>&1)
EXIT_CODE=$?

# Save output to temp file for analysis
TEMP_FILE=$(mktemp)
echo "$OUTPUT" > "$TEMP_FILE"

# Check for death
DEATH=$(echo "$OUTPUT" | grep "died")
if [ -n "$DEATH" ]; then
    echo -e "${RED}⚠ DEATH DETECTED:${NC}"
    echo "  $DEATH"
    echo ""
fi

# Count meals per philosopher
echo -e "${BLUE}Meal count per philosopher:${NC}"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

total_meals=0
min_meals=-1
max_meals=0
unfed_philos=0

for (( i=1; i<=$NUM_PHILOS; i++ )); do
    # Count "is eating" for each philosopher
    meals=$(grep "^ *[0-9]* $i is eating" "$TEMP_FILE" | wc -l)
    total_meals=$((total_meals + meals))
    
    # Track min/max
    if [ $min_meals -eq -1 ] || [ $meals -lt $min_meals ]; then
        min_meals=$meals
    fi
    if [ $meals -gt $max_meals ]; then
        max_meals=$meals
    fi
    
    # Track unfed philosophers
    if [ $meals -eq 0 ]; then
        ((unfed_philos++))
    fi
    
    # Color code based on meal count
    if [ $meals -eq 0 ]; then
        color=$RED
        status="⚠"
    elif [ "$5" != "" ] && [ $meals -ge $5 ]; then
        color=$GREEN
        status="✓"
    else
        color=$YELLOW
        status="○"
    fi
    
    printf "  ${color}Philosopher %3d: %4d meals %s${NC}\n" $i $meals "$status"
done

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""

# Statistics
echo -e "${CYAN}Statistics:${NC}"
echo "  Total meals: $total_meals"
echo "  Average meals per philosopher: $((total_meals / NUM_PHILOS))"
echo "  Minimum meals (any philosopher): $min_meals"
echo "  Maximum meals (any philosopher): $max_meals"
echo "  Unfed philosophers: $unfed_philos"

if [ $min_meals -gt 0 ] && [ $max_meals -gt 0 ]; then
    difference=$((max_meals - min_meals))
    echo "  Meal distribution variance: $difference"
    
    # Check fairness (difference should be small)
    if [ $difference -le 2 ]; then
        echo -e "  Fairness: ${GREEN}Excellent ✓${NC} (variance ≤ 2)"
    elif [ $difference -le 5 ]; then
        echo -e "  Fairness: ${YELLOW}Good ○${NC} (variance ≤ 5)"
    else
        echo -e "  Fairness: ${RED}Poor ⚠${NC} (variance > 5)"
    fi
fi

# Check if meal limit was met
if [ "$5" != "" ]; then
    echo ""
    echo -e "${BLUE}Meal limit check:${NC}"
    all_met=true
    for (( i=1; i<=$NUM_PHILOS; i++ )); do
        meals=$(grep "^ *[0-9]* $i is eating" "$TEMP_FILE" | wc -l)
        if [ $meals -lt $5 ]; then
            echo -e "  ${RED}✗ Philosopher $i only ate $meals times (required: $5)${NC}"
            all_met=false
        fi
    done
    
    if [ "$all_met" = true ]; then
        echo -e "  ${GREEN}✓ All philosophers met the meal requirement!${NC}"
    fi
fi

# Death analysis
if [ -n "$DEATH" ]; then
    echo ""
    echo -e "${RED}Death Analysis:${NC}"
    DEAD_PHILO=$(echo "$DEATH" | awk '{print $2}')
    DEATH_TIME=$(echo "$DEATH" | awk '{print $1}')
    meals_before_death=$(grep "^ *[0-9]* $DEAD_PHILO is eating" "$TEMP_FILE" | wc -l)
    echo "  Philosopher $DEAD_PHILO died at ${DEATH_TIME}ms"
    echo "  Meals eaten before death: $meals_before_death"
    
    # Get last meal time
    LAST_MEAL=$(grep "^ *[0-9]* $DEAD_PHILO is eating" "$TEMP_FILE" | tail -1 | awk '{print $1}')
    if [ -n "$LAST_MEAL" ]; then
        time_since_meal=$((DEATH_TIME - LAST_MEAL))
        echo "  Time since last meal: ${time_since_meal}ms"
        
        if [ $time_since_meal -gt $TIME_TO_DIE ]; then
            echo -e "  ${RED}⚠ Death delay: $((time_since_meal - TIME_TO_DIE))ms over limit${NC}"
        else
            echo -e "  ${GREEN}✓ Death detection was timely${NC}"
        fi
    fi
fi

# Cleanup
rm "$TEMP_FILE"

echo ""
echo -e "${CYAN}==========================================${NC}"

# Exit code summary
if [ $EXIT_CODE -eq 124 ]; then
    echo -e "${YELLOW}Simulation timed out after ${TIMEOUT}s${NC}"
elif [ $EXIT_CODE -eq 0 ]; then
    echo -e "${GREEN}Simulation completed successfully${NC}"
else
    echo -e "${RED}Simulation exited with code: $EXIT_CODE${NC}"
fi

echo ""
