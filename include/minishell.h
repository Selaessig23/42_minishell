
//to avoid duplications
#ifndef MINISHELL_H
# define MINISHELL_H

//stdio.h (for debugging) | stdlib.h (for malloc & free) | 
//unistd.h (for write) is included in libft.h
# include "../libft/include/libft.h"
//#include <limits.h>
//to use data type bool
# include <stdbool.h>
//to provide a standardized way to report and interpret error conditions
# include <errno.h>
//to be able to work with function waitpid
# include <sys/wait.h>
// to be able to work with function readline
// we also have to include -lreadline to our Makefile 
// to consider readline while compiling
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//define error message
# define INPUT_ERROR "Not correct number of input arguments to execute minishell\n"

//it is "a good practice" to use a global variable for environment instead of picking it in the main
extern char	**environ;

// to define all different tokens
typedef enum e_tokentype {
	WORD,
	D_QUOTED, 
	S_QUOTED, 
	PIPE,
	HEREDOC,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
}	t_tokentype;

// linked list for lexer analysis -> token system, redefined from libft_bonus.h
typedef struct s_list{
	void			*content;
	t_tokentype		token;
	struct s_list	*next;
}				t_list;

// Struct representing command data
typedef struct s_data
{
	int		infile; // Input file descriptor (defaults to stdin)
	int		outfile; // Output file descriptor (defaults to stdout)
	char	**cmd; // Command and arguments
}					t_data;

// Linked list containing a s_data nodes with
// all commands separated by pipes
// typedef struct s_list
// {
// 	t_data			*cmds; // Command data
// 	struct t_list	*next; // Pointer to the next list node
// }					t_list;

// Main struct containing the list of commands and
// a copy of the environment
typedef struct s_big
{
	t_list	*list; // Linked list of commands
	char	**env; // Copy of environment variables
}					t_big;

////////////////////////////
//maybe rename to bin_path for binary path
typedef struct s_envp{
	char	**bin_paths;
	char	***commands;
	char	*outfile;
	char	*infile;
	size_t	commands_no;
}				t_envp;



// main.c
//
//error_handling.c
void	error_handling(int err);
//lexer.c
char	**create_nodes(char *readline_str);
//ft_split_quotes.c
char	**ft_split_quotes(char const *s, char c);
//tokenizer.c
t_list	*ft_tokenizer(char **input_arr);

#endif
