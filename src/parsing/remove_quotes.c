/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:49:09 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:22:06 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *string)
{
	size_t	i;
	char	*result;
	char	*tmp;

	tmp = NULL;
	result = NULL;
	i = 0;
	while (string[i])
	{
		if (string[i] && string[i] == '\'')
			tmp = rm_quotes_handle_single_quoted(string, &i);
		else if (string[i] && string[i] == '"')
			tmp = rm_quotes_handle_double_quoted(string, &i);
		else
			tmp = rm_quotes_handle_unquoted(string, &i);
		if (tmp)
		{
			result = ft_append(result, tmp);
			free(tmp);
		}
	}
	return (result);
}

char	**remove_quotes_token(char **tokens)
{
	int		i;
	char	*string;

	string = NULL;
	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		string = remove_quotes(tokens[i]);
		if (string)
		{
			free(tokens[i]);
			tokens[i] = string;
		}
		i++;
	}
	return (tokens);
}

static void	rm_quotes_args(t_command *cur_cmd)
{
	if (cur_cmd->args)
	{
		cur_cmd->args = remove_quotes_token(cur_cmd->args);
		set_command_type(cur_cmd);
	}
}

static void	rm_quotes_file(t_redirect *cur_redir)
{
	char	*tmp;

	tmp = NULL;
	if (cur_redir->file)
	{
		tmp = remove_quotes(cur_redir->file);
		if (tmp)
		{
			free(cur_redir->file);
			cur_redir->file = tmp;
		}
	}
}

void	rm_quotes_command(t_command *command)
{
	t_command	*cur_cmd;
	t_redirect	*cur_redir;

	cur_cmd = command;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirects;
		rm_quotes_args(cur_cmd);
		while (cur_redir)
		{
			rm_quotes_file(cur_redir);
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
}
