/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:05:43 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/21 18:06:35 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decrem_close_free_pipes(t_pipes *pipes, int i)
{
	while (i >= 0)
	{
		if (pipes->pipefds[i])
		{
			if (pipes->pipefds[i][0] != -1)
				close(pipes->pipefds[i][0]);
			if (pipes->pipefds[i][1] != -1)
				close(pipes->pipefds[i][1]);
			free(pipes->pipefds[i]);
		}
		i--;
	}
	if (pipes->pipefds)
		free(pipes->pipefds);
}

void	decrem_free_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count)
	{
		if (pipes->pipefds[i])
			free(pipes->pipefds[i++]);
	}
	if (pipes->pipefds)
		free(pipes->pipefds);
}

void	close_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count)
	{
		if (pipes->pipefds[i][0] != -1)
			close(pipes->pipefds[i][0]);
		if (pipes->pipefds[i][1] != -1)
			close(pipes->pipefds[i][1]);
		i++;
	}
}

void	free_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count)
	{
		if (pipes->pipefds[i])
			free(pipes->pipefds[i++]);
	}
	if (pipes->pipefds)
		free(pipes->pipefds);
}
