#include "minishell.h"

/**
 * DESCRIPTION:
 * this file handles the sorting request of builtin "export" access
 * (if command line input == "export" without any arguments)
 */

/**
 * @brief function to swap two pointers
 * 
 * @param a 1st pointer
 * @param b 2nd pointer
 */
static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief function to sort the array of env
 * 
 * @param env_cpy copy of array env that should be sorted
 */
static void	ft_export_sort_algo(char ***p_env_cpy)
{
	int		i;
	char	**env_cpy;

	env_cpy = *p_env_cpy;
	i = 0;
	while (env_cpy[i] && env_cpy[i + 1])
	{
		if (ft_strncmp(env_cpy[i], env_cpy[i + 1], ft_strlen(env_cpy[i])) > 0)
		{
			ft_swap(&env_cpy[i], &env_cpy[i + 1]);
			i = 0;
		}
		else
			i += 1;
	}
}

/**
 * @brief function to organise the sorting request of the 
 * builtin function "export"
 */
void	ft_export_sort(t_big *big)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = copy_envp(big->env);
	ft_export_sort_algo(&env_cpy);
	while (env_cpy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_cpy[i], 1);
		i += 1;
	}
	ft_free(env_cpy);
}
