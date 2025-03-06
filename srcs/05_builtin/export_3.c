/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 14:51:55 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function replaces the old value of the environmental
 * variable to the new one.
 * @param var_to_rmv is a string with only a name of environmental
 * variable, it is retrived from a 'str_new_val'
 * @param str_new_val is a string as an argument for export command
 * which contains a variable that is already in env array and also either
 * consist of '=' and following characters or only '=' sign.
 */
void	exp_replace_val(t_big *big, char *str_new_val)
{
	char	**old;
	char	**new;
	char	**var_to_rmv;

	new = NULL;
	old = NULL;
	var_to_rmv = ft_split(str_new_val, '=');
	ft_rmv_var_array(big, var_to_rmv[0]);
	ft_free(var_to_rmv);
	old = big->env;
	new = ft_add_arr_back(str_new_val, old, new);
	big->env = new;
	if ((old))
		ft_free(old);
}
