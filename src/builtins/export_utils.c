/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:50:44 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/21 17:45:37 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(t_data *data, char *str, t_pipes *pipes)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (str);
	key = ft_substr(str, 0, i);
	if (!key)
		malloc_error(data, pipes);
	return (key);
}

static char	*get_value(t_data *data, char *str, t_pipes *pipes)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	if (str[i] == '\0')
	{
		value = ft_strdup("");
		if (!value)
			malloc_error(data, pipes);
	}
	else
	{
		value = ft_substr(str, i, (ft_strlen(str) - i + 1));
		if (!value)
			malloc_error(data, pipes);
	}
	return (value);
}

void	bi_export_variable(t_data *data, t_command *command, t_pipes *pipes)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	data->exit_status = 0;
	while (command->args[i])
	{
		key = get_key(data, command->args[i], pipes);
		value = get_value(data, command->args[i], pipes);
		if (key_syntax(command->args[i]) == true)
			set_env_value(&data->env, key, value);
		else
			export_variable_error(command->args[i], data);
		if (value != NULL)
			free(key);
		free(value);
		i++;
	}
}
