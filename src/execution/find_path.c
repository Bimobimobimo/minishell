/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:48:32 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 11:09:45 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_three(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*find_path(char *cmd, char **envp, int *exit_status)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	while (*envp && (ft_strncmp("PATH=", *envp, 5)))
		envp++;
	if (!*envp)
		return (*exit_status = -1, NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = join_three(paths[i++], cmd);
		if (full_path)
		{
			if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
				return (free_array(paths), full_path);
			if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0)
				*exit_status = 126;
		}
		free(full_path);
	}
	return (free_array(paths), NULL);
}
