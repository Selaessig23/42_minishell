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
 * @brief function to reset the global variable
 * g_signalnum (it is only set to !0 if a signal was used)
 * and defines the exit code in case of a signal
 * 
 * @brief big struct with all necessary information to run a command, 
 * exit_codes are saved here
 */
void	signal_set_exitcode_and_reset(t_big *big)
{
	g_signalnum = 0;
	big->exit_code = 130;
}

/**
 * @brief this function organises the parsing part
 * (the preparation of command line input for execution)
 * 1st an array of strings (input_arr) is created out of 
 * the readline input (all keywords are seperated here)
 * 2nd the array of strings is trasnformed into a
 * linked list and each node get a token describing
 * the type of the input-keyword
 * 3rd check for syntax errors
 * 4th a linked list for execution is created (ft_commands)
 * 
 * @param input the command line input from readline
 * @param big struct with all necessary information to run a command, 
 * the linked list of commands is saved here
 */
int	minishell_parsing(char *input, t_big *big)
{
	char	**input_arr;
	t_list	*lexx;

	lexx = NULL;
	input_arr = create_cleanarr(&input);
	free(input);
	input = NULL;
	if (!input_arr)
		return (0);
	lexx = ft_tokenizer(input_arr);
	ft_free(input_arr);
	input_arr = NULL;
	if (!lexx || ft_syntax(lexx))
	{
		big->exit_code = 2;
		ft_free_ll(&lexx);
		return (0);
	}
	ft_expa_precond(lexx, big);
	ft_commands(lexx, &big);
	ft_free_ll(&lexx);
	return (1);
}

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
void	minishell_is_running(t_big	*big)
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
 */
int	main(int argc, char **argv, char **envp)
{
	t_big	*big;

	(void)argv;
	rl_catch_signals = 0;
	//ft_welcome();
	if (argc != 1)
		error_and_exit(1);
	else if (argc == 1)
	{
		big = init_t_big(envp);
		minishell_is_running(big);
	}
	exit(0);
}
