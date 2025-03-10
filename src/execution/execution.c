/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:26:34 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/26 15:29:24 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_pipes(t_command *cmd, t_pipes *pipes, int cmd_index)
{
	int			has_input_redir;
	int			has_output_redir;
	t_redirect	*cur;

	signal(SIGQUIT, SIG_DFL);
	has_input_redir = 0;
	has_output_redir = 0;
	cur = cmd->redirects;
	while (cur)
	{
		if (cur->type == REDIRECT_IN || cur->type == HERE_DOC)
			has_input_redir = 1;
		if (cur->type == REDIRECT_OUT || cur->type == REDIRECT_APPEND)
			has_output_redir = 1;
		cur = cur->next;
	}
	if (!has_input_redir && cmd_index > 0)
		dup2(pipes->pipefds[cmd_index - 1][0], STDIN_FILENO);
	if (!has_output_redir && cmd->next)
		dup2(pipes->pipefds[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipes);
}

void	wait_children(t_data *data)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == data->last_pid)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
				else if (WTERMSIG(status) == SIGINT)
					ft_putstr_fd("\n", 2);
				data->exit_status = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
		}
	}
}

void	exec_command(t_data *data, t_command *command, t_pipes *pipes)
{
	char	*path;
	int		exit_status;

	exit_status = 127;
	path = NULL;
	if (builtins(data, command, pipes) == true)
		free_pipes_memory_exit(data, pipes, data->exit_status);
	if (!check_is_directory(command->args[0])
		&& access(command->args[0], F_OK | X_OK) == 0)
		path = ft_strdup(command->args[0]);
	else if (command->args[0][0] == '/'
		|| ft_strncmp(command->args[0], "./", 2) == 0)
		specific_slash_case(data, command->args[0]);
	else
		path = find_path(command->args[0], data->env_array, &exit_status);
	if (!path)
		command_error(data, pipes, command->args[0], exit_status);
	if (execve(path, command->args, data->env_array) == -1)
	{
		execve_error(command, path);
		free_pipes_memory_exit(data, pipes, 127);
	}
}

void	execute_pipeline(t_data *data, t_command *command, t_pipes *pipes)
{
	pid_t		pid;
	int			cmd_index;

	cmd_index = 0;
	while (command)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			perror("fork error");
		else if (pid == 0)
			handle_child(data, command, pipes, cmd_index);
		else
		{
			data->last_pid = pid;
			handle_parent(&command, &cmd_index);
		}
	}
}

void	execute_commands(t_data *data)
{
	t_pipes		pipes;
	t_command	*cmd;

	cmd = data->command;
	init_pipes_data(data, &pipes);
	command_index(data->command);
	signal(SIGINT, SIG_IGN);
	if (process_heredocs(data, cmd, &pipes) != EXIT_SUCCESS)
	{
		if (data->exit_status == 128)
			data->exit_status = 0;
		close_pipes(&pipes);
		free_pipes(&pipes);
		g_global_signal = 0;
		data->hd_temp_count = 0;
		return ;
	}
	if (!cmd->next && cmd->type == BUILTIN_CMD && !cmd->redirects)
		builtins(data, cmd, &pipes);
	else
		execute_pipeline(data, cmd, &pipes);
	close_pipes(&pipes);
	free_pipes(&pipes);
	wait_children(data);
	cleanup_heredoc_temp(data);
}
