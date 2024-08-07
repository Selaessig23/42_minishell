
#include "minishell.h"
//test branch2

int	main(int argc, char **argv)
{
	int		exitcode;
	int		i;
	char	*input;
	char	*prompt;
	char	**input_arr;

	(void)argv;
	i = 0;
	exitcode = 0;
	if (argc == 1)
	{
		if (!*__environ)
			error_handling(4);
		prompt = ft_strdup("Marina's and Markus' minishell>");
		while (1)
		{
			input = readline(prompt);
			if (!input)
			{
				// free session
				exit(EXIT_FAILURE);
			}
			if (input)
					add_history(input);
			ft_printf("input length: %i\n", ft_strlen(input));
			input_arr = create_nodes(input);
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
					ft_printf("arr[%i]: %s\n", i, input_arr[i]);
					i++;
				}
			}
			ft_free(input_arr);
		}
		rl_clear_history();
		free(prompt);
		prompt = NULL;
	}
	else
		error_handling(1);
	exit(exitcode);
	// return (exitcode);
}

