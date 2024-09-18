/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:27:49 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:50:25 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief finds the last command in the list
t_command	*cmd_lstlast(t_command *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/// @brief frees the arguments of the command 
/// @param list 
void	free_commands(t_command **list)
{
	t_command	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->fd_in > -1)
			close(temp->fd_in);
		if (temp->fd_out > -1)
			close(temp->fd_out);
		free_args(temp->command);
		free(temp);
	}
	*list = NULL;
}

/// @brief adds a command to the back of the list
void	cmd_add_back(t_command **list, t_command *new)
{
	t_command	*temp;

	if (*list == NULL)
		*list = new;
	else
	{
		temp = cmd_lstlast(*list);
		temp->next = new;
	}
}

/// @brief checks if the command is a built-in command
int	check_bcommand(char *comm)
{
	if (!comm)
		return (0);
	if (!ft_strncmp(comm, "echo", 4))
		return (1);
	else if (!ft_strncmp(comm, "cd", 2))
		return (1);
	else if (!ft_strncmp(comm, "pwd", 3))
		return (1);
	else if (!ft_strncmp(comm, "export", 6))
		return (1);
	else if (!ft_strncmp(comm, "unset", 5))
		return (1);
	else if (!ft_strncmp(comm, "env", 3))
		return (1);
	else if (!ft_strncmp(comm, "exit", 4))
		return (1);
	else if (ft_strrchr(comm, '=') && ft_strlen(comm) > 1
		&& comm[0] != '=' && is_valid_key(comm))
		return (1);
	else
		return (0);
}

/// @brief creates a new command for the list to execute
t_command	*new_command(char **cmd, int fd_in, int fd_out, int fd_type)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
	{
		perror("malloc");
		exit(1);
	}
	new->command = cmd;
	new->next = NULL;
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	new->fd_type = fd_type;
	new->is_bcommand = check_bcommand(cmd[0]);
	return (new);
}
