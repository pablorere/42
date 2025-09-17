# Mile 2 - Algorithms & Graphics 🎮

**Core Rank: 02-03**

Mile 2 introduces you to algorithmic thinking, data structures, graphics programming, and system-level process management.

## 🎯 Learning Objectives

By the end of Mile 2, you will have:

- ✅ Designed and optimized sorting algorithms
- ✅ Created interactive graphical applications
- ✅ Mastered process creation and inter-process communication
- ✅ Understood event-driven programming
- ✅ Implemented efficient data structures and algorithms

## 📚 Projects

### [push_swap](./push_swap/) - Sorting Algorithm Challenge

Design the most efficient algorithm to sort a stack using only specific operations with two stacks.

#### 🎯 Objective
Sort a stack of integers using the minimum number of operations, with only two stacks (A and B) and a limited set of allowed operations.

#### 📝 Allowed Operations
**Stack Operations:**
- `sa` - Swap first two elements of stack A
- `sb` - Swap first two elements of stack B  
- `ss` - Execute sa and sb simultaneously
- `pa` - Push first element from B to A
- `pb` - Push first element from A to B
- `ra` - Rotate stack A (first element becomes last)
- `rb` - Rotate stack B (first element becomes last)
- `rr` - Execute ra and rb simultaneously
- `rra` - Reverse rotate stack A (last element becomes first)
- `rrb` - Reverse rotate stack B (last element becomes first)
- `rrr` - Execute rra and rrb simultaneously

#### 🛠 Technical Concepts
**Algorithm Design:**
- Stack-based sorting strategies
- Optimization for different input sizes
- Move count minimization
- Pattern recognition in data

**Data Structures:**
- Linked list implementation for stacks
- Stack operations (push, pop, rotate)
- Memory efficient implementations

#### 🎯 Performance Requirements
- **3 numbers:** ≤ 3 operations
- **5 numbers:** ≤ 12 operations  
- **100 numbers:** ≤ 700 operations (5 points), ≤ 900 (4 points), ≤ 1100 (3 points)
- **500 numbers:** ≤ 5500 operations (5 points), ≤ 7000 (4 points), ≤ 8500 (3 points)

---

### [so_long](./so_long/) - 2D Game Development

Create a small 2D game where a character collects items and finds an exit, introducing you to graphics programming.

#### 🎯 Objective
Build a 2D top-down game using the MiniLibX graphics library, handling player movement, collectibles, and win conditions.

#### 📝 Game Requirements
**Core Mechanics:**
- Player can move with WASD or arrow keys
- Player must collect all collectibles before exiting
- Display move count in terminal
- Game ends when player reaches exit with all collectibles

**Map Requirements:**
- Rectangular map enclosed by walls ('1')
- At least one exit ('E'), one collectible ('C'), one starting position ('P')
- Map validation (valid path, proper formatting)

#### 🛠 Technical Concepts
**Graphics Programming:**
- Sprite rendering and management
- Event handling (keyboard input)
- Game loop implementation
- Image loading and display

**Game Development:**
- Collision detection
- State management
- Asset management
- User interface basics

#### 🎨 Visual Elements
- **Player Character** - Animated sprite
- **Collectibles** - Items to gather
- **Walls** - Impassable obstacles
- **Floor** - Walkable terrain
- **Exit** - Goal location

---

### [pipex](./pipex/) - Unix Pipes Implementation

Recreate the behavior of shell pipes, managing process creation and inter-process communication.

#### 🎯 Objective
Simulate the shell command `< file1 cmd1 | cmd2 > file2` by creating processes and establishing communication between them.

#### 📝 Requirements
**Basic Functionality:**
```bash
./pipex file1 cmd1 cmd2 file2
# Equivalent to: < file1 cmd1 | cmd2 > file2
```

**Bonus Features:**
- Multiple pipes: `./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2`
- Here_doc support: `./pipex here_doc LIMITER cmd1 cmd2 file`

#### 🛠 Technical Concepts
**Process Management:**
- Fork system calls
- Process creation and termination
- Parent-child process relationships
- Wait and exit status handling

