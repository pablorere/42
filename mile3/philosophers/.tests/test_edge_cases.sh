#!/bin/bash

# Philosophers Edge Cases Test Suite
# Tests invalid inputs and edge cases to ensure proper error handling

# Get the directory where this script is located and navigate to project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
PHILO="$PROJECT_ROOT/philo"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=========================================="
echo "  PHILOSOPHERS EDGE CASES TEST SUITE"
echo "=========================================="
echo ""

# Check if philo exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: philo executable not found. Run 'make' first.${NC}"
    exit 1
fi

passed=0
failed=0

# Function to run test
run_test() {
    local test_name="$1"
    shift
    local args="$@"

    echo -n "Testing: $test_name ... "

    # Run with timeout and capture output
    timeout 5 $PHILO $args > /dev/null 2>&1
    local exit_code=$?

    # For invalid inputs, we expect error (exit code 1)
    if [ $exit_code -eq 1 ]; then
        echo -e "${GREEN}✓ PASS${NC} (properly rejected)"
        ((passed++))
    elif [ $exit_code -eq 124 ]; then
        echo -e "${RED}✗ FAIL${NC} (timeout - program didn't exit)"
        ((failed++))
    elif [ $exit_code -eq 0 ]; then
        echo -e "${RED}✗ FAIL${NC} (accepted invalid input)"
        ((failed++))
    else
        echo -e "${YELLOW}? UNKNOWN${NC} (exit code: $exit_code)"
        ((failed++))
    fi
}

echo "=== ARGUMENT COUNT TESTS ==="
run_test "No arguments"
run_test "Only 1 argument" 5
run_test "Only 2 arguments" 5 800
run_test "Only 3 arguments" 5 800 200
run_test "Too many arguments (7)" 5 800 200 200 5 100 200

echo ""
echo "=== LETTER/NON-NUMERIC INPUT TESTS ==="
run_test "Letters in arg 1" abc 800 200 200 2
run_test "Letters in arg 2" 5 abc 200 200 2
run_test "Letters in arg 3" 5 800 abc 200 2
run_test "Letters in arg 4" 5 800 200 abc 2
run_test "Letters in arg 5" 5 800 200 200 abc
run_test "Mixed letters and numbers" 5abc 800 200 200 2
run_test "Special characters" 5 800@ 200 200 2
run_test "Spaces in arguments" "5 10" 800 200 200 2
run_test "Empty string arg" "" 800 200 200 2

echo ""
echo "=== NEGATIVE NUMBER TESTS ==="
run_test "Negative philosophers" -5 800 200 200 2
run_test "Negative time_to_die" 5 -800 200 200 2
run_test "Negative time_to_eat" 5 800 -200 200 2
run_test "Negative time_to_sleep" 5 800 200 -200 2
run_test "Negative limit_meals" 5 800 200 200 -5

echo ""
echo "=== ZERO VALUE TESTS ==="
run_test "Zero philosophers" 0 800 200 200 2
run_test "Zero time_to_die" 5 0 200 200 2
run_test "Zero time_to_eat" 5 800 0 200 2
run_test "Zero time_to_sleep" 5 800 200 0 2
run_test "Zero limit_meals" 5 800 200 200 0

echo ""
echo "=== VERY LARGE NUMBER TESTS ==="
run_test "2^31 philosophers (INT_MAX)" 2147483647 800 200 200 2
run_test "2^31+1 (overflow)" 2147483648 800 200 200 2
run_test "Huge number" 999999999999999 800 200 200 2
run_test "Very large time_to_die" 5 2147483648 200 200 2
run_test "Very large time_to_eat" 5 800 2147483648 200 2
run_test "Very large time_to_sleep" 5 800 200 2147483648 2

echo ""
echo "=== BOUNDARY TESTS (subject requirements) ==="
run_test "Exactly 200 philosophers" 200 800 200 200 2
run_test "Time below 60ms (time_to_die)" 5 59 200 200 2
run_test "Time below 60ms (time_to_eat)" 5 800 59 200 2
run_test "Time below 60ms (time_to_sleep)" 5 800 200 59 2
run_test "All times below 60ms" 5 50 50 50 2

echo ""
echo "=== FLOAT/DECIMAL TESTS ==="
run_test "Float in arg 1" 5.5 800 200 200 2
run_test "Float in arg 2" 5 800.5 200 200 2
run_test "Decimal notation" 5 8e2 200 200 2

echo ""
echo "=== WHITESPACE/FORMAT TESTS ==="
run_test "Leading zeros" 005 0800 0200 0200 2
run_test "Plus sign prefix" +5 +800 +200 +200 2
run_test "Tab character" "5	800	200	200	7"

echo ""
echo "=== EXTREME EDGE CASES ==="
run_test "Single philosopher" 1 400 200 200 2
run_test "NULL byte attempt" "$(printf '5\x00')" 800 200 200 2
run_test "Newline in arg" "$(printf '5\n800')" 200 200 200

echo ""
echo "=========================================="
echo "  RESULTS"
echo "=========================================="
echo -e "${GREEN}Passed: $passed${NC}"
echo -e "${RED}Failed: $failed${NC}"
echo "Total: $((passed + failed))"
echo ""

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}✓ All edge case tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed. Review error handling.${NC}"
    exit 1
fi
