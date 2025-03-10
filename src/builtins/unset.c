/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:06:48 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/21 17:46:06 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	syntax_unset(char *arg, t_data *data)
{
	int	i;

	if (key_syntax(arg) == false)
	{
		unset_variable_error(arg, data);
		return (false);
	}
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			unset_variable_error(arg, data);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	bi_unset(t_data *data, t_command *command, t_pipes *pipes)
{
	int		i;
	char	*key;

	i = 1;
	key = NULL;
	data->exit_status = 0;
	if (!command->args[1])
		return (true);
	while (command->args[i])
	{
		if (ft_strncmp(command->args[i], "$?", 3) != 0
			&& syntax_unset(command->args[i], data) == true)
		{
			key = ft_substr(command->args[i], 0, ft_strlen(command->args[i]));
			if (!key)
				malloc_error(data, pipes);
			unset_env_value(&data->env, key);
			free(key);
		}
		i++;
	}
	free_array(data->env_array);
	data->env_array = env_to_array(data->env);
	return (true);
}
