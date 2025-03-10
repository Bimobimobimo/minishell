/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:27:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/21 18:06:27 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pipe_count(t_data *data)
{
	t_command	*command;
	int			pipe_count;

	pipe_count = 0;
	command = data->command;
	while (command)
	{
		pipe_count++;
		command = command->next;
	}
	if (pipe_count != 0)
		pipe_count--;
	return (pipe_count);
}

static void	init_pipes(t_pipes *pipes, t_data *data)
{
	int	i;

	pipes->pipefds = malloc(sizeof(int *) * pipes->pipe_count);
	if (!pipes->pipefds)
	{
		perror("Pipe allocation error");
		free_memory(data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipes->pipe_count)
	{
		pipes->pipefds[i] = malloc(sizeof(int) * 2);
		if (!pipes->pipefds[i] || pipe(pipes->pipefds[i]) == -1)
		{
			if (pipes->pipefds[i])
				free(pipes->pipefds[i]);
			perror("Pipe creation error");
			decrem_close_free_pipes(pipes, i - 1);
			free_memory(data);
			exit(129);
		}
		i++;
	}
}

void	init_pipes_data(t_data *data, t_pipes *pipes)
{
	pipes->pipe_count = set_pipe_count(data);
	pipes->pipefds = NULL;
	if (pipes->pipe_count > 0)
		init_pipes(pipes, data);
}
