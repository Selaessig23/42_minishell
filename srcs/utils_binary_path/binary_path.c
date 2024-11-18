/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:39:16 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 09:19:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Used during command creation and execution.
// During command creation in `ft_match_counter` 
// and `ft_match_filler` functions,
// and during execution `exe_exists` function.

/**
 * @brief Constructs the full path to a command by joining a folder and 
 * command name.
 * 
 * @param folder The directory containing the command.
 * @param cmd_name The name of the command.
 * @return The full command path or NULL on failure.
 */
char	*build_cmd_path(const char *folder, const char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin(folder, "/");
	if (!temp)
	{
		perror("malloc");
		return (NULL);
	}
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
		perror("malloc");
	return (cmd_path);
}
