#pragma once
// readline library
#include <readline/readline.h>
#include <readline/history.h>

#include "./libft/libft.h"
// Standard I/O
#include <stdio.h>

// Memory management
#include <stdlib.h>

// File operations
#include <unistd.h>
#include <fcntl.h>

// Process management
#include <sys/types.h>
#include <sys/wait.h>

// Signal handling
#include <signal.h>

// File status
#include <sys/stat.h>
#include <dirent.h>

// Error handling
#include <string.h>
#include <errno.h>

// Terminal control
#include <termios.h>
#include <curses.h>
#include <term.h>

// Function prototypes
void	free_split(char **split);

/*
	make file needs :
	-lreadline
*/
