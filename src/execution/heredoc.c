/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 03:48:01 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:47:21 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_fork(t_data *data, t_pipes *pipes, char *tmp_file,
	t_redirect *redir)
{
	char	*line;

	handle_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line && g_global_signal)
		{
			cleanup_heredoc_temp(data);
			free(tmp_file);
			free_pipes_memory_exit(data, pipes, 128 + g_global_signal);
		}
		if (process_line(data, data->infile_fd, redir, line))
			break ;
	}
	free(tmp_file);
	free_pipes_memory_exit(data, pipes, EXIT_SUCCESS);
}

static void	wait_children_heredoc(t_data *data)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}

static int	here_doc(t_data *data, t_redirect *redir, t_pipes *pipes)
{
	char	*tmp_file;
	pid_t	pid;

	data->heredoc_counter++;
	tmp_file = new_tmp_filename(data->hd_temp_count);
	data->infile_fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->infile_fd < 0)
		return (file_error_heredoc(data, tmp_file, data->infile_fd));
	redir->heredoc_temp = ft_strdup(tmp_file);
	data->hd_temp_files = realloc_tokens(data->hd_temp_files,
			data->hd_temp_count);
	data->hd_temp_files[data->hd_temp_count++] = ft_strdup(tmp_file);
	data->hd_temp_files[data->hd_temp_count] = NULL;
	pid = fork();
	if (pid < 0)
		return (file_error_heredoc(data, tmp_file, data->infile_fd));
	if (pid == 0)
		hd_fork(data, pipes, tmp_file, redir);
	close(data->infile_fd);
	free(tmp_file);
	return (EXIT_SUCCESS);
}

int	process_heredocs(t_data *data, t_command *command, t_pipes *pipes)
{
	t_command	*cur_cmd;
	t_redirect	*cur_redir;
	int			status;

	status = 0;
	cur_cmd = command;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirects;
		while (cur_redir)
		{
			if (cur_redir->type == HERE_DOC)
			{
				status = here_doc(data, cur_redir, pipes);
				wait_children_heredoc(data);
				if (status == EXIT_FAILURE)
					data->exit_status = EXIT_FAILURE;
				if (data->exit_status != EXIT_SUCCESS)
					return (data->exit_status);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (EXIT_SUCCESS);
}

int	process_line(t_data *data, int fd, t_redirect *redir, char *line)
{
	char	*expanded;

	if (!line)
	{
		heredoc_warning(data, redir->file);
		return (1);
	}
	if (ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0
		&& ft_strlen(line) == ft_strlen(redir->file))
		return (free(line), 1);
	if (!redir->has_quotes_limiter)
	{
		expanded = expand_token(data, line, data->env);
		free(line);
		line = expanded;
	}
	if (line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}
