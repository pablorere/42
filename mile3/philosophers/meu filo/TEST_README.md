# Philosophers Test Suite

Comprehensive testing suite for the 42 Philosophers project.

## Overview

This test suite provides extensive testing for the philosophers project, including:
- Edge case and error handling tests
- Mandatory test cases from the 42 subject
- Meal counting and analysis
- Stress testing for race conditions
- Comprehensive test runner

## Files

- `test_edge_cases.sh` - Tests invalid inputs and edge cases
- `test_mandatory.sh` - Tests all mandatory cases from the subject
- `count_meals.sh` - Counts and analyzes meals per philosopher
- `stress_test.sh` - Runs tests multiple times to detect intermittent issues
- `run_all_tests.sh` - Master script that runs all tests

## Prerequisites

Build the philosophers program first:
```bash
make
```

Make scripts executable (if not already):
```bash
chmod +x *.sh
```

## Usage

### 1. Edge Cases Test

Tests error handling for invalid inputs:
```bash
./test_edge_cases.sh
```

Tests include:
- Letters and non-numeric input
- Negative numbers
- Zero values
- Very large numbers (overflow)
- Wrong argument count
- Boundary conditions (>200 philosophers, <60ms times)

### 2. Mandatory Tests

Runs all mandatory test cases from the 42 subject:
```bash
./test_mandatory.sh
```

Key tests:
- `1 800 200 200` - Single philosopher (should die)
- `5 800 200 200` - 5 philosophers (no death)
- `5 800 200 200 7` - 5 philosophers eat 7 times each
- `4 410 200 200` - Tight timing (no death)
- `4 310 200 100` - Impossible timing (one should die)
- Additional stress tests with various configurations

### 3. Meal Counter

Counts how many times each philosopher ate:
```bash
./count_meals.sh <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [limit_meals]
```

Examples:
```bash
# Basic usage with meal limit
./count_meals.sh 5 800 200 200 7

# Without meal limit (runs for 10 seconds)
./count_meals.sh 5 800 200 200

# Test single philosopher
./count_meals.sh 1 800 200 200

# Test two philosophers
./count_meals.sh 2 800 200 200
```

Output includes:
- Meal count per philosopher
- Statistics (total, average, min, max)
- Fairness analysis (meal distribution variance)
- Death analysis (if any philosopher died)
- Meal limit verification (if specified)

### 4. Stress Test

Runs the same configuration multiple times to detect race conditions:
```bash
./stress_test.sh <iterations> [test_config]
```

Examples:
```bash
# Run default config 10 times
./stress_test.sh 10

# Run specific config 50 times
./stress_test.sh 50 "5 800 200 200 7"

# Test tight timing 100 times
./stress_test.sh 100 "4 410 200 200"

# Test two philosophers 20 times
./stress_test.sh 20 "2 800 200 200"
```

This is crucial for detecting:
- Race conditions
- Intermittent failures
- Timing issues
- Non-deterministic behavior

### 5. Run All Tests

Comprehensive test suite that runs everything:
```bash
./run_all_tests.sh
```

This will:
1. Run edge cases tests
2. Run mandatory tests
3. Show meal counting examples
4. Run stress tests with multiple configurations
5. Provide final summary

**Note:** This script is interactive and will pause between sections.

## Understanding Results

### Edge Cases Test

- ✓ PASS (properly rejected) - Invalid input was correctly rejected
- ✗ FAIL (timeout) - Program didn't exit (hung or infinite loop)
- ✗ FAIL (accepted invalid input) - Program accepted input it shouldn't

### Mandatory Tests

- ✓ PASS - Test passed as expected
- ✗ FAIL - Test failed (unexpected death or survival)
- ? UNCERTAIN - Unexpected exit code

### Meal Counter

Colors indicate:
- 🟢 Green (✓) - Philosopher met meal requirement
- 🟡 Yellow (○) - Philosopher is eating but hasn't met requirement yet
- 🔴 Red (⚠) - Philosopher hasn't eaten

