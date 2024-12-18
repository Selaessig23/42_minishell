/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:03:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 15:03:04 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function that updates the current input when the | character
 * at the end. For instance, if the main input was "ls |" and
 * the extra prompt takes "pwd", this function concatenates it
 * into "ls |pwd".
 */
void	update_read_input(char **main, char *extra)
{
	char	*new;
	int		length;

	length = ft_strlen(*main) + ft_strlen(extra) + 1;
	new = ft_calloc(1, length);
	if (new == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new, *main, ft_strlen(*main) + 1);
	ft_strlcat(new, extra, length);
	free(*main);
	free(extra);
	*main = new;
}

/**
 * The function open a prompt in case when in the end the PIPE sign.
 * It implements behaviour of a bash that is waiting for input to
 * complete input.
 */
char	*extra_prompt_reader(void)
{
	char	*input2;

	input2 = NULL;
	if (g_signalnum != 1)
	{
		input2 = readline(">");
		if (!input2)
		{
			ft_dprintf("minishell: ");
			ft_dprintf("syntax error: unexpected end of file\n");
			ft_dprintf("exit\n");
			exit(2);
		}
		return (input2);
	}
	else
		return (NULL);
}

/**
 * The function is called when the input ends with |
 * and it opens and extra prompt and waiting for additional
 * input.
 */
void	to_complete_input(char **readline_input)
{
	char	*extra_input;

	extra_input = NULL;
	extra_input = extra_prompt_reader();
	if (!extra_input)
		return ;
	if (extra_input)
	{
		if (g_signalnum == 1)
		{
			free(extra_input);
			return ;
		}
		update_read_input(readline_input, extra_input);
	}
}

/**
 * The function checks if there is PIPE in the end of input.
 * It ignores all SPACES in the end of the input.
 * It returns 0 if all input is only one PIPE and if
 * if the preceding character (excluding all spaces) is PIPE '|' or
 * LESS '<' or GREATER '>'.
 */
int	is_incomplete_input(char *input)
{
	int	i;

	if (!*input)
		return (0);
	i = ft_strlen(input) - 1;
	if (i == 0)
		return (0);
	else
		while (i >= 0 && input[i] && input[i] == 32)
			i--;
	if (i >= 0 && input[i] == '|' && input[i - 1] != '|')
	{
		i--;
		while (input[i] == 32)
			i--;
		if (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<')
			return (1);
		return (0);
	}
	else
		return (0);
}
