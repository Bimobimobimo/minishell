/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:06:13 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/20 15:23:59 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_variable_error(char *key, t_data *data)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit_status = 1;
}

void	unset_variable_error(char *key, t_data *data)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit_status = 1;
}

void	malloc_error(t_data *data, t_pipes *pipes)
{
	ft_putstr_fd("Malloc error", 2);
	free_memory(data);
	free_pipes(pipes);
	close_pipes(pipes);
	exit(1);
}

bool	builtins(t_data *data, t_command *command, t_pipes *pipes)
{
	if (command->args)
	{
		if (ft_strncmp(command->args[0], "cd", 3) == 0)
			return (bi_cd(data, command));
		else if (ft_strncmp(command->args[0], "pwd", 4) == 0)
			return (bi_pwd(data));
		else if (ft_strncmp(command->args[0], "echo", 5) == 0)
			return (bi_echo(data, command));
		else if (ft_strncmp(command->args[0], "export", 7) == 0)
			return (bi_export(data, command, pipes));
		else if (ft_strncmp(command->args[0], "unset", 6) == 0)
			return (bi_unset(data, command, pipes));
		else if (ft_strncmp(command->args[0], "env", 4) == 0)
			return (bi_env(data));
		else if (ft_strncmp(command->args[0], "exit", 5) == 0)
			return (bi_exit(data, command, pipes));
	}
	return (false);
}
