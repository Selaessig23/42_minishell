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
	ft_printf("updated readline input $%s$\n", new);
	free(*main);
	free(extra);
	*main = new;
}

/**
 * The function open a prompt in case when in the end the PIPE sign.
 * It implements behaviour of a bash that is waiting for additional input.
 * (c) Marina
 */
char	*extra_prompt(void)
{
	char	*prompt;
	char	*input2;

	prompt = ft_strdup(">");
	if (!prompt)
	{
		perror("error extra_prompt");
		exit(EXIT_FAILURE);
	}
	input2 = readline(prompt);
	while (input2 && !*input2)
	{
		free(input2);
		input2 = readline(prompt);
	}
	if (!input2)
	{
		perror("error extra_input");
		free(prompt);
		exit(EXIT_FAILURE);
	}
	free(prompt);
	return (input2);
}

/**
 * The function is called when the input ends with |
 * and it opens and extra prompt and waiting for additional
 * input.
*/
void	close_pipe(char **readline_input)
{
	char	*extra_input;

	extra_input = NULL;
	extra_input = extra_prompt();
	if (!extra_input)
		return ;
	if (extra_input)
		update_read_input(readline_input, extra_input);
}

/**
 * The function checks if there is PIPE in the end of input.
 * It ignores all SPACES in the end of the input.
 * It returns 0 if all input is only one PIPE and if
 * if the preceding character (excluding all spaces) is PIPE.
 * (c) Marina
 */
int	is_open_pipe(char *input)
{
	int	i;

	if (!*input)
		return (0);
	i = ft_strlen(input) - 1;
	if (i == 0)
		return (0);
	else
		while (input[i] && input[i] == 32)
			i--;
	if (input[i] == '|' && input[i - 1] != '|')
	{
		i--;
		while (input[i] == 32)
			i--;
		if (input[i] && input[i] != '|')
			return (1);
		return (0);
	}
	else
		return (0);
}
