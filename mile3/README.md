# Mile 3 - System Programming & Concurrency 🧠

**Core Rank: 03-04**

Mile 3 introduces advanced system programming concepts, focusing on multi-threading, process synchronization, and concurrent programming challenges.

## 🎯 Learning Objectives

By the end of Mile 3, you will have:

- ✅ Mastered multi-threading and thread synchronization
- ✅ Understood concurrent programming challenges and solutions
- ✅ Implemented deadlock prevention mechanisms
- ✅ Learned advanced system programming concepts
- ✅ Developed skills in parallel processing and resource management

## 📚 Projects

### [philosophers](./philosophers/) - The Dining Philosophers Problem

A classic computer science problem that teaches thread synchronization, resource sharing, and deadlock prevention.

#### 🎯 Objective
Simulate the dining philosophers problem where N philosophers sit around a table, alternating between eating, thinking, and sleeping, while sharing N forks between them.

#### 📝 The Problem
**Setup:**
- N philosophers sit around a circular table
- N forks are placed between philosophers (one between each pair)
- Philosophers alternate between three states: eating, thinking, sleeping
- A philosopher needs TWO forks to eat
- Philosophers cannot communicate with each other

**Rules:**
- A philosopher must pick up both adjacent forks to eat
- After eating, they put down both forks and sleep
- After sleeping, they think
- A philosopher dies if they don't start eating within `time_to_die` ms
- The simulation stops when a philosopher dies

