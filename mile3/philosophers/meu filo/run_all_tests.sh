#!/bin/bash

# Master Test Runner for Philosophers Project
# Runs all test suites comprehensively

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

PHILO="./philo"

echo -e "${MAGENTA}"
echo "╔════════════════════════════════════════════════╗"
echo "║                                                ║"
echo "║      PHILOSOPHERS COMPREHENSIVE TEST SUITE     ║"
echo "║                                                ║"
echo "╚════════════════════════════════════════════════╝"
echo -e "${NC}"
echo ""

# Check if philo exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: philo executable not found.${NC}"
    echo "Building project..."
    make
    if [ ! -f "$PHILO" ]; then
        echo -e "${RED}Build failed. Cannot continue.${NC}"
        exit 1
    fi
    echo -e "${GREEN}Build successful!${NC}"
    echo ""
fi

# Make all test scripts executable
chmod +x test_edge_cases.sh test_mandatory.sh count_meals.sh stress_test.sh 2>/dev/null

overall_result=0

# Function to run a test suite
run_suite() {
    local suite_name="$1"
    local suite_script="$2"
    shift 2
    local args="$@"
    
    echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
    echo -e "${CYAN}  $suite_name${NC}"
    echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
    echo ""
    
    if [ ! -f "$suite_script" ]; then
        echo -e "${RED}Error: $suite_script not found${NC}"
        return 1
    fi
    
    bash "$suite_script" $args
    local result=$?
    
    echo ""
    
    if [ $result -ne 0 ]; then
        overall_result=1
    fi
    
    return $result
}

# Test Suite 1: Edge Cases
echo ""
run_suite "EDGE CASES & ERROR HANDLING" "test_edge_cases.sh"
edge_result=$?

echo ""
read -p "Press Enter to continue to mandatory tests..."
echo ""

# Test Suite 2: Mandatory Tests
run_suite "MANDATORY TEST CASES" "test_mandatory.sh"
mandatory_result=$?

echo ""
read -p "Press Enter to continue to meal counting examples..."
echo ""

# Test Suite 3: Meal Counting Examples
echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
echo -e "${CYAN}  MEAL COUNTING EXAMPLES${NC}"
echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
echo ""

echo -e "${BLUE}Example 1: Simple case with meal limit${NC}"
bash count_meals.sh 5 800 200 200 7
echo ""

echo -e "${BLUE}Example 2: Single philosopher (should die)${NC}"
bash count_meals.sh 1 800 200 200
echo ""

echo -e "${BLUE}Example 3: Two philosophers${NC}"
bash count_meals.sh 2 800 200 200
echo ""

read -p "Press Enter to continue to stress tests..."
echo ""

# Test Suite 4: Stress Tests
echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
echo -e "${CYAN}  STRESS TESTS${NC}"
echo -e "${CYAN}═══════════════════════════════════════════════${NC}"
echo ""

echo -e "${BLUE}Stress Test 1: Basic configuration (10 runs)${NC}"
bash stress_test.sh 10 "5 800 200 200 7"
stress1=$?
echo ""

echo -e "${BLUE}Stress Test 2: Tight timing (10 runs)${NC}"
bash stress_test.sh 10 "4 410 200 200"
stress2=$?
echo ""

echo -e "${BLUE}Stress Test 3: Two philosophers (20 runs)${NC}"
bash stress_test.sh 20 "2 800 200 200"
stress3=$?
echo ""

# Final Summary
echo ""
echo -e "${MAGENTA}"
echo "╔════════════════════════════════════════════════╗"
echo "║                                                ║"
echo "║              FINAL TEST SUMMARY                ║"
echo "║                                                ║"
echo "╚════════════════════════════════════════════════╝"
echo -e "${NC}"
echo ""

# Display results
if [ $edge_result -eq 0 ]; then
    echo -e "  Edge Cases:       ${GREEN}✓ PASSED${NC}"
else
    echo -e "  Edge Cases:       ${RED}✗ FAILED${NC}"
fi

if [ $mandatory_result -eq 0 ]; then
    echo -e "  Mandatory Tests:  ${GREEN}✓ PASSED${NC}"
else
    echo -e "  Mandatory Tests:  ${RED}✗ FAILED${NC}"
fi

if [ $stress1 -eq 0 ]; then
    echo -e "  Stress Test 1:    ${GREEN}✓ PASSED${NC}"
else
    echo -e "  Stress Test 1:    ${RED}✗ FAILED${NC}"
fi

if [ $stress2 -eq 0 ]; then
    echo -e "  Stress Test 2:    ${GREEN}✓ PASSED${NC}"
else
    echo -e "  Stress Test 2:    ${RED}✗ FAILED${NC}"
fi

if [ $stress3 -eq 0 ]; then
    echo -e "  Stress Test 3:    ${GREEN}✓ PASSED${NC}"
else
    echo -e "  Stress Test 3:    ${RED}✗ FAILED${NC}"
fi

echo ""

# Overall verdict
if [ $overall_result -eq 0 ] && [ $stress1 -eq 0 ] && [ $stress2 -eq 0 ] && [ $stress3 -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║                                                ║${NC}"
    echo -e "${GREEN}║       ✓ ALL TESTS PASSED SUCCESSFULLY!         ║${NC}"
    echo -e "${GREEN}║                                                ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════╝${NC}"
else
    echo -e "${RED}╔════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║                                                ║${NC}"
    echo -e "${RED}║          ✗ SOME TESTS FAILED                   ║${NC}"
    echo -e "${RED}║                                                ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════╝${NC}"
    overall_result=1
fi

echo ""
echo "Test suite completed!"
echo ""

exit $overall_result
