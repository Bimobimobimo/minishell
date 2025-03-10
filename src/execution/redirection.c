/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:48:36 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/21 21:22:49 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirection(t_data *data, t_redirect *redirect,
	t_pipes *pipes)
{
	data->infile_fd = open(redirect->file, O_RDONLY);
	if (data->infile_fd < 0)
	{
		perror(redirect->file);
		free_pipes_memory_exit(data, pipes, 1);
	}
	dup2(data->infile_fd, STDIN_FILENO);
	close(data->infile_fd);
}

static void	handle_output_redirection(t_data *data, t_redirect *redirect,
	t_pipes *pipes)
{
	data->outfile_fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
	{
		perror(redirect->file);
		free_pipes_memory_exit(data, pipes, 1);
	}
	dup2(data->outfile_fd, STDOUT_FILENO);
	close(data->outfile_fd);
}

static void	handle_append_redirection(t_data *data, t_redirect *redirect,
	t_pipes *pipes)
{
	data->outfile_fd = open(redirect->file, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (data->outfile_fd < 0)
	{
		perror(redirect->file);
		free_pipes_memory_exit(data, pipes, 1);
	}
	dup2(data->outfile_fd, STDOUT_FILENO);
	close(data->outfile_fd);
}

void	setup_redirections(t_data *data, t_command *command, t_pipes *pipes)
{
	t_redirect	*current;

	current = command->redirects;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			data->infile_fd = open(current->heredoc_temp, O_RDONLY);
			if (data->infile_fd < 0)
			{
				perror(current->heredoc_temp);
				free_pipes_memory_exit(data, pipes, EXIT_FAILURE);
			}
			if (is_last_heredoc(current))
				dup2(data->infile_fd, STDIN_FILENO);
			close(data->infile_fd);
		}
		else if (current->type == REDIRECT_IN)
			handle_input_redirection(data, current, pipes);
		else if (current->type == REDIRECT_OUT)
			handle_output_redirection(data, current, pipes);
		else if (current->type == REDIRECT_APPEND)
			handle_append_redirection(data, current, pipes);
		current = current->next;
	}
}
