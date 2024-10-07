#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the the following behaviour for signals will be
 * integrated:
 * >ctrl-C (=sigint) displays "^C" followd by a new prompt on a new line, same on heredoc!
 * >ctrl-D exits the shell (use built-in exit), within heredoc
 * on empty line: stops heredoc and returns error message: 
 * "bash: warning: here-document at line 1 delimited by end-of-file (wanted `$limiter')"
 * on non empty line nothing happens
 * >ctrl-\ (=sigquit) does nothing (do not quit!).
*/

// static void	handle_sigquit(int sig)
// {
// 	sigaction(SIGQUIT, )
// }

static void	handle_sigint(int sig)
{
	// (void) sig;
	if (sig == SIGINT)
	{
		// ft_putstr_fd("\n", 1);
		// rl_replace_line("", 0); //clear the input line
		// rl_on_new_line(); //Go to a new line
		// rl_redisplay(); //Redisplay the prompt
		signalnum = 1;
	}
	else
	{
		write(2, "\n", 1);
		rl_replace_line("", 0); //clear the input line
		rl_on_new_line(); //Go to a new line
		rl_redisplay(); //Redisplay the prompt
		signalnum = 2;
		// big->
		// ft_putstr_fd("do nothing\n", 1);
	}
}

/**
 * @brief in this function signal actions are coordinated
 * 1st all signal are set to zero
 * 2nd signalsets are only set to those signals required
 * 3rd signals sigquit and sigint are defined
 */
int	ft_handle_signals(void)
{
	sigset_t set;
	struct sigaction sa;
	// int signum;

	sa.sa_handler = &handle_sigint;
	if (sigemptyset(&set) == -1)
	{
		perror("sigemtyset\n");
		return (1);
	}
	sigaddset(&set, SIGINT);
	// sigaddset(&set, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	// handle_sigquit();
	return (0);
}