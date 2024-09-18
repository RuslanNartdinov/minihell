/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:32:06 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 20:02:24 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief checks if the type is valid command type
/// @param type 
/// @return 
int	is_valid_type(int type)
{
	if (type == 11 || type == 24
		|| type == 23 || type == 19
		|| type == 20)
	{
		return (1);
	}
	else if (type == 12 || type == 13
		|| type == 14 || type == 15)
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
	t_bundle		bundle;

	init_cmd_data(&cmd_data);
	bundle.shell = shell;
	bundle.head = head;
	bundle.cmd_data = &cmd_data;
	while (temp && temp->type != 18)
	{
		if (!handle_token_type(temp, command, &bundle))
		{
			// free_args(command);
			return (NULL);
		}
		temp = temp->next;
	}
	*head = handle_pipe(temp);
	command[cmd_data.iter] = NULL;
	return (new_command(command, cmd_data.fd_in,
			cmd_data.fd_out, cmd_data.fd_type));
}

/// @brief handles the token type for the command
/// @param temp 
/// @param command 
/// @param bundle 
/// @return 
int	handle_token_type(t_token *temp, char **command, t_bundle *bundle)
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
	cmd_data->fd_in = -10;
	cmd_data->fd_out = -10;
	cmd_data->fd_type = -10;
	cmd_data->iter = 0;
}

/// @brief takes the token and adds it to the command
/// @param temp 
/// @returns double array of strings
char	**cmd_size_init(t_token *temp)
{
	t_token	*count;
	size_t	c_len;
	char	**command;
	size_t	iter;

	iter = 0;
	c_len = 0;
	count = temp;
	command = NULL;
	while (count && count->type != 18)
	{
		if (count->type == 11 || count->type == 24
			|| count->type == 23 || count->type == 19
			|| count->type == 20)
		{
			c_len++;
		}
		count = count->next;
	}
	command = (char **)malloc((c_len + 1) * sizeof(char *));
	while (iter <= c_len)
	{
		command[iter++] = NULL;
	}
	return (command);
}
