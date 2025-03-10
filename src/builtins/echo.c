/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:44:50 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/11 16:27:56 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(char **tab)
{
	int	arg_nb;

	arg_nb = 0;
	while (tab[arg_nb])
		arg_nb++;
	arg_nb -= 1;
	return (arg_nb);
}

static bool	good_n_option(char *opt)
{
	int	i;

	i = 0;
	if (opt[i] != '-')
		return (false);
	i++;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	bi_echo(t_data *data, t_command *command)
{
	int	i;
	int	arg_nb;

	i = 1;
	arg_nb = arg_count(command->args);
	if (arg_nb == 0)
	{
		printf("\n");
		return (true);
	}
	while (i <= arg_nb && good_n_option(command->args[i]) == true)
		i++;
	while (command->args[i])
	{
		printf("%s", command->args[i]);
		if (i != tab_lign_nb(command->args) - 1)
			printf(" ");
		i++;
	}
	if (good_n_option(command->args[1]) == false)
		printf("\n");
	data->exit_status = 0;
	return (true);
}
