
#include "minishell.h"

/**
 * function to print and work with cleaned array of strings
 */
void ft_test_arr_print(char **input_arr, char *prompt)
{
	int	i;

	i = 0;
	if (ft_arrlen(input_arr) == 1 && (!ft_strncmp(input_arr[0], "env",
						3) && ft_strlen(input_arr[0]) == 3))
	{
		while (*__environ)
		{
			ft_printf("%s\n", *__environ);
			__environ++;
		}
	}
	else if (ft_arrlen(input_arr) == 1 && (!ft_strncmp(input_arr[0],
				"exit", 4) && ft_strlen(input_arr[0]) == 4))
	{
		ft_free(input_arr);
		free(prompt);
		prompt = NULL;
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
	// ft_free(input_arr);
	// 	ft_printf("%s\n", testinput);
}

/**
 * test function to print the tokens in string (not ids)
 */
static char	*print_tokens(int i)
{
	if (i == 1)
		return (ft_strdup("WORD"));
	else if (i == 2)
		return (ft_strdup("D_QUOTED"));
	else if (i == 3)
		return (ft_strdup("S_QUOTED"));
	else if (i == 4)
		return (ft_strdup("PIPE"));
	else if (i == 5)
		return (ft_strdup("HEREDOC"));
	else if (i == 6)
		return (ft_strdup("REDIRECT_INPUT"));
	else if (i == 7)
		return (ft_strdup("REDIRECT_OUTPUT"));
	else if (i == 8)
		return (ft_strdup("D_QUOTED_F"));
	else if (i == 9)
		return (ft_strdup("S_QUOTED_F"));
	else
		return (NULL);
}
/**
 * test function to print the content of the linked list
 */
void	test_print(t_list *lexx)
{
	t_list	*curr;
	char 	*token_print;
	int		i;

	i = 0;
	token_print = NULL;
	curr = lexx;
	while (curr != NULL)
	{
		if (!ft_strncmp(curr->content, "exit", 4) 
			&& ft_strlen(curr->content) == 4)
		{
			//valgrind-error as prompt, input_arr, 
			ft_free_ll(&lexx);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		else if (!ft_strncmp(curr->content, "env", 3) 
			&& ft_strlen(curr->content) == 3)
		{
			while (*__environ)
			{
				ft_printf("%s\n", *__environ);
				__environ++;
			}
		}
		else
		{
			token_print = print_tokens((int)curr->token);
			ft_printf("node (%i): %s\n", i, curr->content);
			// ft_printf("token (%i): %d\n", i, (int)curr->token);
			ft_printf("token (%i): %s\n", i, token_print);
			free (token_print);
			if (!ft_strncmp(curr->content, "$USER", ft_strlen("$USER"))
				&& ft_strlen("$USER") == ft_strlen(curr->content))
				ft_printf("after expand function $USER is \"user_name\"\n");
		}
		i++;
		curr = curr->next;
	}
}