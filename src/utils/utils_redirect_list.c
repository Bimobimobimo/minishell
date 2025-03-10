/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:56:29 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:05:36 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*new_redirect(const char *file, t_redir_type type)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->heredoc_temp = NULL;
	redir->type = type;
	redir->next = NULL;
	redir->has_quotes_limiter = 0;
	return (redir);
}

void	add_redirection(t_redirect **head, t_redirect *new_redir)
{
	t_redirect	*current;

	if (!head || !new_redir)
		return ;
	new_redir->next = NULL;
	if (*head == NULL)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

void	free_redirect_list(t_redirect **redirect)
{
	t_redirect	*cur;
	t_redirect	*previous;

	cur = *redirect;
	while (cur)
	{
		previous = cur;
		cur = cur->next;
		if (previous)
		{
			if (previous->file)
				free(previous->file);
			if (previous->heredoc_temp)
				free(previous->heredoc_temp);
			free(previous);
		}
	}
	*redirect = NULL;
}
