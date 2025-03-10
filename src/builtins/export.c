/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:45:31 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/18 19:35:38 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bi_export_alone(t_data *data)
{
	t_env	*sorted_copy;
	t_env	*cur;

	sorted_copy = create_sorted_copy(data->env);
	cur = sorted_copy;
	while (cur)
	{
		if (ft_strncmp(cur->key, "_", 2) != 0
			&& ft_strncmp(cur->key, "$?", 3) != 0)
		{
			printf("export %s", cur->key);
			if (cur->value)
				printf("=\"%s\"", cur->value);
			printf("\n");
		}
		cur = cur->next;
	}
	free_env_list(&sorted_copy);
	data->exit_status = 0;
}

bool	bi_export(t_data *data, t_command *command, t_pipes *pipes)
{
	if (command->args[1] == NULL)
		bi_export_alone(data);
	else
		bi_export_variable(data, command, pipes);
	free_array(data->env_array);
	data->env_array = env_to_array(data->env);
	return (true);
}
