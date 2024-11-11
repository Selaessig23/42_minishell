#include "minishell.h"


/**
 * @brief checks for empty input (only tabs or spaces)
 * to ignore it in history and return a new prompt
 * 
 * @param input the readline input
 */
int	ft_spacetabchecker(char *input)
{
	while (*input)
	{
		if ((*input >= 9 && *input <= 11)
			|| *input == 32)
			input += 1;
		else
			return (0);
	}
	return (1);
}

// **Note for Markus. 12 Aug** I moved it up "if (argc != 1) error_handling(1);"
// The reason is that is generally common to start by checking for invalid input
// or error conditions first. In the context of command-line arguments, this
// often means checking for incorrect argument counts before proceeding with
// the valid case. Please look at it, and say if it works for you. Thanks!
int	signalnum = 0;

/**
 * (To be continued...)
 * An INFINITE LOOP to continuously prompt for and process user input

	* using the 'readline' function. Inside a loop there are three 'if' statements.
 * 1. Check if 'readline' failed to get input.

	* 2. Check if the input is an empty string (user pressed Enter without typing anything).
 * If the input is empty,

	?????????
 */
int	main(int argc, char **argv, char **envp)
{
	int exitcode;
	char *input;
	char *prompt;
	char **input_arr;
	t_list *lexx;
	// t_list	*comm;
	t_big *big;

	(void)argv;
	lexx = NULL;
	// comm = NULL;
	exitcode = 0;
	// ft_welcome();

	rl_catch_signals = 0;

	if (argc != 1)
		error_handling(1);
	else if (argc == 1)
	{
		prompt = ft_strdup("minishell$ ");
		input = NULL;
		big = init_t_big(envp);
		while (1)
		{
			ft_handle_signals(false);
			input = readline(prompt);
			ft_handle_signals(true);
			if (!input)
			{
				ft_putstr_fd("exit\n", 1);
				ft_free(big->env);
				free(prompt);
				exit(EXIT_FAILURE);
			}
			else if (!*input || ft_spacetabchecker(input))
			{
				free(input);
				exitcode = 0;
			}
			else if (*input)
			{
				add_history(input);
				// ft_printf("input length: %i\n", ft_strlen(input));
				input_arr = create_nodes(&input);
				free(input);
				input = NULL;
				if (input_arr != NULL)
				{
					// ft_test_arr_print(input_arr, prompt);
					// attempt to use both ways, to not destroy the work
					// with input_arr on extra input of marina
					// otherwise I would add this function call to create_nodes-function
					// in lexer.c
					lexx = ft_tokenizer(input_arr);
					ft_free(input_arr);
					if (!ft_syntax(lexx))
					{
						// printf_env(big);
						ft_expa_precond(lexx, big);
						// ft_printf("test\n");
						// ft_test_ll_print(lexx, prompt, big);
						ft_commands(lexx, &big);
						ft_free_ll(&lexx);
						ft_executer(big, prompt);
					}
					else
					{
						big->exit_code = 2;
						ft_free_ll(&lexx);
					}
				}
					
			}
			if (signalnum == 1)
			{
				signalnum = 0;
				big->exit_code = 130;
			}
		}
		ft_free_ll(&lexx);
		free_t_big(big);
		rl_clear_history();
		free(prompt);
		prompt = NULL;
		free_t_big(big);
	}
	exit(exitcode);
	// return (exitcode);
}
