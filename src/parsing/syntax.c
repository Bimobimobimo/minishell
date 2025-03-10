/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:29:45 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:08:26 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	syntax_error(char *message, char *line, t_data *data)
{
	ft_putendl_fd(message, 2);
	data->exit_status = 2;
	free(line);
	return (false);
}

bool	syntax(t_data *data, char *entry)
{
	char	*line;

	line = ft_strtrim(entry, " \t\n");
	if (!line)
		return (false);
	if (pipe_error(line) == true)
		return (syntax_error("Minishell: pipe syntax error", line, data));
	if (chevron_error(line) == true && pipe_error(line) == false)
		return (syntax_error("Minishell: chevron syntax error", line, data));
	if (open_quotes(line) == true)
		return (syntax_error("Minishell: open quotes error", line, data));
	if (ft_strncmp(entry, ":", 2) == 0 || ft_strncmp(entry, "!", 2) == 0)
	{
		if (ft_strncmp(entry, "!", 2) == 0)
			data->exit_status = 1;
		return (free(line), false);
	}
	free(line);
	return (true);
}

static void	which_quote(bool *sgl, bool *dbl, char *line, int *i)
{
	if (line[*i] == '\'' && *sgl == false && *dbl == false)
		*sgl = true;
	else if (line[*i] == '\'' && *sgl == true && *dbl == false)
		*sgl = false;
	if (line[*i] == '"' && *dbl == false && *sgl == false)
		*dbl = true;
	else if (line[*i] == '"' && *dbl == true && *sgl == false)
		*dbl = false;
}

bool	open_quotes(char *line)
{
	int		i;
	bool	sgl;
	bool	dbl;

	i = 0;
	sgl = false;
	dbl = false;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			which_quote(&sgl, &dbl, line, &i);
		i++;
	}
	if (sgl == true || dbl == true)
		return (true);
	return (false);
}

bool	not_empty_line(char *entry)
{
	int	i;

	i = 0;
	if (!entry)
		return (false);
	while (entry[i])
	{
		if (entry[i] != ' ' && entry[i] != '\t' && entry[i] != '\0')
			return (true);
		i++;
	}
	return (false);
}
