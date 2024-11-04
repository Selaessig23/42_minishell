#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the incrementation of 
 * env-variable $SHLVL in case of executing minishell
 * within a minishell-environment is handled
 */


size_t	ft_countnbr(int n)
{
    
}

void	ft_writenbr(int n)
{
	char *nbr;

    nbr = ft_calloc((ft_countnbr(n) + 1), sizeof(char *))
    if (n == -2147483648)
		// write(fd, "-2147483648", 11);
        nbr = "-2147483648";
	if (n < 0)
	{
		nbr[i] = '-';
        n *= (- 1);
        // ft_putchar_fd(45, fd);
		// ft_putnbr_fd((n * (-1)), fd);
	}
    while (n > 9)
    {
        
        n /= 10;
    }
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + 48), fd);
	}
	else
		ft_putchar_fd((n + 48), fd);
}

/**
 * @brief function to execute the builtin function "exit", 
 * it closes the programm and frees all allocated memory
 * 
 * @param big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param prompt string that has to be freed before exit the program
 */
void    ft_ms_executer(char *env[])
{
	char	*temp;
    char    *shlvl_new;
    size_t  count;
    
    count = 0;
    while (*env && ft_strncmp("SHLVL", *env, 4))
		env++;
		temp = *env;
    count = ft_atoi(temp);
    count += 1;
    shlvl_new = ft_writenbr(count);
    *env = shlvl_new;
    free (temp);
}
