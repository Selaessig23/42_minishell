/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:39 by mstracke          #+#    #+#             */
/*   Updated: 2026/03/05 16:33:23 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * 
 * in child processes the default behaviour should be implmented
*/

/**
 * @brief This is for heredoc handler
 * different behaviour from main-readline-loop
 * as it should exit the loop in case of CRTL+C
 */ 
static void	handle_sigint_non(int sig)
{
	(void) sig;
	g_signalnum = 1;
	ft_putstr_fd("\n", 1);
}

/**
 * @brief Event hook for readline. Called repeatedly while readline waits.
 * If a signal was received (g_signalnum == 1), forces readline to exit.
 */
static int	check_signal(void)
{
    if (g_signalnum == 1)
    {
        extern int rl_done;
        rl_done = 1; // To finish readline
        return (0);
    }
    return (0);
}

/**
 * @brief Handles SIGINT (CTRL+C) for the main interactive prompt.
 *
 * This signal handler is triggered when the user presses CTRL+C while the
 * shell is waiting for input. It performs the following actions:
 * 1. Sets the global signal flag (g_signalnum = 1) to notify the main loop
 *    that a signal has occurred.
 * 2. Prints visual feedback: "^C" followed by a newline.
 * 3. Updates readline's internal state: clears the current input buffer
 *    using rl_replace_line("", 0) and tells readline to move to a new line
 *    with rl_on_new_line().
 *
 * Note: The actual termination of readline is handled by the rl_event_hook
 * (check_signal function), which monitors g_signalnum and sets rl_done = 1
 * when a signal is detected. This approach avoids conflicts and ensures
 * clean termination of readline across different environments.
 */ 
static void	handle_sigint_inter(int sig)
{
	(void)sig;
	g_signalnum = 1;
	ft_putstr_fd("^C", 2);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

/**
 * @brief Configures signal handlers for SIGINT (CTRL+C) and SIGQUIT (CTRL+\).
 *
 * This function sets up the behavior for signals depending on the shell's
 * current state (interactive prompt vs. heredoc input).
 * - SIGINT (CTRL+C) is handled by either `handle_sigint_inter` for the main
 *   prompt or `handle_sigint_non` for heredoc.
 * - SIGQUIT (CTRL+\) is always ignored in the parent shell.
 *
 * For the interactive mode (is_heredoc == false), this function also sets up
 * the readline event hook (rl_event_hook) to point to check_signal(). This
 * hook is called repeatedly by readline during input and allows for clean
 * termination when g_signalnum is set by the signal handler.
 *
 * @param is_heredoc A boolean flag:
 *                   - `false`: Use the handler for the interactive main prompt
 *                              and set up the readline event hook.
 *                   - `true`: Use the handler for heredoc input.
 * @return Returns 0 on success, 1 on failure.
 */
int	ft_handle_signals(bool is_heredoc)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	if (is_heredoc == false) {
		action.sa_handler = &handle_sigint_inter;
		extern int (*rl_event_hook)(void);
        rl_event_hook = check_signal;
	}
	else // heredoc handler
		action.sa_handler = &handle_sigint_non;
	action.sa_flags = 0;
	if (sigemptyset(&action.sa_mask) == -1)
	{
		perror("sigemtyset\n");
		return (1);
	}
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
	return (0);
}

/**
 * @brief  function to set the behaviour
 * of SIGINT in child processes
 */ 
void	sig_handle_child(int sig_num)
{
	(void)sig_num;
}

/**
 * @brief  function that handles signal behaviour
 * in child processes, here the sigquit (STRG+\) 
 * as to be set to default behaviour
 */ 

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
