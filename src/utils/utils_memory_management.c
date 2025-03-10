/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:56:12 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/18 03:54:42 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes_memory_exit(t_data *data, t_pipes *pipes, int exit_status)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close_pipes(pipes);
	free_pipes(pipes);
	free_memory_exit(data, exit_status);
}

void	free_memory(t_data *data)
{
	if (data->entry)
		free(data->entry);
	if (data->env)
		free_env_list(&data->env);
	if (data->tokens)
		free_array(data->tokens);
	if (data->env_array)
		free_array(data->env_array);
	if (data->command)
		free_command_list(&data->command);
	if (data->hd_temp_files)
		free_array(data->hd_temp_files);
	free(data);
	rl_clear_history();
}

void	free_memory_exit(t_data *data, int exit_status)
{
	free_memory(data);
	exit(exit_status);
}

void	refresh_data(t_data *data)
{
	if (data->tokens)
	{
		free_array(data->tokens);
		data->tokens = NULL;
	}
	if (data->command)
	{
		free_command_list(&data->command);
		data->command = NULL;
	}
	if (data->env_array)
	{
		free_array(data->env_array);
		data->env_array = NULL;
	}
	if (data->hd_temp_files)
	{
		free_array(data->hd_temp_files);
		data->hd_temp_files = NULL;
	}
}
