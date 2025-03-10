/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:58:47 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/07 17:19:40 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	return (0);
}

int	token_count(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

int	is_builtin(char *arg)
{
	if (ft_strncmp(arg, "cd", 3) == 0
		|| ft_strncmp(arg, "pwd", 4) == 0
		|| ft_strncmp(arg, "echo", 5) == 0
		|| ft_strncmp(arg, "export", 7) == 0
		|| ft_strncmp(arg, "unset", 6) == 0
		|| ft_strncmp(arg, "env", 4) == 0
		|| ft_strncmp(arg, "exit", 5) == 0)
		return (1);
	return (0);
}

t_redir_type	get_redirect_type(const char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (REDIRECT_IN);
	if (ft_strncmp(token, ">", 2) == 0)
		return (REDIRECT_OUT);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (REDIRECT_APPEND);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (HERE_DOC);
	if (ft_strncmp(token, "|", 2) == 0)
		return (PIPE);
	return (WORD);
}
