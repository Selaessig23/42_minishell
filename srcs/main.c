/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:24:46 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 19:24:46 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signalnum = 0;

static void	procced_and_execute(t_big *big, char *input)
{
	char **input_arr;
				
	input_arr = NULL;
	add_history(input);
	input_arr = create_nodes(&input);
	free(input);
	input = NULL;
	if (input_arr != NULL)
	{
		t_list	*lexx;
		
		lexx = NULL;
		lexx = ft_tokenizer(input_arr);
		ft_free(input_arr);
		if (!ft_syntax(lexx))
		{
			ft_expa_precond(lexx, big);
			ft_commands(lexx, &big);
			ft_free_ll(&lexx);
			if (g_signalnum != 1)
				ft_executer(big);
		}
		else
		{
			big->exit_code = 2;
			ft_free_ll(&lexx);
		}
	}
	if (g_signalnum == 1)
	{
		g_signalnum = 0;
		big->exit_code = 130;
		ft_free_cl(&(big->cmdlist));
		big->count_commds = 0;
	}
}

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
		{
			int		exitcode;
			
			ft_putstr_fd("exit\n", 1);
			exitcode = big->exit_code;
			free_t_big(big);
			rl_clear_history();
			exit(exitcode);
		}
		else if (!*input || ft_spacetabchecker(input))
			free(input);
		else if (*input)
			procced_and_execute(big, input);
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
	(void)argv;

	rl_catch_signals = 0;
	//ft_welcome();
	if (argc != 1)
		error_and_exit(1);
	else if (argc == 1)
	{
		t_big	*big;
		
		big = init_t_big(envp);
		minishell_is_running(big);
	}
	exit(0);
}
