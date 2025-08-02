/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:41:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 14:29:01 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to avoid duplications
#ifndef MINISHELL_H
# define MINISHELL_H

//unistd.h (for write) is included in libft.h
# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"
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
//stdio.h (for debugging) | stdlib.h (for malloc & free) | 
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

//for testing reasons:
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 
//--track-fds=yes --suppressions=suppressions.supp ./minishell

//define a global variable for signal-handling
extern int	g_signalnum;

// to define all different tokens
typedef enum e_tokentype
{
	PIPE = 1,
	SEMI = 2,
	HEREDOC = 3,
	REDIRECT_IN = 4,
	REDIRECT_STDOUT = 5,
	REDIRECT_STDOUT_APP = 6,
	REDIRECT_ERROUT = 7,
	REDIRECT_STDERROUT = 8,
	REDIRECT_STDERROUT_MERGE = 9,
	AMPERSAND = 10,
	DOUBLE_AMPERSAND = 11,
	DOUBLE_PIPE = 12,
	LOG_NEG = 13,
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
 * parsing struct 
 * serves as content for the linked list of
 * command line input
 * (is used especially for syntax analysis and expander)
 * 
 * @param number_helper helps to create many heredocs
 */
typedef struct s_lexer
{
	char			*value;
	t_tokentype		token;
	int				number_helper;
}				t_lexer;

/**
 * execution struct
 * serves as content for linked list of commands (cmdlist in t_big)
 * 
 * @param cmd the argv for execution (command + options + arguments)
 * @param commands_no the number of each command
 */ 
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

/**
 * Main struct containing all necessary information to execute commands
 * and return correct exit codes
 * 
 * @param cmdlist list of commands that have to be executed
 * @param env the environmental variables 
 * @param binarypaths dafault value of env-var "PATH"
 * @param count_commds total amount of commands that have to be executed
 * @param exe to define if we execute export, unset, cd and exit. 
 * We execute those cmds fully only if there is no pipeline, 
 * but only one command.
 */
typedef struct s_big
{
	t_list	*cmdlist;
	char	**env;
	char	**binarypaths;
	int		exit_code;
	size_t	count_commds;
	bool	exe;
}					t_big;

//01_pre_prompt/pre_prompt.c
t_big		*init_t_big(char **envp);
char		**copy_envp(char **envp);
int			ft_spacetabchecker(char *input);
void		ft_welcome(void);
//error/error_handling.c
void		error_and_exit(int err);
//02_sig/signals.c
int			ft_handle_signals(bool rl_antes);
void		ft_handle_signals_childs(void);
//02_sig/signals_reset.c
void		signal_set_exitcode_and_reset(t_big *big);

// PARSING - LEXICAL ANALYSIS
//03_pars/parsing_1.c
int			minishell_parsing(char *input, t_big *big);
char		**create_cleanarr(char **readline_input);
//03_pars/parsing_2.c
char		**ft_split_rlinput(char **readline_input, char *clean_input);
//03_pars/is_incomplete_input.c
int			is_incomplete_input(char *clean_input);
void		to_complete_input(char **readline_input);
char		*extra_prompt_reader(void);
void		update_read_input(char **main, char *extra);

//04_lex/lexer_cleaner.c
void		ft_create_clean_input(char *dest, char *src);
//04_lex/lexer_op_check.c
bool		single_operator_check(char c);
bool		double_operator_check(char c, char k);
//04_lex/ft_split_ms.c
char		**ft_split_quotes(char const *s, char c);
//04_lex/ft_split_specials.c
int			ft_space_tab_jump(const char *s, char c, int i);
int			ft_quo_handling(const char *s, int i);
int			is_tab(char c);
//04_lex/lexer_str_utils.c.c
void		trim_out_spaces(char **str);

//05_tokenizer/tokenizer.c
t_list		*ft_tokenizer(char **input_arr);
//05_tokenizer/tokenizer_utils.c
void		ft_free_ll(t_list **ll);
int			ft_check_fstquote(char *content, char checker);
//05_tokenizer/tokenizer_operators.c
t_tokentype	ft_creat_redir_token(char *input_string);
t_tokentype	ft_creat_operators_token(char *input_string);
//05_tokenizer/tokenizer_strings.c
t_tokentype	ft_creat_str_token(char *input_string);
//05_tokenizer/tokenizer_qwords.c
void		ft_qword_quotecheck(char *input_string, t_tokentype *token_old);

// PARSING - SYNTAX ANALYSIS
//06_syntax/syntax.c
int			ft_syntax(t_list *lexx);
//06_syntax/syntaxerrors.c
void		ft_syntax_errors(t_list *lexx, int errorno);

// PARSING - EXPANDER
//07_expand/expander.c
void		ft_expa_precond(t_list *lexx, t_big *big);
void		ft_var_checker(void	**token, t_big *big);
//07_expand/expander_quotes.c
void		ft_quote_checker(void **token);
//07_expand/expander_env.c
char		*ft_var_creator(char *value_old, char **env);
//07_expand/expander_env_no.c
char		*delete_varname_from_value(char *value_old, char *wrongenvp);
//07_expand/expander_env_yes.c
char		*add_env_to_value(char *value_old, char *env, char *env_name);
//07_expand/expander_exit.c
char		*ft_exit_expander(char *value_old, int exit_code);
//07_expand/expander_utils.c
char		*ft_givenbr(int nbr);
int			ft_is_env_var(char c);
//07_expand/expander_q.c
void		ft_q_word_handling(void **token, t_big *big);
//07_expand/llist_to_string.c
char		*ft_listtostr(t_list *q_word_list);

// COMMAND LIST CREATION AND READING
//08_cmd_creat/command_list.c
void		ft_commands(t_list *lexx, t_big **big);
//08_cmd_creat/initiate_comm_infos.c
void		ft_init_clist(t_list **lexx, t_list **comm, t_big **p_big);
//08_cmd_creat/handle_redirections.c
t_list		*ft_set_r_in(t_lexer *token, 
				t_data **cominfo, t_list *lexx, t_big **p_big);
t_list		*ft_set_r_out(t_lexer *token, 
				t_data **cominfo, t_list *lexx, t_big **p_big);
//08_cmd_creat/create_argv_of_cmds.c
void		ft_add_arr_end(char *token_value, t_data **p_comm_info);
//08_cmd_creat/file_creator.c
int			fd_in_checker(t_data *comm_info, char *infile, t_big **p_big);
int			fd_here_creator(char *filename, bool wr);
int			fd_out_creator(bool appender, char *filename);
//08_cmd_creat/heredoc.c
int			heredoc_start(t_data *comm_info, char *limiter, t_big **p_big);
void		delete_heredoc(t_data *comm_info);
//08_cmd_creat/command_utils.c
void		exe_fd_error(t_big *big, t_data *comm_info_next);
t_data		*ft_pointer_next_command(t_list	*curr);
void		ft_free_cl(t_list **ll);
//08_cmd_creat/check_def_env_paths.c
void		ft_check_defaultpath(char *binary, char **binarypaths);

// BUILT-INS
//09_builtin/builtin_check.c
int			check_parent_builtin(t_data *comm_info);
int			check_child_builtin(t_data *comm_info);
//09_builtin/builtin_exit.c
void		ft_builtin_exit(t_data *comm_info, t_big *big);
//09_builtin/exit.c
void		ft_exit_minishell(t_big *big, bool print_exit);
//09_builtin/env.c
void		ft_print_env(t_data *comm_info, t_big *big);
//09_builtin/echo.c
void		ft_echo(t_data *comm_info, t_big *big);
//09_builtin/pwd.c
void		ft_print_pwd(t_big *big, t_data *comm_info);
//09_builtin/cd.c
void		ft_cd(t_big *big, char **argv);
//09_builtin/cd_error.c
int			cd_error_check(char **argv);
//09_builtin/export_1.c
int			ft_export(t_big *big, t_data *comm_info);
char		**ft_add_arr_back(char *str_to_add,
				char **array_old, char **array_new);
//09_builtin/export_2.c
void		ft_rmv_var_array(t_big *big, char *str_to_rmv);
void		export_exit_status(t_big *big, char **cmd_arg);
int			check_dash_in_var_name(char *argument);
//09_builtin/export_3.c
void		exp_replace_val(t_big *big, char *str_new_val);
//09_builtin/export_sort.c
void		ft_export_sort(t_big *big);
//09_builtin/unset.c
int			ft_unset(t_big *big, t_data *comm_info);
size_t		count_till_char(char *str, char up_to);
//09_builtin/help.c
void		ft_minishell_help(t_data *comm_info, t_big *big);

// EXECUTION
//10_exec/command_reader_01.c
int			ft_executer(t_big *big);
//10_exec/command_reader_02.c
int			get_exit_status_waitpid(t_big *big);
void		assign_exit_code(t_list	*cmdlist, int exit_status_binar, 
				t_big *big);
//10_exec/command_reader_print_err_01.c
int			is_valid_cmd_and_print_err(char **cmd_plus_args, t_big *big);
//10_exec/command_reader_print_err_02.c
int			is_dir_err_handling(char *cmd);
int			err_handling_executable(char *executable);
int			is_absolute_path_to_exe_err_handling(char *cmd);
int			get_path_from_env_or_binarypaths(t_big *big, char **cmd_plus_args);
//10_exec/exe_built-ins.c
void		exe_parent_builtin(t_data *comm_info, t_big *big);
int			fork_and_exe_child_builtin(t_data *comm_info, t_data *c_i_next, 
				t_big *big);
void		setup_and_exe_builtin_in_child(t_data *comm_info, t_data *c_i_next, 
				t_big *big);
void		exe_child_builtin(t_data *comm_info, t_big *big);
//10_exec/exe_binary.c
int			fork_and_exe_binary(t_data *comm_info, t_data *c_i_next, 
				t_big *big);
void		setup_and_exe_binary_in_child(t_data *comm_info, t_data *c_i_next, 
				t_big *big);
//10_exec/exe_binary_child_0.c
int			exe_child_binary(char **cmd_plus_args, char *env[]);

//10_exec/exe_binary_child_1.c
int			get_path_from_env_path_and_exe(char **cmd_plus_args, char *env[]);
char		*get_path(char *cmd_name, char **env);
char		*get_all_folders(const char *env_var_path, char **env);
char		*build_cmd_path(const char *folder, const char *cmd_name);
char		*exe_exists(char **folders, char *cmd_name);
//10_exec/exe_child_fd_setup_cleanup.c
void		fd_cleanup_in_child(t_big *big);
void		fd_cleanup_read_end_in_child(t_big *big);
void		setup_input_output_in_child(t_data *comm_info, t_data *c_i_next);
//10_execn/minishell_executer.c
int			is_minishell_command(char *cmd, char *env[]);
void		ft_ms_executer(char *env[]);
//10_exec/exe_error_handling.c
void		close_fd_with_error_handling(void);
void		w_errpipe_close(int open_fd);
void		w_errfork_close(int open_fd, int *pipe_fd);
void		w_dup2(int dupfd, int newfd);
//10_exec/exe_utils.c
int			is_absolute_path(const char *str, const char *str_cmp, int nmb);
int			is_attempt_to_execute(const char *str, const char *str_cmp, 
				int nmb);

// General Utils
//free/free.c
void		free_t_big(t_big *big);
//utils_strings/utils_string.c
int			count_strings(char **envp);
void		ft_freestr(char **lst);
int			ft_strcmp(const char *s1, const char *s2);
int			is_exact_string(const char *str_org, char *str_cmp);
int			is_last_char(const char *str, char c);
//utils_binary_path/binary_path.c
char		*build_cmd_path(const char *folder, const char *cmd_name);
//test_and_debug/test_and_debug.c
/*
void	printf_env(t_big *big);
*/
//test_and_debug/testprints.c --> only test functions
/*
void	ft_test_arr_print(char **input_arr, t_big *big);
void	ft_test_ll_print(t_list *lexx, t_big *big);
void	ft_test_command_print(t_data *comm_info, t_big *big);
*/
#endif
