/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:32:06 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:32:03 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/// @brief checks if the type is valid command type
/// @param type 
/// @return 
int	is_valid_type(int type)
{
	if (type == COMMAND || type == FLAG
		|| type == BCOMMAND || type == DQUOTES
		|| type == SQUOTES)
	{
		return (1);
	}
	else if (type == FD_IN || type == FD_OUT
		|| type == APPEND || type == HEREDOC)
	{
		return (2);
	}
	return (0);
}

/// @brief sets the command for the shell to execute 
/// @param command 
/// @param temp 
/// @param shell 
/// @param head 
/// @return 
t_command	*set_command(char **command, t_token *temp,
	t_shell *shell, t_token **head)
{
	t_cmd_data		cmd_data;
	t_shell_bundle	bundle;

	init_cmd_data(&cmd_data);
	bundle.shell = shell;
	bundle.head = head;
	bundle.cmd_data = &cmd_data;
	while (temp && temp->type != PIPE)
	{
		if (!handle_token_type(temp, command, &bundle))
		{
			free_args(command);
			return (NULL);
		}
		temp = temp->next;
	}
	*head = handle_pipe(temp);
	command[cmd_data.i] = NULL;
	return (new_command(command, cmd_data.fd_in,
			cmd_data.fd_out, cmd_data.fd_type));
}

/// @brief handles the token type for the command
/// @param temp 
/// @param command 
/// @param bundle 
/// @return 
int	handle_token_type(t_token *temp, char **command, t_shell_bundle *bundle)
{
	if (is_valid_type(temp->type) == 1)
		handle_command(temp, command, bundle->shell, bundle->cmd_data);
	else if (is_valid_type(temp->type) == 2)
	{
		if (!handle_redirection(temp, command, bundle))
			return (0);
	}
	return (1);
}

/// @brief initializes the command data structure
/// @param cmd_data 
void	init_cmd_data(t_cmd_data *cmd_data)
{
	cmd_data->fd_in = NO_FD;
	cmd_data->fd_out = NO_FD;
	cmd_data->fd_type = NO_FD;
	cmd_data->i = 0;
}

/// @brief takes the token and adds it to the command
/// @param temp 
/// @returns double array of strings
char	**cmd_size_init(t_token *temp)
{
	t_token	*count;
	size_t	c_len;
	char	**command;
	size_t	i;

	i = 0;
	c_len = 0;
	count = temp;
	command = NULL;
	while (count && count->type != PIPE)
	{
		if (count->type == COMMAND || count->type == FLAG
			|| count->type == BCOMMAND || count->type == DQUOTES
			|| count->type == SQUOTES)
		{
			c_len++;
		}
		count = count->next;
	}
	command = (char **)malloc((c_len + 1) * sizeof(char *));
	while (i <= c_len)
	{
		command[i++] = NULL;
	}
	return (command);
}
