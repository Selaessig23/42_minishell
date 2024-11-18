#include "minishell.h"

/**
 * Function to clean t_big struct.
*/
void	free_t_big(t_big *big)
{
	if (big->env)
		ft_free(big->env);
	// printf("test1\n");
	if (big->cmdlist)
		ft_free_cl(&(big->cmdlist));
	// printf("test2\n");
	if (big->binarypaths)
		ft_free(big->binarypaths);
	// printf("test3\n");
	free(big);
	big = NULL;
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
 * Function counts a number of strings in array of strings.
 * It serves for memory allocation for an array of strings.
*/
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

/**
 * The function copies array of strings from environmental 
 * variables into array of strings that is a part of
 * struct t_big.
*/
char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;
	int		j;
	int		str_size;

	j = 0;
	i = count_strings(envp);
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
	copy[j] = NULL;
	return (copy);
}

/**
 * Function initialize t_big struct and copies the environmental
 * varibles into array of strings char **env.
 * 
 * @param t_big	*big
 * @param char **envp
 * @param char	**env
 * 
 * by default big->exe = true;
*/

t_big	*init_t_big(char **envp)
{
	t_big	*big;
	char	**env;
	char	*all_folders;

	big = ft_calloc(1, sizeof(t_big));
	if (big == NULL)
		error_handling(2);
	big->cmdlist = NULL;
	env = copy_envp(envp);
	big->env = env;
	all_folders = get_all_folders("PATH", env);
	big->binarypaths = ft_split(all_folders, ':');
	if (!big->binarypaths)
	{
		perror("malloc");
		return (NULL);
	}
	big->exit_code = 0;
	big->count_commds = 0;
	big->exe = true;
	return (big);
}
