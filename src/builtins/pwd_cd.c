/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:32:57 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:11:27 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	data->exit_status = 0;
	return (true);
}

static int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
		return (0);
	}
	return (1);
}

bool	bi_cd(t_data *data, t_command *command)
{
	data->exit_status = 1;
	if (arg_count(command->args) > 1)
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
	else if (!command->args[1])
		data->exit_status = 1;
	else if (ft_strncmp(command->args[1], "-", 2) == 0)
		bi_pwd(data);
	else if (ft_strncmp(command->args[1], "--", 2) == 0)
	{
		data->exit_status = 2;
		ft_putendl_fd("Minishell: cd: --: invalid option", 2);
	}
	else if (!is_directory(command->args[1]))
		return (true);
	else if (chdir(command->args[1]) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
		data->exit_status = 0;
	return (true);
}
