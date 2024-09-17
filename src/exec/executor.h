/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:24:18 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:32:21 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../inc/minishell.h"

typedef struct s_child_params
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	int		is_first;
	pid_t	pid;
	int		saved_stdout;
}	t_child_params;

t_command	*cmd_lstlast(t_command *lst);
void		free_commands(t_command **lst);
void		cmd_add_back(t_command **lst, t_command *new);
t_command	*new_command(char **cmd, int fd_in, int fd_out, int fd_type);
void		create_pipe(t_child_params *params);
void		exec_child(t_command *cmd, t_shell *shell, t_child_params *params);
void		start_child(t_command *cmd, t_shell *shell, t_child_params *params);
void		parent_pid(t_command *cmd, t_child_params	*params, t_shell *shell);
void		exec_cmd(t_command *cmd, t_shell *shell);
int			open_file(char *filename, int open_type);
int			heredoc(char *limiter);
void		bcomm_exec(t_command *cmd, t_shell *shell, t_child_params	*params);
char		**cmd_size_init(t_token *temp);
t_command	*set_command(char **command, t_token *temp,
				t_shell *shell, t_token **head);
int			is_valid_type(int type);
void		create_pipe(t_child_params *params);
//builtins
void		b_echo(t_shell *shell, char **com);
void		b_env(t_shell *shell);
void		b_export(t_shell *shell, char **cmd);
void		b_unset(t_shell *shell, char **cmd);
void		b_cd(t_shell *shell, char **cmd);
void		b_pwd(void);
void		b_exit(t_shell *shell, t_command *cmd, t_child_params	*params);
void		b_declare(t_shell *shell, char **cmd);
char		*get_pwd(void);
void		cd_home_path(char *home, char *cmd, t_shell *shell);
//norme stuff
typedef struct s_cmd_data
{
	int	fd_out;
	int	fd_in;
	int	fd_type;
	int	i;
}	t_cmd_data;

typedef struct s_data_bundle
{
	t_shell		*shell;
	t_token		**head;
	t_cmd_data	*cmd_data;
}	t_shell_bundle;

int			handle_redirection(t_token *temp, char **command,
				t_shell_bundle *bundle);
void		handle_command(t_token *temp, char **command, t_shell *shell,
				t_cmd_data *cmd_data);
int			handle_token_type(t_token *temp, char **command,
				t_shell_bundle *bundle);
t_token		*handle_pipe(t_token *temp);
void		init_cmd_data(t_cmd_data *cmd_data);
void		handle_syntax_error(t_shell_bundle *bundle,
				char **command, t_token *temp);
int			validate_fd(int cmd_fd, int i, char **command);
int			exec_printerr(char *cmd);
#endif