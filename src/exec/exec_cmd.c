/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:43:08 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:32:07 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/// @brief initializes the parameters for the child process
/// @param params 
static void	params_init(t_child_params	*params)
{
	params->fd_in = STDIN_FILENO;
	params->fd_out = STDOUT_FILENO;
	params->is_first = 1;
	params->fd[0] = -10;
	params->fd[1] = -10;
	params->saved_stdout = dup(STDIN_FILENO);
}

/// @brief responsible for handling the termination of
///        a child process in a shell environment
/// @param shell 
/// @param params 
static void	child_proc(t_shell *shell, t_child_params	*params)
{
	waitpid(params->pid, &shell->status, 0);
	if (shell->status == 11)
	{
		ft_putstr_fd("Segmentation fault: 11\n", 2);
		shell->status = 139;
	}
	else
		shell->status = WEXITSTATUS(shell->status);
	if (shell->sflag == 2)
		shell->status = 1;
	shell->sflag = 0;
	close(params->saved_stdout);
}

/// @brief executes the command
/// @param cmd 
/// @param shell 
void	exec_cmd(t_command *cmd, t_shell *shell)
{
	t_child_params	params;

	params_init(&params);
	params.pid = 0;
	while (cmd)
	{
		if (cmd->next)
			create_pipe(&params);
		if (!cmd->next && params.is_first && cmd->is_bcommand)
			parent_pid(cmd, &params, shell);
		else
		{
			params.pid = fork();
			if (params.pid == -1)
				return ((perror("fork"), exit(EXIT_FAILURE)));
			if (params.pid == 0)
				start_child(cmd, shell, &params);
			else
				parent_pid(cmd, &params, shell);
		}
		cmd = cmd->next;
	}
	if (params.fd_in != STDIN_FILENO)
		close(params.fd_in);
	child_proc(shell, &params);
}

/// @brief prints the error message if the command is not found
/// @param cmd 
/// @return 
int	exec_printerr(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
