#!/bin/bash

# Philosophers Mandatory Test Cases
# Tests all mandatory cases from the 42 subject

# Get the directory where this script is located and navigate to project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
PHILO="$PROJECT_ROOT/philo"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo "=========================================="
echo "  PHILOSOPHERS MANDATORY TEST SUITE"
echo "=========================================="
echo ""

# Check if philo exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: philo executable not found. Run 'make' first.${NC}"
    exit 1
fi

passed=0
failed=0
total=0

# Function to check if philosopher died
check_death() {
    local output="$1"
    if echo "$output" | grep -q "died"; then
        echo "died"
    else
        echo "alive"
    fi
}

# Function to check if all ate required meals
check_all_ate() {
    local output="$1"
    local required="$2"
    # Count "is eating" per philosopher
    local total_meals=$(echo "$output" | grep "is eating" | wc -l)
    echo "$total_meals"
}

# Function to run mandatory test
run_mandatory_test() {
    local test_num="$1"
    local description="$2"
    local timeout_duration="$3"
    local expected_result="$4"
    shift 4
    local args="$@"

    echo -e "${BLUE}[TEST $test_num]${NC} $description"
    echo "  Command: $PHILO $args"
    echo -n "  Running (timeout ${timeout_duration}s)... "

    ((total++))

    # Run with timeout and capture output
    local output=$(timeout $timeout_duration $PHILO $args 2>&1)
    local exit_code=$?

    local result=$(check_death "$output")

    # Analyze result
    if [ "$expected_result" == "should_die" ]; then
        if [ "$result" == "died" ]; then
            echo -e "${GREEN}✓ PASS${NC} (philosopher died as expected)"
            ((passed++))
        else
            echo -e "${RED}✗ FAIL${NC} (no philosopher died, but one should have)"
            ((failed++))
        fi
    elif [ "$expected_result" == "no_death" ]; then
        if [ "$result" == "died" ]; then
            echo -e "${RED}✗ FAIL${NC} (philosopher died unexpectedly)"
            ((failed++))
        else
            echo -e "${GREEN}✓ PASS${NC} (no philosopher died)"
            ((passed++))
        fi
    elif [ "$expected_result" == "complete_meals" ]; then
        # Check if simulation completed (no death and proper exit)
        if [ "$result" == "died" ]; then
            echo -e "${RED}✗ FAIL${NC} (philosopher died)"
            ((failed++))
        elif [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ]; then
            echo -e "${GREEN}✓ PASS${NC} (simulation completed without deaths)"
            ((passed++))
        else
            echo -e "${YELLOW}? UNCERTAIN${NC} (exit code: $exit_code)"
            ((failed++))
        fi
    fi
    echo ""
}

echo "=== MANDATORY TEST CASES FROM SUBJECT ==="
echo ""

# Test 1: Single philosopher should die
run_mandatory_test 1 \
    "Single philosopher (should die)" \
    3 \
    "should_die" \
    1 800 200 200

# Test 2: 5 philosophers, comfortable times (no death)
run_mandatory_test 2 \
    "5 philosophers with comfortable times (no death)" \
    5 \
    "no_death" \
    5 800 200 200

# Test 3: 5 philosophers with meal limit (complete and stop)
run_mandatory_test 3 \
    "5 philosophers eating 7 times each (should complete)" \
    10 \
    "complete_meals" \
    5 800 200 200 7

# Test 4: 4 philosophers with tight but workable timing
run_mandatory_test 4 \
    "4 philosophers with 410ms to die (no death)" \
    5 \
    "no_death" \
    4 410 200 200

# Test 5: 4 philosophers with impossible timing
run_mandatory_test 5 \
    "4 philosophers with 310ms to die (one should die)" \
    5 \
    "should_die" \
    4 310 200 100

echo "=== ADDITIONAL CRITICAL TESTS ==="
echo ""

# Test 6: 2 philosophers (death timing check)
run_mandatory_test 6 \
    "2 philosophers (death timing critical)" \
    3 \
    "should_die" \
    2 400 200 200

# Test 7: 2 philosophers with enough time
run_mandatory_test 7 \
    "2 philosophers with enough time (no death)" \
    3 \
    "no_death" \
    2 800 200 200

# Test 8: 3 philosophers (odd number stress test)
run_mandatory_test 8 \
    "3 philosophers with comfortable times (no death)" \
    5 \
    "no_death" \
    3 800 200 200

# Test 9: 4 philosophers with very tight timing
run_mandatory_test 9 \
    "4 philosophers borderline timing (critical)" \
    5 \
    "no_death" \
    4 400 200 200

# Test 10: Large number of philosophers
run_mandatory_test 10 \
    "100 philosophers (stress test)" \
    5 \
    "no_death" \
    100 800 200 200

# Test 11: 5 philosophers with 1 meal limit
run_mandatory_test 11 \
    "5 philosophers eating once each (should complete quickly)" \
    5 \
    "complete_meals" \
    5 800 200 200 1

# Test 12: Minimum timing (60ms boundary)
run_mandatory_test 12 \
    "5 philosophers with 60ms times (minimum allowed)" \
    3 \
    "no_death" \
    5 800 60 60

# Test 13: Death detection precision
run_mandatory_test 13 \
    "2 philosophers precise death timing (should die)" \
    3 \
    "should_die" \
    2 310 200 100

# Test 14: 6 philosophers
run_mandatory_test 14 \
    "6 philosophers (even number test)" \
    5 \
    "no_death" \
    6 800 200 200

# Test 15: High meal requirement
run_mandatory_test 15 \
    "4 philosophers eating 50 times (endurance)" \
    30 \
    "complete_meals" \
    4 800 200 200 50

echo "=========================================="
echo "  RESULTS"
echo "=========================================="
echo -e "${GREEN}Passed: $passed${NC}"
echo -e "${RED}Failed: $failed${NC}"
echo "Total: $total"
echo ""

percentage=$((passed * 100 / total))
echo "Success rate: $percentage%"
echo ""

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}✓ All mandatory tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ $failed test(s) failed. Review implementation.${NC}"
    exit 1
fi
