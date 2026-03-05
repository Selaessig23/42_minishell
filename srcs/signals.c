#include "minishell.h"
#include <sys/ioctl.h>


/**
 * DESRIPTION: 
 * in this file the the following behaviour for signals will be
 * integrated:
 * >ctrl-C (=sigint) displays "^C" followd by a new prompt on a new line, 
 * same on heredoc (here it closes heredoc)!
 * >ctrl-D exits the shell, on heredoc (only on on empty line:)
 * stops heredoc and returns error message: 
 * "bash: warning: here-document at line 1 delimited by end-of-file 
 * (wanted `$limiter')"
 * on non empty line nothing happens
 * >ctrl-\ (=sigquit) does nothing (do not quit!).
*/

static void	handle_sigint_non(int sig)
{
	(void) sig;
	ft_putstr_fd("^C\n", 1);
	signalnum = 3;
}

static void	handle_sigint_inter(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0); //clear the input line
		rl_on_new_line(); //Go to a new line
		rl_redisplay(); //Redisplay the prompt
		signalnum = 1;
	}
	else
	{
		rl_replace_line("", 0); //clear the input line
		rl_on_new_line(); //Go to a new line
		rl_redisplay(); //Redisplay the prompt
		signalnum = 2;
	}
}

/**
 * @brief function that changes the standard behaviour of terminal
 * to not print control sequences like ^\ or ^C if false
 * 
 * 1st the current set has to be catched
 * 2nd the new config (~ECHOCTL) has to be implemented
 * 3rd the new config has to be set
 * 
 * @param rl_antes a booelean value that determines 
 * wether to enable (true) printing control sequences or not (false)
*/
int	ft_terminal_config(bool rl_antes)
{
	struct termios	termios_p;
	
	(void) rl_antes;
	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return (-1);
	if (rl_antes == true)
	{
		termios_p.c_lflag |= ECHOCTL;
		termios_p.c_lflag &= ~ICANON;
	}
	else
	{
		termios_p.c_lflag |= ICANON;
		termios_p.c_lflag &= ~ECHOCTL;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
	{
		perror("tcsetattr");
		return (-1);
	}
	return (0);
}

/**
 * @brief in this function signal actions are coordinated
 * 1st signalset is set to zero
 * 2nd signalsets are only set to those signals required (NECESSARY???)
 * 3rd signals sigquit and sigint are defined
 * 
 * @param heredoc a boolean value that determines if incoming signals should be
 * handled in commandline-input mode(false) or in heredoc-mode(true) 
 * as readline behaviour in heredoc needs special treatment 
 * (it also has to exit heredoc)
 * 
 */
int	ft_handle_signals(bool heredoc)
{
	sigset_t			set;
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (heredoc == true)
	{
		sa.sa_handler = &handle_sigint_inter;
		if (ft_terminal_config(true) == -1)
		{
			perror("tcgetattr faulty\n");
			return (-1);
		}
	}
	else
	{
		sa.sa_handler = &handle_sigint_non;
		if (ft_terminal_config(false) == -1)
		{
			perror("tcgetattr faulty\n");
			return (-1);
		}
	}
	sa.sa_flags = 0;
	if (sigemptyset(&set) == -1)
	{
		perror("sigemtyset\n");
		return (1);
	}
	sa.sa_mask = set;
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
