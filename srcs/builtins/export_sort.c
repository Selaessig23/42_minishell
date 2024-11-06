#include "minishell.h"

/**
 * DESCRIPTION:
 * this file handles the sorting request of builtin "export" access
 * (if command line input == "export" without any arguments)
 */

/**
 * Function counts a number of strings in array of strings.
 * It serves for memory allocation for an array of strings.

static int	count_strings(char **envp)
{
	int	i;

	i = 0;
	while (*envp)
	{
		i++;
		envp++;
	}
	return (i);
}
*/

/**
 * The function copies array of strings from environmental 
 * variables into array of strings that is a part of
 * struct t_big.

static char	**copy_envp_new(char **envp)
{
	char	**copy;
	int		i;
	int		j;
	// int		str_size;

	j = 0;
	i = count_strings(envp);
	// str_size = 0;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		error_handling(2);
	while (envp[j])
	{
		copy[j] = ft_strdup(envp[j]);
		j += 1;
	}
	copy[j] = NULL;
	return (copy);
}
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
		// printf("test 1A: %s vs. %s\n", env_cpy[i], env_cpy[i + 1]);
		if (ft_strncmp(env_cpy[i], env_cpy[i + 1], ft_strlen(env_cpy[i])) > 0)
		{
			ft_swap(&env_cpy[i], &env_cpy[i + 1]);
			// printf("test 1B: %s vs. %s\n", env_cpy[i], env_cpy[i + 1]);
			i = 0;
		}
		else
		{
			// printf("test 1C\n");
			i += 1;
		}
	}
	// ft_printf("test D\n");
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
	// printf("test 1\n");
	ft_export_sort_algo(&env_cpy);
	// printf("test 2\n");
	while (env_cpy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_cpy[i], 1);
		i += 1;
	}
	// printf("test 3\n");
	ft_free(env_cpy);
}