#### 📝 Program Requirements
**Usage:**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers` - Number of philosophers (and forks)
- `time_to_die` - Time in ms after which a philosopher dies if not eating
- `time_to_eat` - Time in ms a philosopher spends eating
- `time_to_sleep` - Time in ms a philosopher spends sleeping
- `[optional]` - Number of times each philosopher must eat to end simulation

#### 🛠 Technical Concepts

**Threading Concepts:**
- **pthread_create** - Creating threads for each philosopher
- **pthread_join** - Waiting for thread completion
- **pthread_detach** - Managing thread lifecycle
- **Thread safety** - Protecting shared resources

**Synchronization Primitives:**
- **Mutexes** - Protecting shared resources (forks, output)
- **pthread_mutex_lock/unlock** - Critical section protection
- **pthread_mutex_init/destroy** - Mutex lifecycle management
- **Atomic operations** - Safe variable access

**Concurrent Programming:**
- **Race conditions** - Multiple threads accessing shared data
- **Deadlock prevention** - Avoiding circular wait conditions
- **Resource allocation** - Fair distribution of limited resources
- **Timing precision** - Accurate time measurements and delays

#### 🎯 Key Challenges

**Deadlock Prevention:**
- **Problem:** All philosophers pick up left fork simultaneously
- **Solutions:** 
  - Asymmetric approach (odd/even philosophers)
  - Resource ordering
  - Timeout mechanisms

**Race Condition Management:**
- **Problem:** Multiple threads accessing shared state
- **Solution:** Proper mutex usage and critical sections

**Timing Accuracy:**
- **Problem:** Precise timing for death detection
- **Solution:** High-resolution timers and regular monitoring

**Resource Sharing:**
- **Problem:** Fair fork distribution
- **Solution:** Proper synchronization and allocation strategies

#### 💡 Implementation Strategies

**Basic Approach:**
1. Create one thread per philosopher
2. Use mutexes to represent forks
3. Implement eating, sleeping, thinking cycle
4. Monitor for death conditions

**Advanced Optimizations:**
- **Monitoring Thread** - Separate thread for death detection
- **State Tracking** - Efficient philosopher state management
- **Performance Tuning** - Minimize unnecessary delays

## 🛠 Technical Skills Developed

### Multi-Threading
- **Thread Creation** - Managing multiple concurrent threads
- **Thread Synchronization** - Coordinating thread execution
- **Thread Communication** - Safe data sharing between threads
- **Thread Lifecycle** - Proper creation, execution, and cleanup

### Synchronization Mechanisms
- **Mutexes** - Mutual exclusion for resource protection
- **Critical Sections** - Protecting shared code segments
- **Atomic Operations** - Thread-safe variable operations
- **Deadlock Prevention** - Avoiding system-wide blocks

### System Programming
- **High-Resolution Timing** - Precise time measurements
- **Memory Management** - Thread-safe allocation and deallocation
- **Error Handling** - Robust error management in concurrent systems
- **System Resources** - Efficient resource utilization

### Concurrent Algorithm Design
- **Resource Allocation** - Fair distribution strategies
- **State Management** - Consistent state across threads
- **Performance Optimization** - Minimizing contention and delays
- **Scalability** - Handling varying numbers of philosophers

## 📋 Evaluation Criteria

### Mandatory Requirements
- ✅ No philosopher should die (unless intended)
- ✅ Philosophers alternate between eating, sleeping, thinking
- ✅ Proper fork sharing (no philosopher eats without 2 forks)
- ✅ Accurate timing and death detection
- ✅ Thread-safe output and resource access

### Performance Requirements
- ✅ Handle 1-200 philosophers efficiently
- ✅ Accurate timing within 10ms precision
- ✅ No unnecessary delays or busy waiting
- ✅ Proper resource cleanup on termination

### Common Mistakes to Avoid
- ❌ Data races on shared variables
- ❌ Deadlock conditions
- ❌ Inaccurate timing calculations
- ❌ Memory leaks with threads
- ❌ Improper mutex usage

## 🎯 Tips for Success

### Design Strategy
1. **Understand the Problem** - Study the classic dining philosophers
2. **Start Simple** - Implement basic version first
3. **Add Synchronization** - Introduce mutexes gradually
4. **Test Edge Cases** - Single philosopher, large numbers

### Implementation Tips
1. **Use Proper Data Structures** - Organize philosopher and fork data
2. **Implement Monitoring** - Separate death detection logic
3. **Handle Timing Carefully** - Use microsecond precision
4. **Test Thoroughly** - Various philosopher counts and timings

### Debugging Concurrent Code
1. **Use Thread Debugging Tools** - GDB with thread support
2. **Add Logging** - Trace thread execution (with locks!)
3. **Test Race Conditions** - Stress test with many iterations
4. **Verify Synchronization** - Ensure proper mutex usage

## 🔧 Common Challenges & Solutions

### Deadlock Issues
- **Challenge:** All philosophers grab one fork and wait
- **Solution:** Implement asymmetric fork pickup or resource ordering

### Race Conditions
- **Challenge:** Multiple threads modifying shared data
- **Solution:** Proper mutex protection around critical sections

### Timing Precision
- **Challenge:** Accurate death detection timing
- **Solution:** Use high-resolution timers and regular monitoring

### Performance Bottlenecks
- **Challenge:** Excessive mutex contention
- **Solution:** Minimize critical section size and duration

## 🚀 Advanced Concepts

### Bonus Implementation
- **Semaphores** - Alternative synchronization primitive
- **Process-based** - Using processes instead of threads
- **Advanced Algorithms** - More sophisticated resource allocation

### Real-World Applications
- **Database Systems** - Transaction management and locking
- **Operating Systems** - Process scheduling and resource allocation
- **Distributed Systems** - Consensus algorithms and coordination
- **Parallel Computing** - Load balancing and task distribution

## 📚 Recommended Resources

### Threading & Synchronization
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [The Little Book of Semaphores](https://greenteapress.com/wp/semaphores/)
- [Concurrent Programming](https://pages.cs.wisc.edu/~remzi/OSTEP/)

### Debugging Tools
- [GDB Thread Debugging](https://sourceware.org/gdb/wiki/NonStopMode)
- [Valgrind Helgrind](https://valgrind.org/docs/manual/hg-manual.html)
- [Thread Sanitizer](https://clang.llvm.org/docs/ThreadSanitizer.html)

### Algorithm Resources
- [Dining Philosophers Solutions](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Deadlock Prevention](https://www.geeksforgeeks.org/deadlock-prevention/)

---

**Remember:** Mile 3 represents a significant step up in complexity. You're now dealing with one of the most challenging aspects of programming - concurrent systems. Take your time to understand the concepts deeply, as these skills are crucial for modern system programming and will serve you throughout your career!

The dining philosophers problem is not just an academic exercise - it represents real-world challenges in resource management, database systems, and distributed computing. Master this, and you'll have a solid foundation for advanced system programming!