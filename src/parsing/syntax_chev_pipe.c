/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_chev_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:30:42 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/19 15:09:13 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	specific_chevron_error(char *line)
{
	int	i;

	i = 0;
	if (line[ft_strlen(line) - 1] == '<' || line[ft_strlen(line) - 1] == '>')
		return (true);
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '<')
			|| (line[i] == '<' && line[i + 1] == '>'))
			return (true);
		i++;
	}
	return (false);
}

bool	chevron_error(char *line)
{
	int		i;
	bool	open_chev;

	i = 0;
	open_chev = false;
	if (specific_chevron_error(line) == true)
		return (true);
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (open_chev)
				return (true);
			if (line[i + 1] == '<' || line[i + 1] == '>')
				i++;
			open_chev = true;
		}
		else if (!is_space(line[i]))
			open_chev = false;
		i++;
	}
	return (false);
}

bool	pipe_error(char *line)
{
	int		i;
	bool	open_pipe;

	i = 0;
	open_pipe = false;
	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (true);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (open_pipe == true)
				return (true);
			open_pipe = true;
		}
		else if (!is_space(line[i]) && !is_chevron(line[i]))
			open_pipe = false;
		i++;
	}
	if (open_pipe == true)
		return (true);
	return (false);
}
