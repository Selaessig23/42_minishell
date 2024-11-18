/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testprints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:31:05 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 14:31:09 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * function to print and work with cleaned array of strings
 */
/*void ft_test_arr_print(char **input_arr, t_big *big)
{
	char	**env_list;
	int		i;

	i = 0;
	env_list = big->env;
	if (ft_arrlen(input_arr) == 1 && (!ft_strncmp(input_arr[0], "env",
						3) && ft_strlen(input_arr[0]) == 3))
	{
		while (env_list && *env_list)
		{
			ft_printf("%s\n", *env_list);
			env_list += 1;
		}
	}
	else if (ft_arrlen(input_arr) == 1 && (!ft_strncmp(input_arr[0],
				"exit", 4) && ft_strlen(input_arr[0]) == 4))
	{
		ft_free(input_arr);
		free_t_big(big);
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	else
	{
		i = 0;
		while (input_arr[i])
		{
			if (!ft_strncmp(input_arr[i], "$USER", ft_strlen("$USER"))
				&& ft_strlen("$USER") == ft_strlen(input_arr[i]))
			{
				ft_printf("arr[%i]: %s\n", i, input_arr[i]);
				ft_printf("after expand function $USER is \"user_name\"\n");
			}
			else
				ft_printf("arr[%i]: %s\n", i, input_arr[i]);
			// free(*input_arr);
			i++;
		}
		// input_arr = NULL;
		// ft_putchar_fd('\n', 1);
	}
	ft_free(input_arr);
	// 	ft_printf("%s\n", testinput);
}*/

/**
 * test function to print the tokens in string (not ids)
 
static char	*print_tokens(int i)
{
	if (i == 1)
		return (ft_strdup("PIPE"));
	else if (i == 2)
		return (ft_strdup("SEMI"));
	else if (i == 3)
		return (ft_strdup("HEREDOC"));
	else if (i == 4)
		return (ft_strdup("REDIRECT_IN"));
	else if (i == 5)
		return (ft_strdup("REDIRECT_STDOUT"));
	else if (i == 6)
		return (ft_strdup("REDIRECT_STDOUT_ADD"));
	else if (i == 7)
		return (ft_strdup("REDIRECT_ERROUT"));
	else if (i == 8)
		return (ft_strdup("REDIRECT_STDERROUT"));
	else if (i == 9)
		return (ft_strdup("REDIRECT_STDERROUT_MERGE"));
	else if (i == 10)
		return (ft_strdup("AMPERSAND"));
	else if (i == 11)
		return (ft_strdup("DOUBLE_AMPERSAND"));
	else if (i == 12)
		return (ft_strdup("DOUBLE_PIPE"));
	else if (i == 20)
		return (ft_strdup("WORD"));
	else if (i == 21)
		return (ft_strdup("D_QUOTED"));
	else if (i == 22)
		return (ft_strdup("S_QUOTED"));
	else if (i == 23)
		return (ft_strdup("D_QUOTED_F"));
	else if (i == 24)
		return (ft_strdup("S_QUOTED_F"));
	else if (i == 25)
		return (ft_strdup("D_Q_WORD"));
	else if (i == 26)
		return (ft_strdup("S_Q_WORD"));
	else if (i == 27)
		return (ft_strdup("D_Q_WORD_F"));
	else if (i == 28)
		return (ft_strdup("S_Q_WORD_F"));
	else if (i == 29)
		return (ft_strdup("Q_WORD_CLEANED"));
	else
		return (NULL);
}*/

