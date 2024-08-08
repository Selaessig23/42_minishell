
#include "minishell.h"
//test branch2

int	main(int argc, char **argv)
{
	int		exitcode;
	int		i;
	char	*input;
	char	*prompt;
	char	**input_arr;
	t_list	*lexx;

	(void)argv;
	lexx = NULL;
	i = 0;
	exitcode = 0;
	if (argc == 1)
	{
		if (!*__environ)
			error_handling(4);
		prompt = ft_strdup("Marina's and Markus' minishell>");
		while (1)
		{
			// testinput = readline("Marina's and Markus' minishell>");
			input = readline(prompt);
			if (!input)
			{
				// free session
				exit(EXIT_FAILURE);
			}
			if(*input)
			{
				if (input)
				{
						add_history(input);
						//integrate history_list for fun
				}
				ft_printf("input length: %i\n", ft_strlen(input));
				input_arr = create_nodes(input);
				free(input);
				input = NULL;
				// ft_test_arr_print(input_arr, prompt);
				// attempt to use both ways, to not destroy the work
				// with input_arr on extra input of marina
				// otherwise I would add this function call to create_nodes-function
				// in lexer.c
				// ft_printf("test0\n");
				lexx = ft_tokenizer(input_arr);
				// ft_printf("test1\n");
				//comment out this free-function if ft_test_arr_print is in use
				// ft_test_ll_print(lexx, prompt);
				ft_free(input_arr);
				//to seperate debug-infos of lexer from bash-output
				ft_printf("\n");
				if (!ft_syntax(lexx))
					ft_test_ll_print(lexx, prompt);
				else
					ft_free_ll(&lexx);
			}
			else if (!*input)
				free(input);
		}
		ft_free_ll(&lexx);
		rl_clear_history();
		free(prompt);
		prompt = NULL;
	}
	else
		error_handling(1);
	exit(exitcode);
	// return (exitcode);
}