Fairness levels:
- Excellent: variance ≤ 2 (very fair distribution)
- Good: variance ≤ 5 (acceptable distribution)
- Poor: variance > 5 (unfair, some philosophers starving)

### Stress Test

- Shows progress bar during execution
- Reports success/failure rate
- Analyzes meal statistics across runs
- Detects intermittent failures (race conditions)
- Shows death analysis if deaths occurred

Success rate should be 100% for a correct implementation.

## Common Issues

### Program Hangs (Timeout)

Possible causes:
- Deadlock in fork acquisition
- Threads not terminating properly
- Missing `simulation_end` flag checks
- Mutex issues

### Intermittent Failures

Detected by stress test. Indicates:
- Race conditions in shared memory access
- Improper mutex protection
- Timing-dependent bugs

### Death Detection Delay

If philosopher dies >10ms late:
- Check death monitoring frequency
- Verify `last_meal_time` updates are protected by mutex
- Ensure monitor thread runs frequently enough

### Unfair Meal Distribution

If variance is too high:
- Review fork acquisition logic
- Check for priority issues
- Verify even/odd philosopher synchronization

## Test Scenarios

### Critical Test Cases

1. **Single Philosopher** (`1 800 200 200`)
   - Should die (can't eat with only one fork)

2. **Two Philosophers** (`2 800 200 200`)
   - Critical timing test
   - Death should be detected within 10ms

3. **Tight Timing** (`4 410 200 200`)
   - Philosophers have just enough time
   - Tests efficiency

4. **Impossible Timing** (`4 310 200 100`)
   - At least one philosopher must die
   - Tests death detection

5. **High Meal Count** (`5 800 200 200 50`)
   - Endurance test
   - Tests for memory leaks and stability

### Edge Cases to Handle

- Zero philosophers
- Negative values
- Very large numbers (INT_MAX and overflow)
- More than 200 philosophers (should reject per subject)
- Times below 60ms (should reject per subject)
- Letters and non-numeric input

## Debugging Tips

1. **Use meal counter** to see if philosophers are eating fairly
2. **Run stress tests** with high iteration counts (50-100)
3. **Check output** for mixed messages (indicates mutex issues)
4. **Monitor timing** - deaths should be detected promptly
5. **Verify fairness** - all philosophers should eat similar amounts

## Expected Behavior

A correct implementation should:
- ✅ Handle all error cases properly
- ✅ Pass all mandatory tests
- ✅ Have 100% success rate in stress tests
- ✅ Distribute meals fairly (low variance)
- ✅ Detect deaths within 10ms
- ✅ Never mix output messages
- ✅ Never deadlock or hang
- ✅ Clean up resources properly

## Quick Test Commands

```bash
# Quick validation
./test_mandatory.sh

# Deep analysis
./count_meals.sh 5 800 200 200 7

# Reliability check
./stress_test.sh 50 "5 800 200 200 7"

# Full test (takes several minutes)
./run_all_tests.sh
```

## Customization

You can create custom tests by modifying the scripts or running specific configurations:

```bash
# Custom stress test
./stress_test.sh 100 "10 600 150 150 20"

# Custom meal analysis
./count_meals.sh 7 500 100 100 10
```

## Contributing

Feel free to add more test cases or improve the existing ones. Each test should:
- Have a clear purpose
- Test a specific scenario
- Provide clear output
- Exit with appropriate code (0 = success, 1 = failure)

## Notes

- Tests use `timeout` command to prevent hanging
- Output is colorized for better readability
- Scripts are designed to be run from the project directory
- Some tests may take several seconds/minutes to complete
- Stress tests with high iterations can be time-consuming but are valuable for detecting race conditions

---

**Author:** Test suite for 42 Philosophers project  
**Version:** 1.0  
**Last Updated:** 2025
