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
void	ft_exit_minishell(t_data *comm_info, t_big *big, char *prompt)
{
	char	**argv;
	char	*argv2;
	bool	is_nondigit;
	int		exit_code;

	argv = comm_info->cmd;
	argv2 = NULL;
	is_nondigit = 0;
	exit_code = 0;
	if (ft_arrlen(argv) >= 2)
	{
		argv2 = argv[1];
		if (*argv2 == '-' || *argv2 == '+')
			argv2 += 1;
		while (*argv2 && ft_isdigit(*argv2))
			argv2 += 1;
		if (*argv2 && (*argv2 - 1) != '-')
			is_nondigit = true;
	}
	argv = comm_info->cmd;
	if (ft_arrlen(argv) >= 2 && is_nondigit == false)
		exit_code = ft_atoi(argv[1]);
	exit_code = (exit_code % 256 + 256) % 256;
	// if (exit_code < 0)
	// 	exit_code += 256;
	// else if (exit_code > 255)
		
	if (ft_arrlen(argv) > 2 && is_nondigit == false)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		big->exit_code = 1;
	}
	else
	{
		free(prompt);
		prompt = NULL;
		rl_clear_history();
		if (is_nondigit == true)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd((argv[1]), 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_t_big(big);
			exit(2);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			free_t_big(big);
			exit(exit_code);
		}
	}
}
