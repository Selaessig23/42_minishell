/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:24:46 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 11:39:53 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signalnum = 0;

/**
 * @brief Infinite loop to continuously query and process user input
 * using the 'readline' function. 
 * The condition if (!input) occurs when the readline function returns NULL. 
 * This usually happens when the end-of-file (EOF) is reached, typically because 
 * the user pressed Ctrl+D (EOF) in the terminal. Exit normally.
 * Inside the loop parsing and executing is organised. 
 * If the global signalvariable g_signalnum != 0, 
 * there was a signal (in rl-loop, heredoc or execution)
 * Before opening a new prompt, the previous command line input
 * has to be freed and the command total resetted
 * 
 * @param big struct with all necessary information to run a command
 */
static void	minishell_is_running(t_big	*big)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_handle_signals(false);
		input = readline("minishell$ ");
		ft_handle_signals(true);
		if (!input)
			ft_exit_minishell(big, true);
		else if (!*input || ft_spacetabchecker(input))
			free(input);
		else if (*input)
		{
			add_history(input);
			if (minishell_parsing(input, big) && g_signalnum != 1)
				ft_executer(big);
		}
		if (g_signalnum == 1)
			signal_set_exitcode_and_reset(big);
		ft_free_cl(&(big->cmdlist));
		big->count_commds = 0;
		big->exe = true;
	}
}

/**
 * Infinite loop to continuously query and process user input
 * using the 'readline' function. Inside a loop there are three 'if' statements.
 * 
 * The condition if (!input) occurs when the readline function returns NULL. 
 * This usually happens when the end-of-file (EOF) is reached, typically because 
 * the user pressed Ctrl+D (EOF) in the terminal. Exit normally.
 * 
 *  ft_welcome();
 */
int	main(int argc, char **argv, char **envp)
{
	t_big	*big;

	(void)argv;
	rl_catch_signals = 0;
	if (argc != 1)
		error_and_exit(1);
	else if (argc == 1)
	{
		big = init_t_big(envp);
		minishell_is_running(big);
	}
	exit(0);
}
