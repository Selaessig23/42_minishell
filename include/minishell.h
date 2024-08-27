// to avoid duplications
#ifndef MINISHELL_H
# define MINISHELL_H

//stdio.h (for debugging) | stdlib.h (for malloc & free) | 
//unistd.h (for write) is included in libft.h
# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"
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
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

//define error message
# define INPUT_ERROR "Not correct number of input arguments\
to execute minishell\n"

//it is "a good practice" to use a global variable for environment 
//instead of picking it in the main
extern char	**environ;

// to define all different tokens
// see libft_bonus
typedef enum e_tokentype
{
	PIPE = 1,
	SEMI = 2,
	HEREDOC = 3,
	REDIRECT_IN = 4,
	REDIRECT_STDOUT = 5,
	REDIRECT_STDOUT_APP = 6,
	REDIRECT_ERROUT = 7, //2>: Redirects standard error to a file.
	REDIRECT_STDERROUT = 8, //&>: Redirects both standard output and standard error to a file.
	REDIRECT_STDERROUT_MERGE = 9, //2>&1: Merges standard error with standard output.
	AMPERSAND = 10, // &
	DOUBLE_AMPERSAND = 11, // &&
	DOUBLE_PIPE = 12, // ||
	LOG_NEG = 13, //Logical Negation (!)
	WORD = 20,
	D_QUOTED = 21, //double quoted word
	S_QUOTED = 22, //single quoted word
	D_QUOTED_F = 23, //to define cases like 'argument1withoutquotend
	S_QUOTED_F = 24, //to define cases like "argument1withoutquotend
	Q_WORD = 25, //to define cases like "argument1"withoutspaceafterquotes
	// and 'argument1'withoutspaceafterquotes
}	t_tokentype;

// struct for lexer analysis
typedef struct s_lexer
{
	char			*value;
	t_tokentype		token;
}				t_lexer;

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
// maybe rename to bin_path for binary path
typedef struct s_envp
{
	char	**bin_paths;
	char	***commands;
	char	*outfile;
	char	*infile;
	size_t	commands_no;
}	t_envp;

// main.c
//
// init.c
// int		init_infile(t_envp *infos, char *infile);
// void	init_compath(t_envp *infos, char **argv, char **paths);
// void	init_outfile(t_envp *infos);
// int		init_check(char **argv, char **paths, t_envp *infos);
// inputcheck.c
// char	*flagcheck(const char *argv);
// int		bin_paths_init(char *command, char **paths, char **bin_paths);
// exec.c
// int		ft_execute(t_envp *infos, char *const envp[]);
// void		ft_execute(t_envp *infos, char *const envp[]);
// utils.c
// size_t	ft_arrlen(char **arr_str);
// void	ft_free(char **arr);
// void	free_struct(t_envp *infos);
// void	error_handling(int err, t_envp *i, int com_no);
void	error_handling(int err);
char	**ft_split_quotes(char const *s, char c);
// extra_prompt.c
int		is_open_pipe(char *clean_input);
void	close_pipe(char **readline_input);
char	*extra_prompt(void);
void	update_read_input(char **main, char *extra);
//str_spaces_trimer.c
void	trim_out_spaces(char **str);
//error_handling.c
void	error_handling(int err);
//t_big_and_env_copy.c
t_big	*init_t_big(char **envp);
void	printf_env(t_big *big); // temp function
void	free_t_big(t_big *big); // temp cleanup function
//lexer.c
char	**create_nodes(char **readline_input);
//ft_split_quotes.c
char	**ft_split_quotes(char const *s, char c);
//tokenizer.c
t_list	*ft_tokenizer(char **input_arr);
void	ft_free_ll(t_list **ll);
//testprints.c --> only test functions
void	ft_test_arr_print(char **input_arr, char *prompt);
void	ft_test_ll_print(t_list *lexx, char *prompt);
//syntax.c
int		ft_syntax(t_list *lexx);
//syntaxerrors.c
void	ft_syntax_errors(t_list *lexx, int errorno);

#endif
