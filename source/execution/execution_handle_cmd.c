/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handle_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:30:08 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:38:15 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_command(t_token *temp, char **command,
	t_shell *shell, t_cmd_data *cmd_data)
{
	if (cmd_data->iter == 0 && temp->type != 23)
	{
		command[cmd_data->iter] = ft_get_cmd_path(temp->content,
				shell->env_str);
		if (!command[cmd_data->iter])
			command[cmd_data->iter] = ft_strdup(temp->content);
	}
	else if (cmd_data->iter == 0 && (!command[cmd_data->iter]
			|| temp->type == 23))
		command[cmd_data->iter] = ft_strdup(temp->content);
	else
		command[cmd_data->iter] = ft_strdup(temp->content);
	cmd_data->iter++;
}

void	read_in_out(t_token *temp, t_bundle *bundle)
{
	if (temp->type == 13 || temp->type == 14)
	{
		if (bundle->cmd_data->fd_out > -1)
			close(bundle->cmd_data->fd_out);
		bundle->cmd_data->fd_out = open_file(temp->next->content, temp->type);
		if (bundle->cmd_data->fd_out == -1)
		{
			bundle->shell->status = 1;
			set_exitstatus(bundle->shell);
		}
		*(bundle->head) = temp;
	}
	else if (temp->type == 12)
	{
		if (bundle->cmd_data->fd_in > -1)
			close(bundle->cmd_data->fd_in);
		bundle->cmd_data->fd_in = open_file(temp->next->content, temp->type);
		if (bundle->cmd_data->fd_in == -1)
		{
			bundle->shell->status = 1;
			set_exitstatus(bundle->shell);
		}
		*(bundle->head) = temp;
	}
}

int	handle_redirection(t_token *temp, char **command, t_bundle *bundle)
{
	if (temp->next && temp->type != 15)
	{
		read_in_out(temp, bundle);
		if (temp->type == 12 && !validate_fd(bundle->cmd_data->fd_in,
				bundle->cmd_data->iter, command))
			return (0);
		else if (temp->type == 13 && !validate_fd(bundle->cmd_data->fd_out,
				bundle->cmd_data->iter, command))
			return (0);
	}
	else if (temp->next && temp->type == 15)
	{
		bundle->cmd_data->fd_in = heredoc(temp->next->content);
		temp->type = 12;
	}
	else if (!temp->next)
	{
		handle_syntax_error(bundle, command, temp);
		return (0);
	}
	if (bundle->cmd_data->fd_in > -1 && bundle->cmd_data->fd_out > -1)
		bundle->cmd_data->fd_type = 9;
	else
		bundle->cmd_data->fd_type = temp->type;
	return (1);
}

int	validate_fd(int cmd_fd, int iter, char **command)
{
	if (cmd_fd == -1 && iter > 0)
	{
		command[iter] = NULL;
		free_args(command);
		return (0);
	}
	else if (cmd_fd == -1)
		return (0);
	return (1);
}

void	handle_syntax_error(t_bundle *bundle,
	char **command, t_token *temp)
{
	ft_putstr_fd
		("minishell: syntax error near unexpected token `newline'\n", 2);
	bundle->shell->status = 258;
	if (bundle->cmd_data->iter > 0)
	{
		command[bundle->cmd_data->iter] = NULL;
		free_args(command);
	}
	bundle->head = &temp;
}
