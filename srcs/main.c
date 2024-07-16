/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:36:30 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 10:47:30 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *const env[])
{
	int	exitcode;
	int	i;

	(void) argv;
	i = 0;
	exitcode = 0;
	if (argc == 1)
	{
		ft_printf("test\n");
		if (!*env)
			error_handling(4);
		while (*env)
		{
			ft_printf("%s\n", *env);
			env++;
		}
		//while (*envp && ft_strncmp("PATH", *envp, 4))
		//	envp++;
		//paths = ft_split(*envp, ':');
		//if (!paths)
		//	error_handling(2);
		//init_check(argv, paths, &infos);
		//ft_free(paths);
		//exitcode = init_ms(envp);
		//free_struct(&infos);
	}
	else
		error_handling(1);
	return (exitcode);
}
