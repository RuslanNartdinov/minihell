/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:52:16 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:37:05 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_file(char *filename, int open_type)
{
	int	ret_fd;

	ret_fd = 0;
	if (open_type == 12)
	{
		ret_fd = open(filename, O_RDONLY);
		if (ret_fd == -1)
			perror(filename);
	}
	else if (open_type == 13)
	{
		ret_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret_fd == -1)
			perror(filename);
	}
	else if (open_type == 14)
	{
		ret_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ret_fd == -1)
			perror(filename);
	}
	return (ret_fd);
}
