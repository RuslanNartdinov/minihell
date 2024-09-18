/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_comm_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:49:17 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 17:06:10 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bcomm_exec(t_command *cmd, t_shell *shell, t_params	*params)
{
	if (!ft_strncmp("echo", cmd->command[0], 5))
		b_echo(shell, cmd->command);
	else if (!ft_strncmp("env", cmd->command[0], 4))
		b_env(shell);
	else if (!ft_strncmp("export", cmd->command[0], 7))
		b_export(shell, cmd->command);
	else if (!ft_strncmp("unset", cmd->command[0], 6))
		b_unset(shell, cmd->command);
	else if (!ft_strncmp("cd", cmd->command[0], 3))
		b_cd(shell, cmd->command);
	else if (!ft_strncmp("pwd", cmd->command[0], 4))
		b_pwd();
	else if (!ft_strncmp("exit", cmd->command[0], 5))
		b_exit(shell, cmd, params);
	else if (ft_strrchr(cmd->command[0], '=') && ft_strlen(cmd->command[0]) > 1
		&& cmd->command[0][0] != '=' && is_valid_key(cmd->command[0]))
		b_declare(shell, cmd->command);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->status = 256;
		shell->shell_flag = 1;
	}
}
