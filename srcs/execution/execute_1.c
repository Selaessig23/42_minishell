
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
	if(!all_folders)
		return(NULL);
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
static int	ft_execve_no_free(char *cmd, char **cmd_plus_args, char *env[])
{
	execve(cmd, cmd_plus_args, env);
	{
	if (errno == ENOENT)
		return (127);
	else if (errno == EACCES)
		return (126);
	else
		return (EXIT_FAILURE);
	}
}

/**
 * This function checks if a given command cmd refers to a valid directory.
 * 
 * 1. Calls stat: It retrieves the file status of cmd and stores it 
 * in a struct stat variable (check_dir).
 * 2. Checks Path Prefix and Directory Type. If cmd starts with ./, /, or 
 * ends with /, and the path corresponds to a directory 
 * (S_ISDIR evaluates to true), it returns 0.
 */
static int	is_command_directory(char *cmd)
{
	struct stat	check_dir;

	if (stat((cmd), &check_dir) == 0)
	{
		if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1) 
			|| (is_last_char(cmd, '/'))) && S_ISDIR(check_dir.st_mode))
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

/**
 * Function checks if the command cmd is exactly "./minishell". If so, 
 * it executes the `ft_ms_executer` function.
 * 
 * If the command is not "./minishell", it simply returns 1.
 * 
 * The condition cmd[ft_strlen("./minishell")] == '\0' checks if the string 
 * cmd has exactly the content ./minishell, with no additional characters after it.
 */
static int is_minishell_command(char *cmd, char *env[])
{
	if (!ft_strncmp(cmd, "./minishell", ft_strlen("./minishell"))
		&& cmd[ft_strlen("./minishell")] == '\0')
	{
		ft_ms_executer(env);
		return (0);
	}
	else
		return (1);
}

/**
 * @brief Executes a command with its arguments, searching for 
 * the executable path.
 * Return value is an exit code of a child process.
 * 
 * @param argument The command and its arguments as a string.
 * @param env The environment variables array.
 */
int	exe_child_binary(char **cmd_plus_args, char *env[])
{
	int	exit_code;

	exit_code = -14;
	// calling minishell in minishell

	if (!is_minishell_command(cmd_plus_args[0], env))
		return (0);
	else if (!is_command_directory(cmd_plus_args[0]))
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	
	// run a file with no permission
	if (!ft_strncmp(cmd_plus_args[0], "./", 2))
	{
		//printf("!ft_strncmp(cmd_plus_args[0], \"./\" 2\n");
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	}

	// new && 
	struct stat	check_dir;

	if (access(cmd_plus_args[0], F_OK | X_OK) == 0 && stat((cmd_plus_args[0]), &check_dir) != 0)
	{
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	}

	//printf("get cmd_path\n");
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_path(cmd_plus_args[0], env);
	if (!cmd_path)
		return (127);

	execve(cmd_path, cmd_plus_args, env);
	if (errno == ENOENT)
	{
		free(cmd_path);
		return (127);
	}
	if (errno == EACCES)
	{
		free(cmd_path);
		return(126);
	}
	else
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
}
