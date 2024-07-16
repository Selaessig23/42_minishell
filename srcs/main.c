/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:36:30 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 10:26:50 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *const envp[])
{
	int	exitcode;

	exitcode = 0;
	if (argc == 1)
	{
		ft_printf("test\n");
		if (!*envp)
			error_handling(4);
		while (*envp)
		{
			ft_printf("%s", *envp);
			envp++;
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
