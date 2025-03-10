/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:31:52 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 11:05:16 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_command_type(t_command *command)
{
	t_command	*cur;

	cur = command;
	while (cur)
	{
		if (cur->args)
		{
			if (is_builtin(command->args[0]))
				cur->type = BUILTIN_CMD;
		}
		cur = cur->next;
	}
}

static int	has_quotes(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (-1);
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	set_heredoc_quotes(t_command *command)
{
	t_command	*cur;
	t_redirect	*cur_redir;

	cur = command;
	while (cur)
	{
		cur_redir = cur->redirects;
		while (cur_redir)
		{
			if (cur_redir->type == HERE_DOC && cur_redir->file)
			{
				if (has_quotes(cur_redir->file) == 1)
					cur_redir->has_quotes_limiter = 1;
			}
			cur_redir = cur_redir->next;
		}
		cur = cur->next;
	}
}
