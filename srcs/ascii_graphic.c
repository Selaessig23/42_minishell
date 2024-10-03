#include "minishell.h"

void	ft_welcome(void)
{
	int	fd;

	fd = 1;
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("            _         _       _            _  _\n", fd);
	ft_putstr_fd("	   (_)       (_)     | |          | || |\n", fd);
	ft_putstr_fd("_ __ ___    _  _ __   _  ___ | |__    ___ | || |\n", fd);
	ft_putstr_fd("| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n", fd);
	ft_putstr_fd("| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n", fd);
	ft_putstr_fd("|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|\n", fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n", fd);
	ft_minishell_help(fd);
	ft_putstr_fd("HAVE FUN USING IT!!!\n\n", fd);
}