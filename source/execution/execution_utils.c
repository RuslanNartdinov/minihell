/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:24:22 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 17:06:10 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>

void	exit_free(t_command *cmd, t_shell *shell, int exit_status)
{
	if (cmd)
		free_commands(&cmd);
	if (shell)
	{
		if (shell->env_str)
			free_args(shell->env_str);
		ft_envclear(&shell->enviro);
	}
	ft_lstclear(shell);
	close_std();
	exit(exit_status);
}

void	exec_child(t_command *cmd, t_shell *shell, t_params *params)
{
	int	exit_status;

	exit_status = 1;
	if (cmd && cmd->command[0] && !cmd->is_bin_command)
	{
		execve(cmd->command[0], cmd->command, shell->env_str);
		if (errno == ENOENT)
			exit_status = exec_printerr(cmd->command[0]);
		else
		{
			perror(cmd->command[0]);
			exit_status = 126;
		}
	}
	else if (cmd->is_bin_command)
	{
		bcomm_exec(cmd, shell, params);
		exit_status = 0;
	}
	if (cmd->fd_out > -1)
		close(cmd->fd_out);
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	close(params->saved_stdout);
	exit_free(cmd, shell, exit_status);
}

void	start_child(t_command *cmd, t_shell *shell, t_params *params)
{
	if (params->is_first && cmd->fd_in > -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		cmd->fd_in = -10;
	}
	else if (!params->is_first)
	{
		if (cmd->fd_in > -1)
			dup2(cmd->fd_in, STDIN_FILENO);
		else
			dup2(params->fd_in, STDIN_FILENO);
	}
	if (cmd->next && cmd->fd_out < 0)
		dup2(params->fd[1], STDOUT_FILENO);
	else if (cmd->fd_out > -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (params->fd[0] > -1)
		close(params->fd[0]);
	if (params->fd[1] > -1)
		close(params->fd[1]);
	exec_child(cmd, shell, params);
}

static void	bcomm_parent(t_command *cmd, t_shell *shell, t_params	*params)
{
	int	saved_stdout;

	if (cmd->fd_out > -1)
		saved_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_out > -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	bcomm_exec(cmd, shell, params);
	if (cmd->fd_out > -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (cmd->fd_out == -1)
		shell->status = 1;
	else if (!shell->shell_flag)
		shell->status = 0;
}

void	parent_pid(t_command *cmd, t_params *params, t_shell *shell)
{
	if (cmd->is_bin_command && !cmd->next && params->is_first)
	{
		bcomm_parent(cmd, shell, params);
		return ;
	}
	if (cmd->next)
	{
		close(params->fd[1]);
		dup2(params->fd[0], STDIN_FILENO);
		close(params->fd[0]);
	}
	else if (!params->is_first)
	{
		dup2(params->saved_stdout, STDIN_FILENO);
		close(params->saved_stdout);
	}
	if (cmd->fd_out > -1)
		close(cmd->fd_out);
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	params->is_first = 0;
}