**Inter-Process Communication:**
- Pipe creation and management
- File descriptor redirection
- Standard input/output manipulation
- Data flow between processes

**System Programming:**
- Execve family functions
- Environment variable handling
- File operations and permissions
- Error handling and cleanup

## 🛠 Technical Skills Developed

### Algorithm Design & Analysis
- **Sorting Algorithms** - Custom stack-based approaches
- **Optimization Techniques** - Move count minimization
- **Complexity Analysis** - Time and space complexity
- **Pattern Recognition** - Identifying optimal strategies

### Graphics Programming
- **2D Graphics** - Sprite rendering and animation
- **Event Handling** - User input processing
- **Game Architecture** - Loop structures and state management
- **Asset Management** - Image loading and memory management

### System Programming
- **Process Control** - Fork, exec, wait
- **File Descriptors** - Redirection and piping
- **System Calls** - Low-level system interaction
- **Error Handling** - Robust error management

### Data Structures
- **Stacks** - Implementation and operations
- **Linked Lists** - Dynamic data structures
- **Trees** - For pathfinding algorithms
- **Memory Management** - Efficient allocation strategies

## 📋 Evaluation Criteria

### push_swap Requirements
- ✅ Correct sorting with valid operations only
- ✅ Meet performance benchmarks
- ✅ Handle edge cases (duplicates, sorted input)
- ✅ Proper error handling
- ✅ Memory management

### so_long Requirements
- ✅ Functional 2D game with all mechanics
- ✅ Proper map validation
- ✅ Smooth graphics and input handling
- ✅ No memory leaks or crashes
- ✅ ESC key and window close handling

### pipex Requirements
- ✅ Correct pipe behavior simulation
- ✅ Proper process management
- ✅ File permission and error handling
- ✅ Memory and file descriptor cleanup
- ✅ Command execution and path resolution

## 🎯 Tips for Success

### push_swap Strategy
1. **Start Small** - Master sorting 3-5 elements first
2. **Analyze Patterns** - Study efficient sorting strategies
3. **Optimize Incrementally** - Improve algorithm step by step
4. **Test Extensively** - Various input sizes and patterns

### so_long Strategy
1. **Plan Your Game** - Design before coding
2. **Test Graphics Early** - Ensure MiniLibX works properly
3. **Implement Incrementally** - Basic movement first, then features
4. **Handle Edge Cases** - Invalid maps, key combinations

### pipex Strategy
1. **Understand Pipes** - Learn how shell pipes work
2. **Test with Simple Commands** - Start with basic operations
3. **Handle Errors Gracefully** - Invalid files, commands, permissions
4. **Debug Process Issues** - Use system tools to monitor processes

## 🔧 Common Challenges & Solutions

### Algorithm Optimization
- **Challenge:** Achieving required operation counts
- **Solution:** Study sorting patterns, implement multiple strategies

### Graphics Performance
- **Challenge:** Smooth animation and responsive input
- **Solution:** Efficient rendering, proper event loop structure

### Process Synchronization
- **Challenge:** Coordinating multiple processes
- **Solution:** Proper wait handling, file descriptor management

## 🚀 Next Steps

After completing Mile 2, you'll be ready for:
- **Mile 3** - Advanced system programming and concurrency
- **Threading** - Parallel processing concepts
- **Network Programming** - Distributed systems
- **Advanced Algorithms** - Complex problem solving

## 📚 Recommended Resources

### Algorithms
- [Sorting Algorithms Visualizer](https://www.sortingalgorithms.com/)
- [Algorithm Analysis](https://www.khanacademy.org/computing/computer-science/algorithms)

### Graphics Programming
- [MiniLibX Documentation](https://github.com/42Paris/minilibx-linux)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)

### System Programming
- [Unix Programming](https://www.gnu.org/software/libc/manual/)
- [Process Management](https://www.tutorialspoint.com/unix/unix-processes.htm)

---

**Remember:** Mile 2 challenges you to think both creatively and systematically. Each project builds different aspects of your programming toolkit - algorithmic thinking, visual programming, and system-level understanding. Master these concepts, and you'll be ready for advanced system programming!