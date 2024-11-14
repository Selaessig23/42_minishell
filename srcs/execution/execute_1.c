
#include "minishell.h"

/* Like the strncmp() function, but compares entire strings, no need to pass
a size.
-	If the two strings are identical, the function returns 0, indicating
	no difference.
-	If a difference is found, and the first differing character in the second
	string (s2) is greater than the character at the same position in the first
	string (s1), the result is negative.
-	If the first differing character in s2 is less than the character at the
	same position in s1, the result is positive.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * This function frees an array of strings.
 * The function iterates through each string in the array, freeing each one 
 * individually. After freeing all the strings, it frees the array itself.
 */
void	ft_freestr(char **lst)
{
	int		i;
	char	*n1;

	i = 0;
	if (!lst)
		return ;
	while (lst[i] != NULL)
	{
		n1 = lst[i];
		i++;
		free(n1);
	}
	free(lst);
}

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
		print_stderr("malloc");
		return (NULL);
	}
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
		print_stderr("malloc");
	return (cmd_path);
}

/**
 * @brief Checks if a command exists in the provided folders and 
 * returns its path.
 * 
 * @param folders An array of folder paths.
 * @param cmd_name The name of the command to check.
 * @return The path to the executable if found, or NULL if not.
 */
char	*exe_exists(char **folders, char *cmd_name)
{
	char	*path;
	int		i;

	i = 0;
	while (folders[i] != NULL)
	{
		path = build_cmd_path(folders[i], cmd_name);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Retrieves the folders from the 'PATH' environment variable.
 * 
 * @param env_var_path The name of the environment variable (e.g., "PATH").
 * @param env The environment variables array.
 * @return A pointer to the first folder in the PATH or NULL if not found.
 */
char	*get_all_folders(const char *env_var_path, char **env)
{
	size_t	i;
	size_t	len;
	char	*current_env_var;

	i = 0;
	while (env[i])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		current_env_var = ft_substr(env[i], 0, len);
		if (!current_env_var)
			perror_and_exit("malloc", NULL);
		if (ft_strcmp(current_env_var, env_var_path) == 0)
		{
			free(current_env_var);
			return (env[i] + len + 1);
		}
		free(current_env_var);
		i++;
	}
	return (NULL);
}

/**
 * @brief Obtains the path of a command by searching the 'PATH' 
 * environment variable.
 * 
 * @param cmd_name The name of the command to locate.
 * @param env The environment variables array.
 * @return The command path if found, or NULL if not.
 */
char	*get_path(char *cmd_name, char **env)
{
	char	**folders;
	char	*path;
	char	*all_folders;

	all_folders = get_all_folders("PATH", env);
	folders = ft_split(all_folders, ':');
	if (!folders)
	{
		print_stderr("malloc");
		return (NULL);
	}
	path = exe_exists(folders, cmd_name);
	if (!path)
	{
		ft_freestr(folders);
		return (NULL);
	}
	else
	{
		ft_freestr(folders);
		return (path);
	}
}

/**
 * @brief Executes a command with its arguments, searching for 
 * the executable path.
 * 
 * @param argument The command and its arguments as a string.
 * @param env The environment variables array.
 */
void	exe_child_binary(char **cmd_plus_args, char *env[])
{
	char	*cmd_path;
	// char	*temp;

	cmd_path = NULL;
	// printf("test: %s\n", cmd_plus_args[0]);
	if (!ft_strncmp(cmd_plus_args[0], "./minishell", ft_strlen("./minishell"))
		&& cmd_plus_args[0][ft_strlen("./minishell")] == '\0')
	// 	//&& ft_strlen(cmd_plus_args[0]) == ft_strlen("./minishell"))
	{
		// printf("test 2: %zu\n", ft_strlen(cmd_plus_args[0]));
		ft_ms_executer(env);
	}
	// else
	// {
		// printf("test 3\n");
		if (access(cmd_plus_args[0], F_OK | X_OK) == 0)
		{
			if (execve(cmd_plus_args[0], cmd_plus_args, env) == -1)
				return ;
				//exit(127);
		}
		cmd_path = get_path(cmd_plus_args[0], env);
		if (!cmd_path)
			return ;
			//exit(127);
		if (execve(cmd_path, cmd_plus_args, env) == -1)
		{
			free(cmd_path);
			return ;
			//exit(127);
		}
	// }
}
