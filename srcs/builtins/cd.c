#include "minishell.h"

/** DESCRIPTION
 * in this file the inbuilt-function "exit"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to change the current working directory
 * and update the env-variable, give error message in case of
 * error
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
void	ft_cd(t_big *big)
{
	(void) big;
	//use of chdir
	//maybe use also getcwd to check if it was set correctly?
}

