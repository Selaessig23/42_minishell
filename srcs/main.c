/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:36:30 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/17 17:41:10 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int		exitcode;
	int		i;
	char	*testinput;

	(void) argv;
	i = 0;
	exitcode = 0;
	if (argc == 1)
	{
		if (!*__environ)
			error_handling(4);
		while (1)
		{
			testinput = readline("Marina's and Markus' minishell>");
			if (!ft_strncmp(testinput, "env", 3) && ft_strlen(testinput) == 3)
			{
				while (*__environ)
				{
					ft_printf("%s\n", *__environ);
					__environ++;
				}
			}
			else if (!ft_strncmp(testinput, "EXIT", 4) && ft_strlen(testinput) == 4)
			{
				exit (EXIT_SUCCESS);
				free(testinput);
			}
			else
				ft_printf("%s\n", testinput);
			free(testinput);
		}
	}
	else
		error_handling(1);
	return (exitcode);
}
