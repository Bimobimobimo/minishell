/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:47:41 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 10:53:07 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_parent_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_parent_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_parent_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_global_signal = SIGINT;
	close(0);
	write(1, "\n", 1);
}

void	handle_heredoc_signals(void)
{
	struct sigaction	sa_heredoc;

	g_global_signal = 0;
	sigemptyset(&sa_heredoc.sa_mask);
	sa_heredoc.sa_handler = sigint_heredoc_handler;
	sa_heredoc.sa_flags = 0;
	sigaction(SIGINT, &sa_heredoc, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_exec_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
