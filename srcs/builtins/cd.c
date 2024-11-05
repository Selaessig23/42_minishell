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
 * @param p_pwd pointer to new_pwd to write the input in
 * 
 */
static void	ft_get_cwd(char **p_pwd)
{
	char	*pwd;

	pwd = *p_pwd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_handling(2);
}

/**
 * @brief function to update the env in big
 * 
 * @param p_env_oldpwd pointer to OLDPWD in env 
 * which has to be updated
 * @param oldpwd_new string with value of last pwd to update
 */
void	ft_update_oldpwd(char **p_env_oldpwd, char *oldpwd_new)
{
	char	*env_oldpwd;

	env_oldpwd = *p_env_oldpwd;
	if (!ft_strncmp("PWD=", oldpwd_new, 4))
		*p_env_oldpwd = ft_strjoin("OLDPWD=", (oldpwd_new + 4));
	else
		*p_env_oldpwd = ft_strjoin("OLDPWD=", (oldpwd_new));
	free(env_oldpwd);
}
/**
 * @brief function to update the env in big
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
static void	ft_update_env(t_big *big)
{
	char	**envp;
	char	*temp1;
	char	*new_pwd;

	new_pwd = NULL;
	envp = big->env;
	while (*envp && ft_strncmp("PWD=", *envp, 4))
		envp++;
	if (*envp == NULL || ft_strncmp("PWD=", *envp, 4))
		ft_get_cwd(&temp1);
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
		ft_update_oldpwd(&(*envp), (temp1));
	free(temp1);
}

/**
 * @brief function to change the current working directory
 * and update the env-variable, give error message in case of
 * error
 * 
 * TODO: set exit status in struct big after execution
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
void	ft_cd(t_big *big, char **argv)
{
	int		i;

	i = 0;
	if (ft_arrlen(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		big->exit_code = 1;
	}
	else if (ft_arrlen(argv) < 2)
		ft_putstr_fd("minishell: cd: Please specifiy the path you want to change to\n", 2);
	else
	{
		i = chdir(argv[1]);
		if (i < 0)
			ft_dprintf("minishell: cd: %s: No such file or directory\n", argv[1]);
		// if (i < 0)
		// 	error_handling(0);
		ft_update_env(big);
		big->exit_code = 0;
	}
}

