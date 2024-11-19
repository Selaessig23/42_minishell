/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:32:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 22:34:30 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// When Bash interprets a command that starts with a /, 
// it is considered an absolute path to a file or directory.
int	is_absolute_path(const char *str, const char *str_cmp, int nmb)
{
	if (!ft_strncmp(str, str_cmp, nmb))
		return (1);
	return (0);
}

/**
 * Function checks if the string starts with "./".
 * In Bash, if a command starts with "./", it interprets it as 
 * an attempt to execute a program or script located in the 
 * current working directory or in the relative path to 
 * a file or executable.
 * 
 * This function compares the first nmb characters of 
 * two strings (str and str_cmp) using ft_strncmp, 
 * and returns 0 if they match, otherwise it returns 1.
 */
int	is_attempt_to_execute(const char *str, const char *str_cmp, int nmb)
{
	if (!ft_strncmp(str, str_cmp, nmb))
		return (1);
	return (0);
}
