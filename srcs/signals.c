#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the the following behaviour for signals will be
 * integrated:
 * >ctrl-C (=sigint) displays a new prompt on a new line.
 * >ctrl-D exits the shell.
 * >ctrl-\ (=sigquit) does nothing.


void	handle_sigquit(int sig)
{
	sigaction(SIGQUIT, )
}

void	handle_sigint(int sig)
{

}
 */