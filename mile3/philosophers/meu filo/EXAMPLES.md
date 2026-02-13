# Test Suite Examples

## Example 1: Edge Cases Test (partial output)

```bash
$ ./test_edge_cases.sh
==========================================
  PHILOSOPHERS EDGE CASES TEST SUITE
==========================================

=== ARGUMENT COUNT TESTS ===
Testing: No arguments ... ✓ PASS (properly rejected)
Testing: Only 1 argument ... ✓ PASS (properly rejected)
Testing: Only 2 arguments ... ✓ PASS (properly rejected)
Testing: Only 3 arguments ... ✓ PASS (properly rejected)
Testing: Too many arguments (7) ... ✓ PASS (properly rejected)

=== LETTER/NON-NUMERIC INPUT TESTS ===
Testing: Letters in arg 1 ... ✗ FAIL (timeout - program didn't exit)
Testing: Letters in arg 2 ... ✓ PASS (properly rejected)
Testing: Letters in arg 3 ... ✓ PASS (properly rejected)
Testing: Letters in arg 4 ... ✓ PASS (properly rejected)

=== NEGATIVE NUMBER TESTS ===
Testing: Negative philosophers ... ✓ PASS (properly rejected)
Testing: Negative time_to_die ... ✓ PASS (properly rejected)
Testing: Negative time_to_eat ... ✓ PASS (properly rejected)
Testing: Negative time_to_sleep ... ✓ PASS (properly rejected)
```

This shows that the program correctly rejects most invalid inputs.

## Example 2: Meal Counter

```bash
$ ./count_meals.sh 5 800 200 200 7
==========================================
  MEAL COUNTER FOR PHILOSOPHERS
==========================================

Configuration:
  Philosophers: 5
  Time to die: 800 ms
  Time to eat: 200 ms
  Time to sleep: 200 ms
  Meal limit: 7
  Timeout: 47 seconds

Running simulation...

Meal count per philosopher:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  Philosopher   1:   10 meals ✓
  Philosopher   2:    8 meals ✓
  Philosopher   3:    8 meals ✓
  Philosopher   4:    7 meals ✓
  Philosopher   5:    7 meals ✓
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Statistics:
  Total meals: 40
  Average meals per philosopher: 8
  Minimum meals (any philosopher): 7
  Maximum meals (any philosopher): 10
  Unfed philosophers: 0
  Meal distribution variance: 3
  Fairness: Good ○ (variance ≤ 5)

Meal limit check:
  ✓ All philosophers met the meal requirement!

==========================================
Simulation completed successfully
```

This shows:
- All philosophers ate at least the required 7 meals
- Meals are fairly distributed (variance of only 3)
- No philosopher died
- Simulation completed successfully

## Example 3: Mandatory Tests (partial)

```bash
$ ./test_mandatory.sh
==========================================
  PHILOSOPHERS MANDATORY TEST SUITE
==========================================

[TEST 1] Single philosopher (should die)
  Command: ./philo 1 800 200 200
  Running (timeout 3s)... ✓ PASS (philosopher died as expected)

[TEST 2] 5 philosophers with comfortable times (no death)
  Command: ./philo 5 800 200 200
  Running (timeout 5s)... ✓ PASS (no philosopher died)

[TEST 3] 5 philosophers eating 7 times each (should complete)
  Command: ./philo 5 800 200 200 7
  Running (timeout 10s)... ✓ PASS (simulation completed without deaths)

[TEST 4] 4 philosophers with 410ms to die (no death)
  Command: ./philo 4 410 200 200
  Running (timeout 5s)... ✓ PASS (no philosopher died)

[TEST 5] 4 philosophers with 310ms to die (one should die)
  Command: ./philo 4 310 200 100
  Running (timeout 5s)... ✓ PASS (philosopher died as expected)
```

## Example 4: Stress Test

```bash
$ ./stress_test.sh 10 "5 800 200 200 7"
==========================================
  PHILOSOPHERS STRESS TEST
==========================================

Configuration: 5 800 200 200 7
Iterations: 10

Running stress test...
  Progress: [██████████████████████████████████████████████████] 100% (10/10)

==========================================
  RESULTS
==========================================

Overall Statistics:
  Total runs: 10
  Successful: 10 (100%)
  Failed: 0 (0%)

Meal Statistics (successful runs only):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  Philosopher   1: avg=8    min=7    max=10  
  Philosopher   2: avg=8    min=7    max=9   
  Philosopher   3: avg=8    min=7    max=9   
  Philosopher   4: avg=7    min=7    max=8   
  Philosopher   5: avg=7    min=7    max=8   
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

✓ EXCELLENT: No failures detected in 10 runs!
  The implementation appears stable.
```

This confirms the implementation is stable across multiple runs.

## Quick Test Commands

### Basic Validation
```bash
# Test all mandatory cases
./test_mandatory.sh

# Count meals for specific configuration
./count_meals.sh 5 800 200 200 7

# Quick stress test (5 runs)
./stress_test.sh 5 "5 800 200 200 7"
```

### Comprehensive Testing
```bash
# Run all tests (takes several minutes)
./run_all_tests.sh

# Heavy stress test (100 runs)
./stress_test.sh 100 "4 410 200 200"
```

### Custom Tests
```bash
# Test your own configuration
./count_meals.sh 10 600 150 150 20

# Stress test custom config
./stress_test.sh 50 "7 500 100 100 15"
```

## Understanding Colors

- 🟢 **Green (✓)** - Success/passed
- 🔴 **Red (✗)** - Failure/error
- 🟡 **Yellow (○)** - Warning/in progress
- 🔵 **Blue** - Information
- 🟣 **Magenta** - Headers/titles
- 🔷 **Cyan** - Sections

## Expected Test Results

A correct implementation should show:
1. Most edge cases properly rejected (some exceptions are acceptable)
2. All mandatory tests passing (15/15)
3. 100% success rate in stress tests
4. Fair meal distribution (variance ≤ 5)
5. Timely death detection (within 10ms)

## Notes

- Tests use colored output for better readability
- Progress bars show real-time testing status
- All scripts exit with appropriate codes (0=success, 1=failure)
- Detailed statistics help identify specific issues
