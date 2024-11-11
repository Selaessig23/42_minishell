/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:55:51 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 20:55:51 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "exit"
 * which should work similar to the bash-function
 * of same name is created
 */


/**
 * @brief function to execute the builtin function "exit", 
 * it closes the programm and frees all allocated memory
 * 
 * @param big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param prompt string that has to be freed before exit the program
 */
// void	ft_exit_minishell(t_data *comm_info, t_big *big, char *prompt)
// {
// 	char	**argv;
// 	char	*argv2;
// 	bool	is_nondigit;
// 	int		exit_code;

// 	argv = comm_info->cmd;
// 	argv2 = NULL;
// 	is_nondigit = 0;
// 	exit_code = 0;
// 	if (ft_arrlen(argv) >= 2)
// 	{
// 		argv2 = argv[1];
// 		if (*argv2 == '-' || *argv2 == '+')
// 			argv2 += 1;
// 		while (*argv2 && ft_isdigit(*argv2))
// 			argv2 += 1;
// 		if (*argv2 && (*argv2 - 1) != '-')
// 			is_nondigit = true;
// 	}
// 	argv = comm_info->cmd;
// 	if (ft_arrlen(argv) >= 2 && is_nondigit == false)
// 		exit_code = ft_atoi(argv[1]);
// 	exit_code = (exit_code % 256 + 256) % 256;
// 	// if (exit_code < 0)
// 	// 	exit_code += 256;
// 	// else if (exit_code > 255)
		
// 	if (ft_arrlen(argv) > 2 && is_nondigit == false)
// 	{
// 		if (big->count_commds == 1)
// 			ft_putstr_fd("exit\n", 1);
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		big->exit_code = 1;
// 	}
// 	else
// 	{
// 		if (big->count_commds == 1)
// 		{
// 			free(prompt);
// 			prompt = NULL;
// 			rl_clear_history();
// 		}
// 		if (is_nondigit == true)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			ft_putstr_fd("minishell: exit: ", 2);
// 			ft_putstr_fd((argv[1]), 2);
// 			ft_putstr_fd(": numeric argument required\n", 2);
// 			free_t_big(big);
// 			exit(2);
// 		}
// 		else if (big->count_commds == 1)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			free_t_big(big);
// 			exit(exit_code);
// 		}
// 	}
// }

/**
 * DESCRIPTION
 * in this file the inbuilt-function "exit"
 * which should work similar to the bash-function
 * of same name is created
 */
static void	exit_error_handling_only(t_big *big, char **argv, bool is_digit)
{
	if (ft_arrlen(argv) > 2 && is_digit == true)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		big->exit_code = 1;
		return ;
	}
	else if (is_digit == false)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((argv[1]), 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		big->exit_code = 2;
		return ;
	}
}

/**
 * Part of exit built-in which exit from a minishell.
 */
static void	exit_exe(char *prompt, t_big *big, char	**argv, bool is_digit)
{
	ft_putstr_fd("exit\n", 1);
	if (ft_arrlen(argv) > 2 && is_digit == true)
	{
		big->exit_code = 1;
	}
	else if (is_digit == false)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((argv[1]), 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		big->exit_code = 2;
	}
	free(prompt);
	prompt = NULL;
	rl_clear_history();
	free_t_big(big);
	exit(big->exit_code);
}

// Utils function of builtin exit which checks if
// the first  argument arg1 is a digit.
// return 1 if it is a digit
// WHAT is it? "if (*arg1 && (*arg1 - 1) != '-')""
static int	exit_utils_check_first_arg(char **argv)
{
	char	*arg1;

	arg1 = argv[1];
	if (*arg1 == '-' || *arg1 == '+')
		arg1 += 1;
	while (*arg1 && ft_isdigit(*arg1))
		arg1 += 1;
	if (*arg1 && (*arg1 - 1) != '-')
		return (0);
	else
		return (1);
}

/**
 * It does a lot different things that  original exit does.
 * It returns 1 if the first arg is a digit.
 * It check the first argument if it is a digit or not.
 * If the first argument is a digit than bool is_digit = true.
 * 
 */
static int	exit_utils(char **argv, bool is_digit, t_big *big)
{
	int	code;

	code = 0;
	if (exit_utils_check_first_arg(argv) == 1)
		is_digit = true;
	else
		is_digit = false;
	if (is_digit == true)
	{
		if (ft_arrlen(argv) > 2 && big->exe == true)
		{
			big->exe = false;
			ft_putstr_fd("exit\n", 1);
		}
		else
		{
			code = ft_atoi(argv[1]);
			code = (code % 256 + 256) % 256;
		}
	}
	big->exit_code = code;
	if (is_digit == true)
		return (1);
	return (0);
}

/**
 * @brief function to execute the builtin function "exit", 
 * it closes the programm and frees all allocated memory
 * 
 * @param big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param prompt string that has to be freed before exit the program
 */
// FULL execution IF big->exe is true
// if exe is false - checking for errors and assigns exit code
void	ft_exit_minishell(t_data *comm_info, t_big *big, char *prompt)
{
	char	**argv;
	bool	is_digit;

	argv = comm_info->cmd;
	is_digit = true;
	if (ft_arrlen(argv) >= 2)
	{
		if (exit_utils(argv, is_digit, big) == 1)
			is_digit = true;
		else 
			is_digit = false;
	}
	if (big->exe == false)
	{
		exit_error_handling_only(big, argv, is_digit);
		return ;
	}
	if (big->exe == true)
		exit_exe(prompt, big, argv, is_digit);
}
