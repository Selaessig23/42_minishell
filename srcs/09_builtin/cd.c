/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:50:02 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/21 15:06:13 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** DESCRIPTION
 * in this file the inbuilt-function "cd"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to get current working directory
 * if there is no variable for it in env,
 * required for setting $OLDPWD 
 * 
 * @param p_pwd pointer to new_pwd to write the input in
 * 
 */
static char	*ft_get_cwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_and_exit(2);
	return (pwd);
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
	char	*oldpwd_old;

	oldpwd_old = *p_env_oldpwd;
	*p_env_oldpwd = ft_strjoin("OLDPWD=", (oldpwd_new));
	free(oldpwd_old);
}

/**
 * @brief function to update the env in big
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
static void	ft_update_env(t_big *big, char *oldpwd_old)
{
	char	**envp;
	char	*old_pwd;
	char	*new_pwd;

	envp = big->env;
	old_pwd = NULL;
	new_pwd = NULL;
	while (*envp && (ft_strncmp("PWD=", *envp, 4)))
		envp++;
	if (*envp)
	{
		old_pwd = *envp;
		new_pwd = getcwd(NULL, 0);
		free(old_pwd);
		if (!new_pwd)
			error_and_exit(2);
		*envp = ft_strjoin("PWD=", new_pwd);
		free(new_pwd);
	}
	envp = big->env;
	while (*envp && (ft_strncmp("OLDPWD=", *envp, 7)))
		envp++;
	if (*envp && !ft_strncmp("OLDPWD=", *envp, 7))
		ft_update_oldpwd(&(*envp), (oldpwd_old));
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
// execution IF exe is true
// if exe is false - checking for errors and exit assigns exit code
// F_OK -- test for file existence. 
void	ft_cd(t_big *big, char **argv)
{
	int		err;
	char	*pwd_old;

	err = 0;
	pwd_old = NULL;
	err = cd_error_check(argv);
	if (err > 0)
		big->exit_code = 1;
	else if (err == 0 && big->exe == true)
	{
		pwd_old = ft_get_cwd();
		if (chdir(argv[1]) < 0)
		{
			free(pwd_old);
			error_and_exit(errno);
		}
		ft_update_env(big, pwd_old);
		free(pwd_old);
		big->exit_code = 0;
	}
}
