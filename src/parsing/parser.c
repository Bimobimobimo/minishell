/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:18 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:06:21 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(char **tokens, t_command *command, int *i)
{
	t_redir_type	type;

	type = get_redirect_type(tokens[*i]);
	if (tokens[*i + 1] && get_redirect_type(tokens[*i + 1]) == WORD)
	{
		add_redirection(&command->redirects,
			new_redirect(tokens[*i + 1], type));
		(*i)++;
	}
}

void	handle_word(char **tokens, t_command *command, int *i)
{
	command->args = realloc_tokens(command->args, token_count(command->args));
	command->args[token_count(command->args)] = ft_strdup(tokens[*i]);
	command->args[token_count(command->args)] = NULL;
}

t_command	*parse_command(char **tokens)
{
	t_command	*command;
	t_command	*cur_cmd;
	int			i;

	i = 0;
	command = NULL;
	cur_cmd = NULL;
	while (tokens[i])
	{
		if (!cur_cmd)
			cur_cmd = new_command();
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			add_command(&command, cur_cmd);
			cur_cmd = NULL;
		}
		else if (is_redir(tokens[i]))
			handle_redir(tokens, cur_cmd, &i);
		else
			handle_word(tokens, cur_cmd, &i);
		i++;
	}
	if (cur_cmd)
		add_command(&command, cur_cmd);
	return (command);
}
