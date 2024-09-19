#include "minishell.h"

/** DESCRIPTION
 * in this file the inbuilt-function "exit"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to get current working directory
 * if there is no variable for it in env
 * 
 */
static char	*ft_get_cwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_handling(2);
	return (pwd);
}

/**
 * @brief function to update the env in big
 * 
 * @param p_oldpwd pointer to OLDPWD in env
 */
void	ft_update_oldpwd(char **p_env_oldpwd, char *new_pwd)
{
	char	*env_oldpwd;

	env_oldpwd = *p_env_oldpwd;
	if (!ft_strncmp("PWD=", new_pwd, 4))
		*p_env_oldpwd = ft_strjoin("OLDPWD=", (new_pwd + 4));
	else
		*p_env_oldpwd = ft_strjoin("OLDPWD=", (new_pwd));
	free(env_oldpwd);
}
/**
 * @brief function to update the env in big
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
static void	ft_update_env(t_big *big, char **argv)
{
	char	**envp;
	char	*temp1;
	// char	*temp2;
	char	*new_pwd;

	new_pwd = NULL;
	envp = big->env;
	while (*envp && ft_strncmp("PWD=", *envp, 4))
		envp++;
	if (*envp == NULL || ft_strncmp("PWD=", *envp, 4))
		temp1 = ft_get_cwd;
	else
	{
		temp1 = *envp;
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
			error_handling(2);
		*envp = ft_strjoin("PWD=", new_pwd);
		free(new_pwd);
		envp = big->env;
	}
	while (*envp && ft_strncmp("OLDPWD=", *envp, 7))
		envp++;
	if (*envp && !ft_strncmp("OLDPWD=", *envp, 7))
		ft_update_oldpwd(&envp, (temp1));
	// printf("temp before freeing: %s\n", temp);
	free(temp1);
	// fre(temp2);
}

/**
 * @brief function to change the current working directory
 * and update the env-variable, give error message in case of
 * error
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
void	ft_cd(t_big *big, char **argv)
{
	char	**envp;
	// char	*temp;
	char	*new_pwd;
	int		i;

	i = 0;
	envp = big->env;
	new_pwd = NULL;
	if (ft_arrlen(argv) < 2)
		ft_putstr_fd("Please specifiy the path you want to change to\n", 1);
	else
	{
		i = chdir(argv[1]);
		if (i < 0)
			error_handling(0);
	}
	ft_update_env(big, argv);
	// //maybe use also getcwd to check if it was set correctly?
	// while (*envp && ft_strncmp("PWD=", *envp, 4))
	// 	envp++;
	// temp = *envp;
	// new_pwd = getcwd(NULL, 0);
	// *envp = ft_strjoin("PWD=", new_pwd);
	// free(new_pwd);
	// envp = big->env;
	// while (*envp && ft_strncmp("OLDPWD=", *envp, 4))
	// 	envp++;
	// *envp = ft_strjoin("OLDPWD=", (temp + 4));
	// // printf("temp before freeing: %s\n", temp);
	// free(temp);
}

