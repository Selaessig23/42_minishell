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

// it is "a good practice" to use a global variable for environment 
// instead of picking it in the main
// but it is not allowd to use global variables
// extern char	**environ;

// to define all different tokens
// see libft_bonus
typedef enum e_tokentype
{
	PIPE = 1,
	SEMI = 2,
	HEREDOC = 3,
	REDIRECT_IN = 4,
	REDIRECT_OUT = 5,
	REDIRECT_OUT_APP = 6,
	WORD = 20,
	D_QUOTED = 21, //double quoted word
	S_QUOTED = 22, //single quoted word
	D_QUOTED_F = 23, //to define cases without closing quotation mark like "argument1withoutquotend
	S_QUOTED_F = 24, //to define cases without closing quotation mark like 'argument1withoutquotend
	D_Q_WORD = 25, //to define cases like "argument1"withoutspaceafterquotes or argument1"withoutspace"afterquotes...
	S_Q_WORD = 26, // to define cases like 'argument1'withoutspaceafterquotes or argument1'withoutspace'afterquotes...
	D_Q_WORD_F = 27, //to define cases with a single double quotation mark like argument1"withoutspaceafterquotes
	S_Q_WORD_F = 28 // to define cases a single single quotation marklike argument1'withoutspaceafterquotes
}	t_tokentype;

// struct for lexer analysis
typedef struct s_lexer
{
	char			*value;
	t_tokentype		token;
}				t_lexer;

typedef struct s_data {
	// int	infile;// Input file descriptor (defaults to stdin)
	// int	outfile;// Output file descriptor (defaults to stdout)
	bool	in_heredoc;
	bool	out_append;
	char	*infile;
	char	*outfile;
	char	**cmd;// Command and arguments
	size_t	commands_no;// if helpful
}				t_data;

// Main struct containing the list of commands and
// a copy of the environment
typedef struct s_big
{
	t_list	*cmdlist; // Linked list t_data
	char	**env; // Copy of environment variables
	int		exit_code;
}					t_big;

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
void	printf_env(t_big *big);
void	free_t_big(t_big *big); // temp cleanup function
//lexer.c
char	**create_nodes(char **readline_input);
//ft_split_quotes.c
char	**ft_split_quotes(char const *s, char c);
//tokenizer/tokenizer.c
t_list	*ft_tokenizer(char **input_arr);
void	ft_free_ll(t_list **ll);
//tokenizer/tokenizer_strings.c
t_tokentype	ft_creat_str_token(char *input_string);
//testprints.c --> only test functions
void	ft_test_arr_print(char **input_arr, char *prompt, t_big *big);
void	ft_test_ll_print(t_list *lexx, char *prompt, t_big *big);
void	ft_test_command_print(char *prompt, t_data *comm_info);
//syntax.c
int		ft_syntax(t_list *lexx);
//syntaxerrors.c
void	ft_syntax_errors(t_list *lexx, int errorno);
//expander/expander.c
void	ft_expa_precond(t_list *lexx, t_big *big);
//expander/expander_quotes.c
void	ft_quote_checker(void **token);
//expander/expander_env.c
char	*ft_var_creator(char *value_old, char **env);
//expander/expander_env_no.c
char	*delete_varname_from_value(char *value_old, char *wrongenvp);
//expander/expander_env_yes.c
char	*add_env_to_value(char *value_old, char *env, char *env_name);
//expander/expander_pid.c
//expander/expander_exit.c
char	*ft_exit_expander(char *value_old, int exit_code);
//expander/expander_utils.c
char	*ft_givenbr(int nbr);
int		ft_is_env_var(char c);
//commands/command_list.c
void	ft_commands(t_list *lexx, t_big **big);
//commands/command_utils.c
void	ft_free_cl(t_list **ll);
//commands/command_reader.c
int    ft_executer(t_big *big, char *prompt);
//builtins/exit.c
void    ft_exit_minishell(t_big *big, char *prompt);
//builtins/env.c
void	ft_print_env(t_big *big);
//builtins/pwd.c
void	ft_print_pwd(t_big *big, t_data *comm_info);

#endif
