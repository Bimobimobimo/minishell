/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:32:40 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:46:35 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft.h"

extern volatile sig_atomic_t	g_global_signal;

typedef enum e_cmd_type
{
	SIMPLE_CMD,
	BUILTIN_CMD,
	ERROR,
}	t_cmd_type;

typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HERE_DOC,
	PIPE,
	WORD,
}	t_redir_type;

typedef struct s_redirect
{
	char					*file;
	char					*heredoc_temp;
	enum e_redirect_type	type;
	int						has_quotes_limiter;
	struct s_redirect		*next;
}	t_redirect;

typedef struct s_command
{
	char				**args;
	enum e_cmd_type		type;
	t_redirect			*redirects;
	struct s_command	*next;
	int					index;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char				*entry;
	char				*expanded_entry;
	t_env				*env;
	t_command			*command;
	char				**tokens;
	char				**env_array;
	char				**hd_temp_files;
	int					hd_temp_count;
	int					heredoc_counter;
	int					infile_fd;
	int					outfile_fd;
	int					exit_status;
	int					last_pid;

}	t_data;

typedef struct s_vars
{
	int		var_start;
	char	*result;
	char	*tmp;
	char	*key;
	char	*value;
	int		start;
	int		exit_status;
}	t_vars;

//struct for find_path.c
typedef struct s_path
{
	char	**paths;
	char	*temp_path;
	char	*full_path;
	int		i;
}	t_path;

typedef struct s_pipes
{
	int	**pipefds;
	int	pipe_count;
}	t_pipes;

// PROTOTYPES
void			minishell(t_data *data);

// Environment
t_env			*init_env(char **envp);
char			*get_env_value(t_env *env, const char *key);
void			set_env_value(t_env **env, const char *key, const char *value);
void			replace_value(t_env *env, const char *value);
void			unset_env_value(t_env **env, const char *key);
char			**env_to_array(t_env *env);
t_env			*create_sorted_copy(t_env *original);

// Environment utils
t_env			*create_env_node(const char *env_str);
void			free_env_node(t_env *node);
void			free_env_list(t_env **list);

// Expansion of environment variables
char			**expand(t_data *data, char **tokens, t_env *env);
char			*expand_token(t_data *data, const char *token, t_env *env);
char			*ft_append(char *dest, char *src);

// Expansion utils
char			*process_unquoted(t_data *data, const char *token, size_t *i,
					t_env *env);
char			*process_double(t_data *data, const char *token, size_t *i,
					t_env *env);
void			process_dollar(const char *tk, t_vars *v, t_env *e, size_t *i);
char			*process_single(const char *token, size_t *i);
int				skip_quotes(const char *token, size_t *i);
char			*dollar_unquoted(t_data *data, const char *token, size_t *i,
					t_env *env);
char			*process_limiter(const char *token, size_t *i);

// Syntax general
bool			syntax(t_data *data, char *entry);
bool			open_quotes(char *line);
bool			not_empty_line(char *entry);

// Syntax chevron & pipe
bool			pipe_error(char *line);
bool			chevron_error(char *line);

// Tokenisation
char			**split_command(t_data *data, const char *input);
void			skip_space(const char **input);
void			append_string(char **token, const char *start, size_t len);
int				check_token_env_value(t_data *data, char *curr_token);
void			store_token(char ***tokens, int *count, char **cur);
void			store_empty_token(char ***tokens, int *count, char **cur);
void			store_check(t_data *data, char ***tokens,
					char **cur_tk, int *count);
void			terminate_tokens(char **tokens, int count);
int				is_separator(char c);
void			handle_string(const char **input, char ***tokens,
					char **cur_token, int *count);

//Remove quotes
char			**remove_quotes_token(char **tokens);
void			rm_quotes_command(t_command *command);
char			*rm_quotes_handle_single_quoted(char *string, size_t *i);
char			*rm_quotes_handle_double_quoted(char *string, size_t *i);
char			*rm_quotes_handle_unquoted(char	*string, size_t *i);

