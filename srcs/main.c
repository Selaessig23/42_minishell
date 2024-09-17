#include "minishell.h"

// **Note for Markus. 12 Aug** I moved it up "if (argc != 1) error_handling(1);"
// The reason is that is generally common to start by checking for invalid input
// or error conditions first. In the context of command-line arguments, this
// often means checking for incorrect argument counts before proceeding with
// the valid case. Please look at it, and say if it works for you. Thanks!
/**
 * (To be continued...)
 * An INFINITE LOOP to continuously prompt for and process user input
 * using the 'readline' function. Inside a loop there are three 'if' statements.
 * 1. Check if 'readline' failed to get input.
 * 2. Check if the input is an empty string (user pressed Enter without typing anything).
 * If the input is empty, free the memory allocated for 'input' and assign 0 to 'exitcode'.
 * 3. If input is not empty, proceed with the program logic.
 *
 * @param input a pointer to a character string that will hold user input
 */
int main(int argc, char **argv, char **envp)
{
	int		exitcode;
	char	*input;
	char	*prompt;
	char	**input_arr;
	t_list	*lexx;
	t_list	*comm;
	t_big	*big;

	(void)argv;
	lexx = NULL;
	comm = NULL;
	exitcode = 0;
	if (argc != 1)
		error_handling(1);
	else if (argc == 1)
	{
		// if (!*__environ)
			// error_handling(4);
		prompt = ft_strdup("Marina's and Markus' minishell>");
		big = init_t_big(envp);
		while (1)
		{
			input = readline(prompt);
			if (!input)
			{
				// free session
				exit(EXIT_FAILURE);
			}
			else if (!*input)
			{
				free(input);
				exitcode = 0;
			}
			else if (*input)
			{
				add_history(input);
				// integrate history_list for fun
				ft_printf("input length: %i\n", ft_strlen(input));
				input_arr = create_nodes(&input);
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
				// comment out this free-function if ft_test_arr_print is in use
				// ft_test_ll_print(lexx, prompt);
				ft_free(input_arr);
				// to seperate debug-infos of lexer from bash-output
				ft_printf("\n");
				if (!ft_syntax(lexx))
				{
					//printf_env(big);
					ft_expa_precond(lexx, big);
					// ft_printf("test\n");
					// ft_test_ll_print(lexx, prompt, big);
					comm = ft_commands(lexx);
					ft_free_ll(&lexx);
				// 	if (ft_executer(comm) == 2)

				// 	else if 

				// 	else
				// 		ft_test_command_print(comm, prompt, big);
				// }
				else
				{
					ft_free_ll(&lexx);
				}
			}
		}
		ft_free_ll(&lexx);
		rl_clear_history();
		free(prompt);
		prompt = NULL;
		free_t_big(big);
	}
	exit(exitcode);
	// return (exitcode);
}
