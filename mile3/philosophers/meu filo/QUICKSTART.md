# Quick Start Guide - Philosophers Test Suite

## 🚀 Getting Started (30 seconds)

```bash
# Build the project
make

# Run the most important tests
./test_mandatory.sh

# That's it! ✅
```

## 🎯 Most Useful Commands

### 1. Quick Health Check (1 minute)
```bash
./test_mandatory.sh
```
Runs all mandatory tests from the 42 subject. Should pass 15/15.

### 2. Analyze Meal Distribution (30 seconds)
```bash
./count_meals.sh 5 800 200 200 7
```
Shows how many times each philosopher ate. Perfect for debugging fairness issues.

### 3. Detect Race Conditions (2 minutes)
```bash
./stress_test.sh 20 "5 800 200 200 7"
```
Runs the same test 20 times. If success rate < 100%, you have race conditions.

### 4. Full Test Suite (5-10 minutes)
```bash
./run_all_tests.sh
```
Runs everything. Use this before submission.

## 📊 What Each Script Does

| Script | Purpose | Time | When to Use |
|--------|---------|------|-------------|
| `test_mandatory.sh` | Mandatory 42 tests | 1 min | Always - first thing to run |
| `count_meals.sh` | Meal analysis | 30 sec | Debug fairness issues |
| `stress_test.sh` | Race condition detection | 1-10 min | Before submission |
| `test_edge_cases.sh` | Error handling | 2 min | Ensure robustness |
| `run_all_tests.sh` | Everything | 5-10 min | Final validation |

## 🔍 Common Issues & Solutions

### Issue: "Philosopher X didn't eat enough"
```bash
# Analyze meal distribution
./count_meals.sh 5 800 200 200 10

# Look for high variance (>5) in the output
# This indicates unfair scheduling
```

### Issue: "Tests sometimes pass, sometimes fail"
```bash
# Run stress test to confirm
./stress_test.sh 50 "5 800 200 200 7"

# If success rate < 100%, you have race conditions
# Check mutex protection on shared data
```

### Issue: "Philosopher died but shouldn't have"
```bash
# Check death detection timing
./count_meals.sh 4 410 200 200

# Look at "Death Analysis" section
# Death should be detected within 10ms
```

## 📝 Test Results Interpretation

### ✅ Good Results
```
Passed: 15
Failed: 0
Success rate: 100%
Fairness: Excellent ✓ (variance ≤ 2)
```
**Action:** You're ready to submit! 🎉

### ⚠️ Warning Signs
```
Passed: 13
Failed: 2
Success rate: 87%
Fairness: Good ○ (variance ≤ 5)
```
**Action:** Review failing tests. Some race conditions likely.

### ❌ Critical Issues
```
Passed: 5
Failed: 10
Success rate: 33%
Fairness: Poor ⚠ (variance > 5)
```
**Action:** Major issues with synchronization or logic.

## 🎨 Understanding the Output

- 🟢 **Green ✓** = Success (good!)
- 🟡 **Yellow ○** = Warning (acceptable but not perfect)
- 🔴 **Red ⚠** = Failure (needs fixing)
- 🔵 **Blue** = Information (neutral)

## 🏆 Before You Submit

Run this checklist:

```bash
# 1. Clean and rebuild
make fclean && make

# 2. Run mandatory tests (should be 15/15)
./test_mandatory.sh

# 3. Stress test (should be 100% success)
./stress_test.sh 50 "5 800 200 200 7"

# 4. Check edge cases
./test_edge_cases.sh

# 5. Verify fair meal distribution
./count_meals.sh 5 800 200 200 20
```

If all pass ✅ - you're good to go!

## 💡 Pro Tips

1. **Start with mandatory tests** - They're the most important
2. **Use stress tests** - 1 pass doesn't mean it always works
3. **Check meal fairness** - Variance should be ≤ 5
4. **Test edge cases** - Don't assume your error handling works
5. **Run tests multiple times** - Race conditions are sneaky

## 🔗 More Information

- `TEST_README.md` - Full documentation
- `EXAMPLES.md` - Example outputs
- Each script has `--help` (not implemented yet but shows usage with no args)

## ⚡ One-Line Test Commands

```bash
# Quick validation
./test_mandatory.sh

# Deep analysis
./count_meals.sh 5 800 200 200 7

# Stress test
./stress_test.sh 50 "5 800 200 200 7"

# Everything
./run_all_tests.sh
```

---

**Remember:** A correct philosophers implementation should:
- ✅ Pass all mandatory tests (15/15)
- ✅ Have 100% success rate in stress tests
- ✅ Distribute meals fairly (variance ≤ 5)
- ✅ Detect deaths within 10ms
- ✅ Never deadlock or hang

Good luck! 🍝🍴
