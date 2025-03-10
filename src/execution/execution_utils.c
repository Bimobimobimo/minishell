/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:41:15 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/21 18:08:33 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child(t_data *data, t_command *command,
	t_pipes *pipes, int cmd_index)
{
	handle_exec_signals();
	setup_redirections(data, command, pipes);
	setup_child_pipes(command, pipes, cmd_index);
	if (command->args)
		exec_command(data, command, pipes);
	free_pipes_memory_exit(data, pipes, 0);
}

void	handle_parent(t_command **command, int *cmd_index)
{
	*command = (*command)->next;
	(*cmd_index)++;
}

bool	check_is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

static void	slash_case_helper(t_data *data, char *arg, char *str,
	int exit_status)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(str, 2);
	free_memory_exit(data, exit_status);
}

void	specific_slash_case(t_data *data, char *arg)
{
	if (ft_strncmp(arg, "/", 1) == 0)
	{
		if (check_is_directory(arg) == true)
			slash_case_helper(data, arg, ": Is a directory", 126);
		else
			slash_case_helper(data, arg, ": No such file or directory", 127);
	}
	if (ft_strncmp(arg, "./", 2) == 0)
	{
		if (check_is_directory(arg) == true)
			slash_case_helper(data, arg, ": Is a directory", 126);
		else if (access(arg + 2, F_OK) == 0
			&& access(arg + 2, X_OK) != 0)
			slash_case_helper(data, arg, ": Permission denied", 126);
		else if (access(arg + 2, F_OK) != 0)
			slash_case_helper(data, arg, ": No such file or directory", 127);
	}
}
