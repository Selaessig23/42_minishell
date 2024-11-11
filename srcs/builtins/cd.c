/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:49:13 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 20:53:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	cd_error(char **argv)
{
	if (ft_arrlen(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (access(argv[1], F_OK))
	{
		ft_dprintf("minishell: cd: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	else if (access(argv[1], X_OK))
	{
		ft_dprintf("minishell: cd: %s: Permission denied\n", argv[1]);
		return (1);
	}
	else
		return (0);
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
	bool	err;

	err = false;
	if (ft_arrlen(argv) < 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd("Please specifiy the path you want to change to\n", 2);
		big->exit_code = 0;
		return ;
	}
	else if (cd_error(argv))
		err = true;
	if (err == true)
		big->exit_code = 1;
	else if (err == false && big->exe == true)
	{
		chdir(argv[1]);
		ft_update_env(big);
		big->exit_code = 0;
	}
}
