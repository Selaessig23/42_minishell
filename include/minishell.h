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
//to handle signals
# include <signal.h>
// to use struct sigaction
# include <bits/sigaction.h>
// function ioctl, macros TIOCSTI
# include <sys/ioctl.h>
//to change behaviour of the terminal (not-printing all control squences)
# include <termios.h>
// for S_ISDIR macro in is_valid_cmd_and_print_err function
# include <sys/stat.h>
//define error message
# define INPUT_ERROR "Not correct number of input arguments\
to execute minishell\n"

//define a global variable for signal-handling
extern int	signalnum;

// it is "a good practice" to use a global variable for environment 
// instead of picking it in the main
// but according t subject it is not allowed to use global variables
// extern char	**environ;

// to define all different tokens
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
	D_QUOTED = 21,
	S_QUOTED = 22,
	D_QUOTED_F = 23,
	S_QUOTED_F = 24,
	D_Q_WORD = 25,
	S_Q_WORD = 26,
	D_Q_WORD_F = 27,
	S_Q_WORD_F = 28,
	WORD_CLEANED = 29,
	HEREDOC_LIMITER = 30
}	t_tokentype;

/**
 * struct for lexer analysis
 * 
 * @param number_helper helps to create many heredocs
 */
typedef struct s_lexer
{
	char			*value;
	t_tokentype		token;
	int				number_helper;
}				t_lexer;

// cmd - Command and arguments
typedef struct s_data {
	bool	in_heredoc;
	bool	heredoc_expander;
	bool	out_append;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pipe[2];
	char	**cmd;
	size_t	commands_no;
	pid_t	id;
}				t_data;

// Main struct containing the list of commands and
// a copy of the environment
// cmdlist - Linked list t_data
// env - Copy of environment variables
// exe - to define if we execute export, unset
// cd and exit. we execute it fully only if there
// is no pipeline, but only one command.
typedef struct s_big
{
	t_list	*cmdlist;
	char	**env;
	char	**binarypaths;
	int		exit_code;
	size_t	count_commds;
	bool	exe;
}					t_big;

//ascii_graohic.c
void	ft_welcome(void);
// void	error_handling(int err, t_envp *i, int com_no);
void	error_handling(int err);
char	**ft_split_quotes(char const *s, char c);
//error_handling.c
void	error_handling(int err);
//t_big_and_env_copy.c
t_big	*init_t_big(char **envp);
void	printf_env(t_big *big);
void	free_t_big(t_big *big);
char	**copy_envp(char **envp);
//testprints.c --> only test functions
void	ft_test_arr_print(char **input_arr, char *prompt, t_big *big);
void	ft_test_ll_print(t_list *lexx, char *prompt, t_big *big);
void	ft_test_command_print(char *prompt, t_data *comm_info, t_big *big);

// PARSING - LEXICAL ANALYSIS
//lexer/lexer.c
char	**create_nodes(char **readline_input);
//lexer/lexer_cleaner.c
void	ft_create_clean_input(char *dest, char *src);
//lexer/lexer_op_check.c
bool	single_operator_check(char c);
bool	double_operator_check(char c, char k);
//lexer/ft_split_ms.c
char	**ft_split_quotes(char const *s, char c);
//lexer/ft_split_specials.c
int		ft_space_tab_jump(const char *s, char c, int i);
int		ft_quo_handling(const char *s, int i);
int		is_tab(char c);
//lexer/extra_prompt.c
int		is_open_pipe(char *clean_input);
void	close_pipe(char **readline_input);
char	*extra_prompt_reader(void);
void	update_read_input(char **main, char *extra);
//lexer/str_spaces_trimer.c
void	trim_out_spaces(char **str);
//tokenizer/tokenizer.c
t_list	*ft_tokenizer(char **input_arr);
//tokenizer/tokenizer_utils.c
void	ft_free_ll(t_list **ll);
int		ft_check_fstquote(char *content, char checker);
//tokenizer/tokenizer_operators.c
t_tokentype	ft_creat_redir_token(char *input_string);
t_tokentype	ft_creat_operators_token(char *input_string);
//tokenizer/tokenizer_strings.c
t_tokentype	ft_creat_str_token(char *input_string);
//tokenizer/tokenizer_qwords.c
void	ft_qword_quotecheck(char *input_string, t_tokentype *token_old);

// PARSING - SYNTAX ANALYSIS
//syntax analyzer/syntax.c
int		ft_syntax(t_list *lexx);
//syntax analyzer/syntaxerrors.c
void	ft_syntax_errors(t_list *lexx, int errorno);

// PARSING - EXPANDER
//expander/expander.c
void	ft_expa_precond(t_list *lexx, t_big *big);
void	ft_var_checker(void	**token, t_big *big);
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
//expander/expander_q.c
void	ft_q_word_handling(void **token, t_big *big);
//expander/llist_to_string.c
char	*ft_listtostr(t_list *q_word_list);

// COMMAND LIST CREATION AND READING
//command_creation/command_list.c
void	ft_commands(t_list *lexx, t_big **big);
int		fd_out_creator(bool appender, char *filename);
//command_creation/initiate_comm_infos.c
void	ft_init_clist(t_list **lexx, t_list **comm, t_big **p_big);
//command_creation/handle_redirections.c
t_list	*ft_set_r_in(t_lexer *token, 
			t_data **cominfo, t_list *lexx, t_big **p_big);
