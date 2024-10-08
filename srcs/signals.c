#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the the following behaviour for signals will be
 * integrated:
 * >ctrl-C (=sigint) displays "^C" followd by a new prompt on a new line, same on heredoc (here it closes heredoc)!
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
		ft_putstr_fd("^C\n", 2);
		rl_replace_line("  hi", 0); //clear the input line
		rl_on_new_line(); //Go to a new line
		rl_redisplay(); //Redisplay the prompt
		signalnum = 1;
	}
	else
	{
		// write(2, "\n", 1);
		rl_replace_line("", 0); //clear the input line
		// rl_on_new_line(); //Go to a new line
		// rl_redisplay(); //Redisplay the prompt
		signalnum = 2;
		// big->
		// ft_putstr_fd("do nothing\n", 1);
	}
}

/**
 * @brief function that changes the standard behaviour of terminal
 * to not print control sequences like ^\
 * 
 * 1st the current set has to be catched
 * 2nd the new config (~ECHOCTL) has to be implemented
 * 3rd the new config has to be set
 * 
 * @param 
*/
int	ft_terminal_config(void)
{
	struct termios	termios_p;
	
	// termios_p = NULL;
	// ft_memset(termios_p, 0, sizeof(termios_p));
	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return (-1);
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
	{
		perror("tcsetattr");
		return (-1);
	}
	return (0);
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

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = 0;
	if (ft_terminal_config() == -1)
	{
		perror("tcgetattr faulty\n");
		return (-1);
	}
	if (sigemptyset(&set) == -1)
	{
		perror("sigemtyset\n");
		return (1);
	}
	sa.sa_mask = set;
	sigaddset(&set, SIGINT);
	// sigaddset(&set, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	// handle_sigquit();
	return (0);
}