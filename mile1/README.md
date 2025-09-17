# Mile 1 - String Manipulation & I/O 📈

**Core Rank: 01-02**

Mile 1 builds upon your libft foundation to explore advanced string processing, formatted output, and file I/O operations.

## 🎯 Learning Objectives

By the end of Mile 1, you will have:

- ✅ Implemented variadic functions and format specifiers
- ✅ Mastered file I/O and line-by-line processing
- ✅ Understood static variables and their applications
- ✅ Optimized memory usage and buffer management
- ✅ Handled complex parsing and formatting tasks

## 📚 Projects

### [ft_printf](./ft_printf/) - Custom Printf Implementation

Your own implementation of the famous `printf` function, handling various format specifiers and edge cases.

#### 🎯 Objective
Create a function that mimics the behavior of `printf` from the C standard library, handling multiple format specifiers and returning the number of characters printed.

#### 📝 Requirements
**Mandatory Format Specifiers:**
- `%c` - Single character
- `%s` - String
- `%p` - Pointer address (hexadecimal)
- `%d` - Signed decimal integer
- `%i` - Signed integer (same as %d)
- `%u` - Unsigned decimal integer
- `%x` - Unsigned hexadecimal (lowercase)
- `%X` - Unsigned hexadecimal (uppercase)
- `%%` - Literal percent sign

**Function Prototype:**
```c
int ft_printf(const char *format, ...);
```

#### 🛠 Technical Concepts

**Variadic Functions:**
- Using `va_list`, `va_start`, `va_arg`, `va_end`
- Handling variable number of arguments
- Type safety considerations

**Format Parsing:**
- String parsing and state machines
- Format specifier identification
- Argument type detection

**Number Base Conversion:**
- Decimal to hexadecimal conversion
- Handling signed/unsigned integers
- Pointer address formatting

#### 🎯 Key Challenges
1. **Buffer Management** - Efficient character output
2. **Type Handling** - Correct argument extraction
3. **Edge Cases** - NULL pointers, zero values, empty strings
4. **Performance** - Minimizing function calls

---

### [get_next_line](./get_next_line/) - File Reading Utility

A function that reads a file line by line, perfect for processing large files efficiently.

#### 🎯 Objective
Create a function that returns one line at a time from a file descriptor, handling any line length and multiple file descriptors simultaneously.

#### 📝 Requirements
**Function Prototype:**
```c
char *get_next_line(int fd);
```

**Behavior:**
- Returns one line ending with `\n` (if present)
- Returns the line without `\n` if it's the last line
- Returns `NULL` when EOF is reached or on error
- Handles multiple file descriptors simultaneously (bonus)

#### 🛠 Technical Concepts

**Static Variables:**
- Persistent data between function calls
- Managing state across multiple invocations
- Memory cleanup considerations

**Buffer Management:**
- Optimal buffer size (BUFFER_SIZE)
- Handling partial reads
- String concatenation and reallocation

**File I/O:**
- Using `read()` system call
- File descriptor management
- Error handling and EOF detection

#### 🎯 Key Challenges
1. **Memory Efficiency** - Minimal memory allocation
2. **Line Detection** - Finding newline characters
3. **Multiple FDs** - Managing multiple files (bonus)
4. **Edge Cases** - Empty files, long lines, binary files

## 🛠 Technical Skills Developed

### Advanced C Concepts
- **Variadic Functions** - Handling variable arguments
- **Static Variables** - Persistent function state
- **File I/O** - System calls and file descriptors
- **String Processing** - Advanced parsing and manipulation

### Memory Management
- **Dynamic Allocation** - Efficient memory usage
- **String Concatenation** - Growing strings dynamically
- **Memory Cleanup** - Preventing leaks with static variables
- **Buffer Optimization** - Choosing optimal buffer sizes

### Algorithm Design
- **State Machines** - Format parsing logic
- **Stream Processing** - Line-by-line file reading
- **String Algorithms** - Search and manipulation
- **Performance Optimization** - Minimizing system calls

## 📋 Evaluation Criteria

### ft_printf Requirements
- ✅ Handle all mandatory format specifiers
- ✅ Return correct character count
- ✅ No crashes with invalid input
- ✅ Proper variadic function implementation
- ✅ Match printf behavior exactly

### get_next_line Requirements
- ✅ Read files line by line correctly
- ✅ Handle any line length
- ✅ Proper memory management
- ✅ Work with different buffer sizes
- ✅ Handle edge cases gracefully

### Common Mistakes to Avoid
- ❌ Memory leaks with static variables
- ❌ Incorrect format specifier handling
- ❌ Buffer overflow vulnerabilities
- ❌ Improper file descriptor handling
- ❌ Wrong character count in ft_printf

## 🎯 Tips for Success

### ft_printf Strategy
1. **Start Simple** - Implement basic specifiers first
2. **Test Incrementally** - Compare with real printf
3. **Handle Edge Cases** - NULL pointers, empty strings
4. **Optimize Later** - Focus on correctness first

### get_next_line Strategy
1. **Choose Buffer Size Wisely** - Balance memory and performance
2. **Test with Various Files** - Different line lengths and endings
3. **Handle Static Variables Carefully** - Proper cleanup on EOF
4. **Consider Multiple FDs** - If implementing bonus part

### Testing Approach
1. **Unit Testing** - Test each function individually
2. **Integration Testing** - Test with real files and programs
3. **Edge Case Testing** - Empty files, large files, binary files
4. **Memory Testing** - Valgrind for leak detection

## 🔧 Debugging Tips

### Common Issues
- **Segmentation Faults** - Check pointer validity
- **Memory Leaks** - Especially with static variables
- **Infinite Loops** - File reading without EOF check
- **Format Errors** - Incorrect specifier parsing

### Debugging Tools
- **GDB** - Step through code execution
- **Valgrind** - Memory leak detection
- **Printf Debugging** - Strategic output statements
- **File Comparison** - Compare with system printf

## 🚀 Next Steps

After completing Mile 1, you'll be ready for:
- **Mile 2** - Complex algorithms and data structures
- **Graphics Programming** - Visual applications
- **System Programming** - Process management
- **Network Programming** - Inter-process communication

## 📚 Recommended Resources

### Variadic Functions
- [C Variadic Functions](https://en.cppreference.com/w/c/variadic)
- [printf Format Specifiers](https://www.cplusplus.com/reference/cstdio/printf/)

### File I/O
- [Unix File I/O](https://www.gnu.org/software/libc/manual/html_node/I_002fO-Overview.html)
- [File Descriptors](https://www.bottomupcs.com/file_descriptors.xhtml)

### Testing Resources
- [Printf Tester](https://github.com/tripouille/printfTester)
- [GNL Tester](https://github.com/tripouille/gnlTester)

---

**Remember:** These projects teach you to think like a system programmer, handling low-level details while maintaining clean, efficient code. Master these concepts, and you'll be well-prepared for the challenges ahead!