/**
 * test function to print the content of the linked list
 * lexx (= command line input)
 
void	ft_test_ll_print(t_list *lexx, t_big *big)
{
	t_list	*curr;
	char	*token_print;
	int		i;
	//char	**env_list;

	i = 0;
	token_print = NULL;
	curr = lexx;
	//env_list = big->env;
	while (curr != NULL)
	{
		if (!ft_strncmp(((t_lexer *)curr->content)->value, "exit", 4) 
			&& ft_strlen(((t_lexer *)curr->content)->value) == 4)
		{
			// ft_free(input_arr);
			free_t_big(big);
			ft_free_ll(&lexx);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		else if (!ft_strncmp(((t_lexer *)curr->content)->value, "env", 3) 
			&& ft_strlen(((t_lexer *)curr->content)->value) == 3)
		{
			while (env_list && *env_list)
			{
				ft_printf("%s\n", *env_list);
				env_list += 1;
			}
		}
		else
		{
			token_print = print_tokens(((t_lexer *)curr->content)->token);
			ft_printf("node (%i): %s\n", i, ((t_lexer *)curr->content)->value);
			ft_printf("token (%i): %s\n", i, token_print);
			ft_printf("length token (%i): %i\n", i, 
				ft_strlen(((t_lexer *)curr->content)->value));
			ft_printf("-------------------------------------\n");
			free (token_print);
			if ((!ft_strncmp(((t_lexer *)curr->content)->value, 
					"$USER", ft_strlen("$USER")))
				&& (ft_strlen("$USER") == 
					ft_strlen(((t_lexer *)curr->content)->value)))
				ft_printf("after expand function $USER is \"user_name\"\n");
		}
		i++;
		curr = curr->next;
	}
	// ft_free(input_arr);
	ft_free_ll(&lexx);
}
*/
/**
 * test function to print the content of the linked list
 * comm (command struct)
 
void	ft_test_command_print(t_data *comm_info, t_big *big)
{
	// t_list	*curr;
	// char	*token_print;
	int		i;
	// char	**env_list;
	// t_data	*comm_info;

	i = 0;
	// token_print = NULL;
	// env_list = big->env;
	// printf("testA\n");
	// curr = big->cmdlist;
	// printf("testB\n");
	// comm_info = curr->content;
	// while (curr != NULL)
	// {
		i = 0;
		// comm_info = curr->content;
		// printf("what the hack VIII: %s\n", comm_info->cmd[0]);
		// if (comm_info->cmd && !ft_strncmp(comm_info->cmd[0], "exit", 4) 
		// 	&& ft_strlen(comm_info->cmd[0]) == 4)
		// {
		// 	// ft_free(input_arr);
		// 	free_t_big(big);
		// 	// ft_free_ll(&comm);
		// 	rl_clear_history();
		// 	exit(EXIT_SUCCESS);
		// }
		// else if (comm_info->cmd && !ft_strncmp(comm_info->cmd[0], "env", 3) 
		// 	&& ft_strlen(comm_info->cmd[0]) == 3)
		// {
		// 	while (env_list && *env_list)
		// 	{
		// 		ft_printf("%s\n", *env_list);
		// 		env_list += 1;
		// 	}
		// }
		// else
		// {
			printf("no builtin command was found\n");
			ft_printf("in_heredoc: %i\n", comm_info->in_heredoc);
			ft_printf("out_append: %i\n", comm_info->out_append);
			ft_printf("fd_infile: %i\n", comm_info->fd_infile);
			ft_printf("fd_outfile: %i\n", comm_info->fd_outfile);
			ft_printf("command no: %i (total: %i)\n", 
				comm_info->commands_no, big->count_commds);
			if (!comm_info->cmd || !comm_info->cmd[0])
				ft_printf("command_array (%i): empty\n", i);
			while (comm_info->cmd && comm_info->cmd[i])
			{
				ft_printf("command_array (%i): %s\n", i, comm_info->cmd[i]);
				i += 1;
			}
			ft_printf("--------------------------------------\n");
		// }
		// curr = curr->next;
		// if (curr != NULL)
		// 	comm_info = curr->content;
		// ft_printf("test\n");
	// }
	// ft_printf("test 2\n");
	// ft_free_cl(&(big->cmdlist));
}*/
