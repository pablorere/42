#include "./include/functions.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();		// Readline: nueva línea
	rl_replace_line("", 0); // Limpiar la línea actual
	rl_redisplay();			// Mostrar nuevo prompt
}

void setupsignals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	// Configurar manejador para SIGINT (Ctrl+C)
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	// Ignorar SIGQUIT (Ctrl+\)
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}