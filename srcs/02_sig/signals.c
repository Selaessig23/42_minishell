#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the following behaviour for signals will be
 * integrated:
 * >ctrl-C (=sigint) displays "^C" followd by a new prompt on a new line, 
 * same on heredoc (here it closes heredoc)!
 * >ctrl-D exits the shell, on heredoc (only on empty line:)
 * stops heredoc and returns error message: 
 * "bash: warning: here-document at line 1 delimited by end-of-file 
 * (wanted `$limiter')"
 * on non empty line nothing happens
 * >ctrl-\ (=sigquit) does nothing (do not quit!).
*/
/**
 * @brief function to reset the global variable
 * g_signalnum (it is only set to !0 if a signal was used)
 * and defines the exit code in case of a signal
 * 
 * @brief big struct with all necessary information to run a command, 
 * exit_codes are saved here
 */
void	signal_set_exitcode_and_reset(t_big *big)
{
	g_signalnum = 0;
	big->exit_code = 130;
}

// !This is for heredoc readline
static void	handle_sigint_non(int sig)
{
	(void) sig;

	g_signalnum = 1;
	ft_putstr_fd("^C", 2);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

// this is for readline in main
static void	handle_sigint_inter(int sig)
{
	(void)sig;

	g_signalnum = 1;
	ft_putstr_fd("^C", 2);
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
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
 * @param sigaction Structure describing the action to be taken when 
 * a signal arrives.
 * It consists of:
 * @param __sighandler_t sa_handler;	write();

 * @param __sigset_t sa_mask - the signal blocking functions use 
 * a data structure (an array of integers) called a signal set 
 * to specify what signals are affected.
 * @param sa_flags - it is int
 */
int	ft_handle_signals(bool heredoc)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	if (heredoc == false)
		action.sa_handler = &handle_sigint_inter;
	else
		action.sa_handler = &handle_sigint_non;
	action.sa_flags = 0;
	if (sigemptyset(&action.sa_mask) == -1)
	{
		perror("sigemtyset\n");
		return (1);
	}
	sigaddset(&action.sa_mask, SIGINT);
	sigaddset(&action.sa_mask, SIGQUIT);
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
	return (0);
}

void	sig_handle_child(int sig_num)
{
	(void)sig_num;
}

/// @brief  TO REWRITE IT!!!!!
/// @param  
void	ft_handle_signals_childs(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &sig_handle_child;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("sigaction");
	signal(SIGQUIT, SIG_DFL);
}
