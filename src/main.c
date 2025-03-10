/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:32:24 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:40:44 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_global_signal = 0;

void	minishell(t_data *data)
{
	if (not_empty_line(data->entry) == true)
	{
		add_history(data->entry);
		if (syntax(data, data->entry) == true)
		{
			refresh_data(data);
			data->tokens = split_command(data, data->entry);
			if (data->tokens)
			{
				data->tokens = expand(data, data->tokens, data->env);
				data->env_array = env_to_array(data->env);
				data->command = parse_command(data->tokens);
				set_heredoc_quotes(data->command);
				rm_quotes_command(data->command);
				if (data->command)
					execute_commands(data);
			}
		}
	}
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->command = NULL;
	data->entry = NULL;
	data->expanded_entry = NULL;
	data->env = init_env(envp);
	data->env_array = NULL;
	data->tokens = NULL;
	data->hd_temp_files = NULL;
	data->hd_temp_count = 0;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->exit_status = 0;
	data->last_pid = -1;
	data->heredoc_counter = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_data(envp);
	if (!data)
	{
		printf("Malloc error\n");
		return (-1);
	}
	while (1)
	{
		handle_parent_signals();
		data->entry = readline("Minishell> ");
		if (data->entry == (void *)0)
		{
			printf("exit\n");
			free_memory(data);
			exit(0);
		}
		minishell(data);
		free(data->entry);
	}
	return (0);
}
