/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:36:30 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 17:15:27 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int	exitcode;
	int	i;

	(void) argv;
	i = 0;
	exitcode = 0;
	if (argc == 1)
	{
		ft_printf("test\n");
		if (!*__environ)
			error_handling(4);
		while (*__environ)
		{
			ft_printf("%s\n", *__environ);
			__environ++;
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
