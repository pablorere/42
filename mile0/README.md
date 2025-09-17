# Mile 0 - Foundation 🚀

**Core Rank: 00-01**

Welcome to Mile 0, the foundation phase of the 42 curriculum! This is where your journey into serious C programming begins.

## 🎯 Learning Objectives

By the end of Mile 0, you will have:

- ✅ Mastered fundamental C programming concepts
- ✅ Understood memory management and pointer manipulation
- ✅ Created your first comprehensive C library
- ✅ Learned proper code documentation and 42 coding standards
- ✅ Implemented common algorithms and data structures

## 📚 Projects

### [Libft](./libft/) - Your C Library
**Score: 125/125** ⭐

The cornerstone project of Mile 0, where you recreate essential functions from the C standard library and implement additional utility functions.

#### Part 1 - Libc Functions
Recreate these standard C library functions:

**Character Classification & Conversion:**
- `ft_isalpha` - Check if character is alphabetic
- `ft_isdigit` - Check if character is a digit
- `ft_isalnum` - Check if character is alphanumeric
- `ft_isascii` - Check if character is ASCII
- `ft_isprint` - Check if character is printable
- `ft_toupper` - Convert to uppercase
- `ft_tolower` - Convert to lowercase

**String Manipulation:**
- `ft_strlen` - Calculate string length
- `ft_strlcpy` - Safe string copy
- `ft_strlcat` - Safe string concatenation
- `ft_strchr` - Find character in string
- `ft_strrchr` - Find character in string (reverse)
- `ft_strncmp` - Compare strings
- `ft_strnstr` - Find substring
- `ft_strdup` - Duplicate string

**Memory Operations:**
- `ft_memset` - Fill memory with constant byte
- `ft_bzero` - Zero memory
- `ft_memcpy` - Copy memory area
- `ft_memmove` - Move memory area (handles overlap)
- `ft_memchr` - Scan memory for character
- `ft_memcmp` - Compare memory areas

**Conversion & Allocation:**
- `ft_atoi` - String to integer
- `ft_calloc` - Allocate and zero memory

#### Part 2 - Additional Functions
Custom utility functions not in the standard library:

- `ft_substr` - Extract substring
- `ft_strjoin` - Concatenate strings
- `ft_strtrim` - Trim characters from string
- `ft_split` - Split string by delimiter
- `ft_itoa` - Integer to string
- `ft_strmapi` - Apply function to each character
- `ft_striteri` - Apply function to each character (with index)

**File Descriptor Functions:**
- `ft_putchar_fd` - Output character to fd
- `ft_putstr_fd` - Output string to fd
- `ft_putendl_fd` - Output string + newline to fd
- `ft_putnbr_fd` - Output number to fd

#### Bonus Part - Linked Lists
Implement linked list data structure and operations:

- `ft_lstnew` - Create new list element
- `ft_lstadd_front` - Add element to front
- `ft_lstsize` - Count list elements
- `ft_lstlast` - Get last element
- `ft_lstadd_back` - Add element to back
- `ft_lstdelone` - Delete one element
- `ft_lstclear` - Delete entire list
- `ft_lstiter` - Apply function to each element
- `ft_lstmap` - Apply function and create new list

## 🛠 Technical Skills Developed

### Memory Management
- Understanding the heap vs stack
- Dynamic memory allocation with `malloc`
- Proper memory deallocation with `free`
- Preventing memory leaks
- Handling null pointers

### Pointer Manipulation
- Pointer arithmetic
- Pointers to pointers
- Function pointers
- Void pointers and casting

### Data Structures
- Linked lists implementation
- Node creation and traversal
- Memory management in data structures

### Build Systems
- Writing Makefiles
- Compilation flags and optimization
- Static library creation with `ar`
- Header file organization

## 📋 Evaluation Criteria

### Mandatory Requirements
- ✅ All functions must follow 42 Norm
- ✅ No memory leaks (checked with Valgrind)
- ✅ Proper error handling
- ✅ Makefile with all required rules
- ✅ Functions behave identically to their libc counterparts

### Bonus Requirements
- ✅ All mandatory parts completed perfectly
- ✅ Linked list functions fully implemented
- ✅ Proper list memory management

### Common Mistakes to Avoid
- ❌ Segmentation faults
- ❌ Memory leaks
- ❌ Incorrect function behavior
- ❌ Norm violations
- ❌ Missing edge case handling

## 🎯 Tips for Success

### Code Quality
1. **Follow the Norm religiously** - Use Norminette early and often
2. **Test extensively** - Create comprehensive test cases
3. **Handle edge cases** - NULL pointers, empty strings, boundary conditions
4. **Document your code** - Clear variable names and logical structure

### Testing Strategy
1. **Unit tests** - Test each function individually
2. **Integration tests** - Test functions working together  
3. **Memory tests** - Use Valgrind to check for leaks
4. **Comparison tests** - Compare output with real libc functions

### Debugging
1. **Use GDB** - Learn to debug with the GNU debugger
2. **Print debugging** - Strategic printf statements
3. **Valgrind** - Memory error detection
4. **Static analysis** - Code review and peer evaluation

## 🚀 Next Steps

After completing Mile 0, you'll be ready for:
- **Mile 1** - Advanced string processing with ft_printf and get_next_line
- More complex algorithms and data structures
- System programming concepts
- Graphics programming

## 📚 Recommended Resources

### C Programming
- "The C Programming Language" by Kernighan & Ritchie
- [C Reference](https://en.cppreference.com/w/c)
- [42 Norm](https://github.com/42School/norminette)

### Tools
- [Valgrind Documentation](https://valgrind.org/docs/manual/)
- [GDB Tutorial](https://www.gnu.org/software/gdb/documentation/)
- [Makefile Tutorial](https://makefiletutorial.com/)

---

**Remember:** The goal isn't just to pass the project, but to truly understand the fundamental concepts that will serve as the foundation for everything that follows in your 42 journey!