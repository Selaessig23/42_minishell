#include "minishell.h"

/**
 * Function to clean t_big struct.
 * A task: to modify it for 
*/
void	free_t_big(t_big *big)
{
	ft_free(big->env);
	free(big->list);
	free(big);
}

// Temporary function to display what t_big holds.
void	printf_env(t_big *big)
{
	int	i;

	i = 0;
	while (big->env[i])
	{
		ft_printf("big->env[%i]:\n%s\n", i, big->env[i]);
		i++;
	}
	ft_printf("big->env[%i]:\n%s\n", i, big->env[i]);
}

/**
 * The function copies array of strings from enironmental 
 * variables into array of strings that is a part of
 * struct t_big. Temp.
*/
static char	**copy_envp(char **envp)
{
	char	**copy;
	size_t	i;
	size_t	j;
	size_t	str_size;

	j = 0;
	i = ft_arrlen(envp);
	str_size = 0;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		error_handling(2);
	while (envp[j])
	{
		str_size = ft_strlen(envp[j]) + 1;
		copy[j] = ft_calloc(str_size, sizeof(char));
		if (!copy[j])
			error_handling(2);
		copy[j] = ft_memcpy(copy[j], envp[j], str_size);
		j++;
	}
	envp[j] = NULL;
	return (copy);
}

/**
 * Function initialize t_big struct and copies the environmental
 * varibles into array of strings char **env.
 * 
 * @param t_big	*big
 * @param char **envp
 * @param char	**env
*/

t_big	*init_t_big(char **envp)
{
	t_big	*big;
	char	**env;

	big = ft_calloc(1, sizeof(t_big));
	if (big == NULL)
		error_handling(2);
	big->list = NULL;
	env = copy_envp(envp);
	big->env = env;
	return (big);
}
