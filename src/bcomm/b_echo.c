/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:05:00 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:39:52 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it is the function to get the current working directory
/// @param  
/// @return 
char	*get_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, PATH_MAX);
	if (!path)
		return ("");
	else
		return (path);
}

/// @brief it is the function to print the current working directory
void	b_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, PATH_MAX);
	if (!path)
		perror("pwd");
	else
	{
		printf("%s\n", path);
		free(path);
	}
}

/// @brief it is the function to print the arguments
void	process_echo_arg(char **com, t_shell *shell, int *flag, int *not_words)
{
	char	*temp;

	temp = com[shell->i];
	if (!ft_strncmp(temp, "-n", 2) && *not_words == 1)
	{
		shell->j = 1;
		while (temp[shell->j] == 'n')
			shell->j++;
		if (temp[shell->j])
		{
			*not_words = 0;
			printf("%s", temp);
			if (com[shell->i + 1])
				printf(" ");
		}
		else
			*flag = 1;
	}
	else
	{
		*not_words = 0;
		printf("%s", temp);
		if (com[shell->i + 1])
			printf(" ");
	}
}

/// @brief it is the function to print the arguments
void	b_echo(t_shell *shell, char **com)
{
	int	flag;
	int	not_words;

	flag = 0;
	shell->i = 1;
	not_words = 1;
	while (com[shell->i] != NULL)
	{
		process_echo_arg(com, shell, &flag, &not_words);
		shell->i++;
	}
	if (!flag)
		printf("\n");
}

/// @brief it is the function to change the directory to the home directory
void	cd_home_path(char *home, char *cmd, t_shell *shell)
{
	char	*joined;

	joined = NULL;
	if (home)
	{
		joined = ft_strjoin(home, cmd + 1);
	}
	if (joined)
	{
		if (chdir(joined) == -1)
		{
			perror("cd");
			shell->status = 1;
		}
		free(joined);
	}
}
