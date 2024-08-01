/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:20:13 by mstracke          #+#    #+#             */
/*   Updated: 2024/08/01 12:31:33 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//maybe rename to bin_path for binary path
typedef struct s_envp{
	char	**bin_paths;
	char	***commands;
	char	*outfile;
	char	*infile;
	size_t	commands_no;
}				t_envp;

//linked list for lexer analysis -> token system
typedef struct s_list{
	void			*value;
	struct s_list	*next;
}				t_list;
//required functions from libft
//
//f

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
