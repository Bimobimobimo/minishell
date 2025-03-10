/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:56:38 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:05:24 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->type = SIMPLE_CMD;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **head, t_command *new_command)
{
	t_command	*current;

	if (!head || !new_command)
		return ;
	new_command->next = NULL;
	if (*head == NULL)
		*head = new_command;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_command;
	}
}

void	free_command_list(t_command **command)
{
	t_command	*cur;
	t_command	*previous;

	cur = *command;
	while (cur)
	{
		previous = cur;
		cur = cur->next;
		if (previous)
			free_command_node(previous);
	}
	*command = NULL;
}

void	free_command_node(t_command *node)
{
	if (node->args)
		free_array(node->args);
	if (node->redirects)
		free_redirect_list(&node->redirects);
	if (node)
		free(node);
}

void	command_index(t_command *command)
{
	int			i;
	t_command	*cur;

	cur = command;
	i = 0;
	while (cur)
	{
		cur->index = i;
		cur = cur->next;
		i++;
	}
}
