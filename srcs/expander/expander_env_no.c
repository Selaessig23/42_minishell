#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be reduced from
 *  $+varname as it does not match any env var name
 */

/**
 * @brief function that deletes part after $ from value
 * as it could not be verified as variable of envp
 * 
 * @param value_old	the value of the command line input token that has
 * to be adapted
 * @param wrongenvp not matching envp variable name, starting with $
 */
char	*delete_varname_from_value(char *value_old, char *wrongenvp)
{
	int		i;
	char	*value_new;
	char	*temp;

	i = 0;
	temp = value_old;
	// printf("test 3A: value_old: %s\nwrongenvp: %s\n", value_old, wrongenvp);
	i = (ft_strlen(value_old) - ft_strlen(wrongenvp));
	value_new = ft_calloc((i + 1), sizeof(char));
	// printf("calloc: %i\n", (i + 1));
	if (!value_new)
		error_handling(2);
	i = 0;
	while (value_old[i] && 
		(!ft_strnstr(&(value_old[i]), wrongenvp, ft_strlen(wrongenvp))))
	{
		value_new[i] = value_old[i];
		i++;
	}
	while (value_old[i + ft_strlen(wrongenvp)])
	{
		value_new[i] = value_old[i + ft_strlen(wrongenvp)];
		i++;
	}
	value_new[i] = '\0';
	// printf("test 4B value_new: %s\n", value_new);
	return (value_new);
}
