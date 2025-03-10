/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:58:06 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:53:23 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_env(t_data *data)
{
	t_env	*cur;

	cur = data->env;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	data->exit_status = 0;
	return (true);
}

static void	exit_cleanup(t_command *command, t_data *data, t_pipes *pipes,
	int code)
{
	if (command->index == 0 && !command->next)
	{
		free_memory(data);
		free_pipes(pipes);
		close_pipes(pipes);
		exit(code);
	}
	else
		data->exit_status = code;
}

static int	get_exit_nb(char *arg)
{
	int	nb;

	nb = ft_atoi(arg);
	if (nb < 0)
		nb = -nb;
	while (nb > 255)
		nb = nb % 256;
	return (nb);
}

bool	bi_exit(t_data *data, t_command *command, t_pipes *pipes)
{
	int	nb;

	if (command->index == 0 && !command->next)
		printf("exit\n");
	if (command->args[1] && !is_num(command->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_cleanup(command, data, pipes, 2);
	}
	else if (arg_count(command->args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_status = 1;
	}
	else if (tab_lign_nb(command->args) == 2 && is_num(command->args[1]))
	{
		nb = get_exit_nb(command->args[1]);
		exit_cleanup(command, data, pipes, nb);
	}
	else if (command->args[1] == NULL)
		exit_cleanup(command, data, pipes, 0);
	return (true);
}
