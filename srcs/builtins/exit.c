#include "minishell.h"

/**
 * DESCRIPTION
 * 
 */


/**
 * @brief function to execute the builtin function "exit"
 * exit closes the programm and frees all allocated memory
 * 
 * @param 
 */
void    ft_exit_minishell(t_big *big, char *prompt)
{
			// ft_free(input_arr);
			free(prompt);
			prompt = NULL;
			free_t_big(big);
			// ft_free_ll(&comm);
			rl_clear_history();
			exit(EXIT_SUCCESS);
}