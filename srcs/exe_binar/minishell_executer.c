#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the incrementation of 
 * env-variable $SHLVL in case of executing minishell
 * within a minishell-environment is handled
 */

/*
size_t	ft_countnbr(int n)
{
	size_t  counter;

	counter = 1;
	if (counter < 0)
		counter += 1;
	while (n > 9)
	{
		n /= 10;
		counter += 1;
	}
	return (counter);

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
*/

/**
 * @brief function to execute the builtin function "exit", 
 * it closes the programm and frees all allocated memory
 * 
 * @param env an array of strings with all environmental variables
 */
void    ft_ms_executer(char *env[])
{
	char	*temp;
	char    *shlvl_new;
	char    *count_new;
	size_t  count;
	
	count = 0;
	while (*env && ft_strncmp("SHLVL", *env, 4))
		env++;
	temp = *env;
	printf("test 2a: temp = %s\n", temp + 6);
	count = ft_atoi(temp + 6);
	printf("test 2b: count = %zu\n", count);
	count += 1;
	count_new = ft_itoa(count);
	if (!count_new)
		error_handling(1);
	shlvl_new = ft_strjoin("SHLVL=", count_new);
	if (!shlvl_new)
		error_handling(1);
	free(count_new);
	printf("test 2c: env new = %s\n", shlvl_new);
	*env = shlvl_new;
	free (temp);
}
