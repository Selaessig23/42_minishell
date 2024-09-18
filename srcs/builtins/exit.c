#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "exit"
 * which should work similar to the bash-function
 * of same name is created
 */


/**
 * @brief function to execute the builtin function "exit"
 * exit closes the programm and frees all allocated memory
 * 
 * @param big big big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param prompt string that has to be freed before exit the program
 */
void	ft_exit_minishell(t_big *big, char *prompt)
{
	free(prompt);
	prompt = NULL;
	free_t_big(big);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}