t_list	*ft_set_r_out(t_lexer *token, 
			t_data **cominfo, t_list *lexx, t_big **p_big);
//command_creation/create_argv_of_cmds.c
void	ft_add_arr_end(char *token_value, t_data **p_comm_info);
//command_creation/file_creator.c
int		fd_in_checker(t_data *comm_info, char *infile, t_big **p_big);
//command_creation/command_utils.c
void	exe_fd_error(t_big *big, t_data *comm_info_next);
t_data	*ft_pointer_next_command(t_list	*curr);
void	ft_free_cl(t_list **ll);
//command_creation/check_def_env_paths.c
void	ft_check_defaultpath(char *binary, char **binarypaths);

// BUILT-INS
//builtins/builtin_check.c
int		check_parent_builtin(t_data *comm_info);
int		check_child_builtin(t_data *comm_info);
//builtins/exit.c
void	ft_exit_minishell(t_data *comm_info, t_big *big, char *prompt);
//builtins/env.c
void	ft_print_env(t_data *comm_info, t_big *big);
//builtins/echo.c
void	ft_echo(t_data *comm_info, t_big *big);
//builtins/pwd.c
void	ft_print_pwd(t_big *big, t_data *comm_info);
//builtins/cd.c
void	ft_cd(t_big *big, char **argv);
//builtins/export.c
int		ft_export(t_big *big, t_data *comm_info);
void	ft_rmv_var_array(t_big *big, char *str_to_rmv);
void	export_exit_status(t_big *big, char **cmd_arg);
int		check_dash_in_var_name(char *argument);
//builtins/export_sort.c
void	ft_export_sort(t_big *big);
//builtins/unset.c
int		ft_unset(t_big *big, t_data *comm_info);
size_t	count_till_char(char *str, char up_to);
//heredoc.c
int		heredoc_start(t_data *comm_info, char *limiter, t_big **p_big);
void	delete_heredoc(t_data *comm_info);
//builtins/help.c
void	ft_minishell_help(t_data *comm_info, t_big *big);
//signals.c
int		ft_handle_signals(bool rl_antes);
void	ft_handle_signals_childs(void);

// EXECUTION
//execution/command_reader_01.c
int		ft_executer(t_big *big, char *prompt);
//execution/command_reader_02.c
int		w_waitpid(t_big *big);
void	assign_exit_code(t_list	*cmdlist, int exit_status_binar, t_big *big);
//execution/command_reader_print_err_01.c
int		is_valid_cmd_and_print_err(char **cmd_plus_args, t_big *big);
//execution/command_reader_print_err_02.c
int		is_dir_err_handling(char *cmd);
int		err_handling_executable(char *executable);
int		is_absolute_path_to_exe_err_handling(char *cmd);
int		get_path_from_env_or_binarypaths(t_big *big, char **cmd_plus_args);

//execution/exe_built-ins.c
void	exe_parent_builtin(t_data *comm_info, t_big *big, char *prompt);
int		fork_and_exe_child_builtin(t_data *comm_info, t_data *c_i_next, t_big *big);
void	setup_and_exe_builtin_in_child(t_data *comm_info, t_data *c_i_next, t_big *big);
void	exe_child_builtin(t_data *comm_info, t_big *big);
//execution/exe_binary.c
int		fork_and_exe_binary(t_data *comm_info, t_data *c_i_next, t_big *big);
void	setup_and_exe_binary_in_child(t_data *comm_info, t_data *c_i_next, t_big *big);
//execution/exe_binary_child_0.c
int		exe_child_binary(char **cmd_plus_args, char *env[]);

//execution/exe_binary_child_1.c
int		get_path_from_env_path_and_exe(char **cmd_plus_args, char *env[]);
char	*get_path(char *cmd_name, char **env);
char	*get_all_folders(const char *env_var_path, char **env);
char	*build_cmd_path(const char *folder, const char *cmd_name);
char	*exe_exists(char **folders, char *cmd_name);

//execution/exe_child_fd_setup_cleanup.c
void	fd_cleanup_in_child(t_big *big);
void	fd_cleanup_read_end_in_child(t_big *big);
void	setup_input_output_in_child(t_data *comm_info, t_data *c_i_next);

//execution/minishell_executer.c
int		is_minishell_command(char *cmd, char *env[]);
void	ft_ms_executer(char *env[]);

//void	ft_overwrite_shlvl(char ***p_env);
// ????

//execution/exe_error_handling.c
void	close_fd_with_error_handling();
void	w_errpipe_close(int open_fd);
void	w_errfork_close(int open_fd, int *pipe_fd);
void	perror_and_exit(char *what_error, int *pipe_fd);
void	print_stderr(char *what_error);
//execution/exe_utils.c
int		is_absolute_path(const char *str, const char *str_cmp, int nmb);
int		is_attempt_to_execute(const char *str, const char *str_cmp, int nmb);

// General Utils
//utils_strings/utils_string.c
void	ft_freestr(char **lst);
int		ft_strcmp(const char *s1, const char *s2);
int		is_exact_string(const char *str_org, char *str_cmp);
int		is_last_char(const char *str, char c);
//utils_binary_path/binary_path.c
char	*build_cmd_path(const char *folder, const char *cmd_name);
#endif
