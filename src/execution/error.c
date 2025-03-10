/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:36 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:45:53 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_error(t_data *data, t_pipes *pipes, char *cmd, int exit_status)
{
	char	*string;

	string = NULL;
	if (exit_status == 127)
		string = ft_strjoin(cmd, ": command not found\n");
	else if (exit_status == 126)
		string = ft_strjoin(cmd, ": Permission denied\n");
	else if (exit_status == -1)
	{
		string = ft_strjoin(cmd, ": no such file or directory\n");
		exit_status = 127;
	}
	if (string)
	{
		ft_putstr_fd(string, 2);
		free(string);
	}
	free_pipes(pipes);
	free_memory_exit(data, exit_status);
}

void	heredoc_warning(t_data *data, char *limiter)
{
	char	*nb_string;

	nb_string = NULL;
	nb_string = ft_itoa(data->heredoc_counter);
	if (!nb_string)
		return ;
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd("here-document at line ", 2);
	ft_putstr_fd(nb_string, 2);
	ft_putstr_fd(" delimited by end-of-file", 2);
	ft_putstr_fd(" (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	if (nb_string)
		free(nb_string);
}

void	execve_error(t_command *command, char *path)
{
	if (path)
		free(path);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command->args[0], 2);
	ft_putendl_fd(": command not found", 2);
}
