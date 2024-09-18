/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:29:53 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:34:11 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief it checks if the token is a file descriptor
/// @param temp 
static void	check_fd_type(t_token *temp)
{
	if (temp->type)
		return ;
	if (temp->next && !ft_strncmp(temp->content, "<", 1)
		&& ft_strlen(temp->content) == 1)
		temp->type = 12;
	else if (temp->next && !ft_strncmp(temp->content, ">", 1)
		&& ft_strlen(temp->content) == 1)
		temp->type = 13;
	else if (!ft_strncmp(temp->content, ">>", 2))
		temp->type = 14;
	else if (!ft_strncmp(temp->content, "<<", 2))
		temp->type = 15;
}

/// @brief it checks if the token is a command
static int	check_if_command(t_shell *shell, t_token *curr)
{
	t_token	*temp;
	int		command_flag;

	if (curr->type)
		return (2);
	command_flag = 0;
	temp = shell->tokens;
	while (temp && temp != curr)
	{
		if (temp->type == 11 || temp->type == 23
			|| temp->type == 16 || temp->type == 17)
			command_flag = 1;
		else if (temp->type == 18)
			command_flag = 0;
		else if (temp->type == 12 || temp->type == 13
			|| temp->type == 14)
			command_flag = 3;
		else if (temp->type == 15)
			command_flag = 4;
		temp = temp->next;
	}
	return (command_flag);
}

/// @brief checks for built-in commands
/// @param temp 
void	check_if_bcommand(t_token *temp)
{
	if (temp->type)
		return ;
	if (!ft_strncmp(temp->content, "echo", 4))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "cd", 2))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "pwd", 3))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "export", 6))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "unset", 5))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "env", 3))
		temp->type = 23;
	else if (!ft_strncmp(temp->content, "exit", 4))
		temp->type = 23;
	else if (ft_strrchr(temp->content, '=') && ft_strlen(temp->content) > 1
		&& temp->content[0] != '=' && is_valid_key(temp->content))
		temp->type = 23;
}

/// @brief it sets the type of the tokens
/// @param temp 
/// @param shell 
static void	token_type(t_token *temp, t_shell *shell)
{
	if (!ft_strncmp(temp->content, "|", 1) && ft_strlen(temp->content) == 1)
		temp->type = 18;
	else if (check_if_command(shell, temp) == 1)
		temp->type = 24;
	else if (check_if_command(shell, temp) == 0)
		temp->type = 11;
	else if (check_if_command(shell, temp) == 3)
		temp->type = 16;
	else if (check_if_command(shell, temp) == 4)
		temp->type = 17;
}

/// @brief it loops through the tokens and sets the filename
/// @param shell 
void	set_type(t_shell *shell)
{
	t_token	*temp;

	if (!shell || !shell->tokens)
		return ;
	temp = shell->tokens;
	while (temp)
	{
		if (temp->type == 21)
			temp->type = 0;
		if (!temp->type)
		{
			check_fd_type(temp);
			check_if_bcommand(temp);
			token_type(temp, shell);
		}
		temp = temp->next;
	}
	set_filename(shell->tokens);
}