// Utils strings
char			*ft_strndup(const char *s, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
bool			key_syntax(char *key);

// Utils characters
bool			is_space(char c);
bool			is_operator(char c);
bool			is_upper(char c);
bool			is_num(char *str);
bool			is_chevron(char c);

// Utils arrays
void			free_array(char **array);
int				tab_lign_nb(char **tab);
char			**realloc_tokens(char **tokens, int count);
int				env_array_malloc_size(t_env *env);

// input/output redirection
void			setup_redirections(t_data *data, t_command *command,
					t_pipes *pipes);

// Builtins
bool			builtins(t_data *data, t_command *command, t_pipes *pipes);
void			export_variable_error(char *key, t_data *data);
void			unset_variable_error(char *key, t_data *data);
void			malloc_error(t_data *data, t_pipes *pipes);
bool			bi_pwd(t_data *data);
bool			bi_cd(t_data *data, t_command *command);
bool			bi_env(t_data *data);
bool			bi_exit(t_data *data, t_command *command, t_pipes *pipes);
bool			bi_export(t_data *data, t_command *command, t_pipes *pipes);
void			bi_export_variable(t_data *data, t_command *command,
					t_pipes *pipes);
bool			wrong_char(char *key);
bool			bi_unset(t_data *data, t_command *command, t_pipes *pipes);
bool			bi_echo(t_data *data, t_command *command);
int				arg_count(char **tab);

// Linked commands list management
void			free_command_list(t_command **command);
void			free_redirect_list(t_redirect **redirect);
void			free_command_node(t_command *node);
t_command		*new_command(void);
void			add_command(t_command **head, t_command *new_command);
t_redirect		*new_redirect(const char *file, t_redir_type type);
void			add_redirection(t_redirect **head, t_redirect *new_redir);
void			sanitize_command(t_command *command);
void			set_command_type(t_command *command);
void			set_heredoc_quotes(t_command *command);

// Parser start
t_command		*parse_command(char **tokens);
t_redir_type	get_redirect_type(const char *token);
void			sanitize_tokens(char **tokens);

// Parser utils
int				is_redir(char *token);
int				token_count(char **args);
int				is_builtin(char *arg);

// Data struct managment
t_data			*init_data(char **envp);
void			free_memory(t_data *data);
void			free_memory_exit(t_data *data, int exit_status);
void			free_pipes_memory_exit(t_data *data, t_pipes *pipes,
					int exit_status);
void			refresh_data(t_data *data);

// Execution
void			execute_commands(t_data *data);
void			execute_pipeline(t_data *data, t_command *command,
					t_pipes *pipes);
void			exec_command(t_data *data, t_command *command, t_pipes *pipes);
void			setup_child_pipes(t_command *cmd, t_pipes *pipes,
					int cmd_index);
char			*find_path(char *cmd, char **envp, int *exit_status);
void			init_pipes_data(t_data *data, t_pipes *pipes);
void			close_pipes(t_pipes *pipes);
void			free_pipes(t_pipes *pipes);
void			command_error(t_data *data, t_pipes *pipes, char *cmd,
					int exit_status);
void			command_index(t_command *command);
void			wait_children(t_data *data);
void			decrem_close_free_pipes(t_pipes *pipes, int i);
void			execve_error(t_command *command, char *path);

// Execution utils
void			handle_child(t_data *data, t_command *command,
					t_pipes *pipes, int cmd_index);
void			handle_parent(t_command **command, int *cmd_index);
void			specific_slash_case(t_data *data, char *arg);
bool			check_is_directory(char *path);

// Heredoc
void			heredoc_warning(t_data *data, char *limiter);
int				process_heredocs(t_data *data, t_command *command,
					t_pipes *pipes);
void			cleanup_heredoc_temp(t_data *data);
char			*new_tmp_filename(int index);
int				is_last_heredoc(t_redirect *redirect);
void			cleanup_heredoc(char *tmp_file, int fd);
int				process_line(t_data *data, int fd, t_redirect *redir,
					char *line);
int				file_error_heredoc(t_data *data, char *tmp_file, int fd);

// Signals
void			handle_parent_signals(void);
void			handle_heredoc_signals(void);
void			handle_exec_signals(void);
void			sigint_heredoc_handler(int sig);
void			sigint_parent_handler(int sig);

#endif
