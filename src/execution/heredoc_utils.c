/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:48:39 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 11:21:42 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_tmp_filename(int index)
{
	char	*index_str;
	char	*filename;

	filename = NULL;
	index_str = ft_itoa(index);
	filename = ft_strjoin("/tmp/minishell_heredoc", index_str);
	free(index_str);
	return (filename);
}

void	cleanup_heredoc(char *tmp_file, int fd)
{
	if (tmp_file)
	{
		if (access(tmp_file, F_OK) == 0)
			unlink(tmp_file);
		free(tmp_file);
	}
	if (fd != -1)
		close(fd);
}

int	file_error_heredoc(t_data *data, char *tmp_file, int fd)
{
	perror(tmp_file);
	cleanup_heredoc_temp(data);
	cleanup_heredoc(tmp_file, fd);
	return (EXIT_FAILURE);
}

void	cleanup_heredoc_temp(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hd_temp_count)
	{
		if (access(data->hd_temp_files[i], F_OK) == 0)
			unlink(data->hd_temp_files[i]);
		if (data->hd_temp_files && data->hd_temp_files[i])
		{
			free(data->hd_temp_files[i]);
			data->hd_temp_files[i] = NULL;
		}
		i++;
	}
	if (data->hd_temp_files)
		free(data->hd_temp_files);
	data->hd_temp_files = NULL;
	data->hd_temp_count = 0;
}

int	is_last_heredoc(t_redirect *redirect)
{
	t_redirect	*current;

	current = redirect;
	while (current)
	{
		if (current->next && current->next->type == HERE_DOC)
			return (0);
		current = current->next;
	}
	return (1);
}
