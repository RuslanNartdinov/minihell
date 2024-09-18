/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:25:03 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 17:57:03 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_exit_code;

/// @brief function is responsible for creating a pipe and storing
///        its file descriptors in the params structure
void	create_pipe(t_params *params)
{
	if (pipe(params->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

/// @brief The SHLVL environment variable is used to track
///        the number of nested shell invocations
/// @param limiter 
/// @returns the file descriptor 
int	heredoc(char *limiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		if (!line || (ft_strlen(line) == ft_strlen(limiter)
				&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}

/// @brief it continues the execution of the next command
/// @param command 
/// @param head 
/// @param curr 
/// @returns the next token that is not a pipe
static t_token	*next_cmd(t_command	*command, t_command	**head, t_token *curr)
{
	t_token		*temp;

	temp = curr;
	if (command)
		cmd_add_back(head, command);
	else
		while (temp && temp->type != 18)
			temp = temp->next;
	return (temp);
}

/// @brief it executes the command and sets the exit status
/// @param shell 
void	exec_line(t_shell *shell)
{
	t_command	*command;
	t_command	*head;
	t_token		*temp;
	char		**cmd;

	temp = shell->tokens;
	head = NULL;
	cmd = NULL;
	command = NULL;
	while (temp)
	{
		cmd = cmd_size_init(temp);
		command = set_command(cmd, temp, shell, &temp);
		temp = next_cmd(command, &head, temp);
	}
	if (head && *cmd != NULL && command)
		exec_cmd(head, shell);
	g_exit_code = 0;
	set_exitstatus(shell);
	free_commands(&head);
}

/// @brief it handles the pipe token
/// @param temp 
/// @returns the next token that is not a pipe
t_token	*handle_pipe(t_token *temp)
{
	if (temp && temp->type == 18)
		temp = temp->next;
	return (temp);
}
