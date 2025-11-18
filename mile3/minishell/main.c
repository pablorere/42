#include "./include/functions.h"

/*
** Step 1: Initialize the shell environment
** - Use sigaction to handle SIGINT and SIGQUIT signals.
** - Check if the terminal is interactive using isatty.
**
** Step 2: Start a loop to keep the terminal open
** - Use a while loop to continuously prompt the user for input.
**
** Step 3: Handle user input
** - Use readline to get the input from the user.
** - Add the input to the history using add_history.
** - Check for empty input and continue the loop if necessary.
**
** Step 4: Parse the input
** - Tokenize the input string using strtok or a custom parser.
** - Handle special characters like pipes (|), redirections (>, <), etc.
**
** Step 5: Execute the commands
** - Check if the command is a built-in (e.g., cd, echo, exit) and execute it.
** - If not, fork a new process using fork and use execve to execute external commands.
** - Handle errors and return values appropriately.
**
** Step 6: Clean up and prepare for the next iteration
** - Free any dynamically allocated memory using free.
** - Reset any modified file descriptors (e.g., after redirection) using dup2.
**
** Step 7: Exit the shell
** - Break the loop when the user enters the exit command.
** - Perform any necessary cleanup before exiting using exit.
*/

void parseinput(char *input)
{
	char **argv = ft_split(input, ' ');
	if (!argv)
		return ;
	if (ft_strncmp(argv[0], "exit", 4) == 0)
	{
		rl_clear_history();
		free_split(argv);
		if (!argv[1])
			exit(0);
		exit(ft_atoi(argv[1]));
	}
	free_split(argv);
}

int main(void)
{
	char *string;
	char *prompt;
	char cwd[1024];

	string = NULL;
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			prompt = ft_strjoin(cwd, "$ ");
			if (!prompt)
				prompt = ft_strdup("minishell$ ");
		}
		else
			prompt = ft_strdup("minishell$ ");
		string = readline(prompt);
		free(prompt);
		if (!string)
		{
			rl_clear_history();
			return (0);
		}
		parseinput(string);
		add_history(string);
		free(string);
	}
	return (0);
}
/*
	liberar el readline, pasar eof a readline para ver si \
	 rompe (en una linea vacia y una linea con contenido)

*/