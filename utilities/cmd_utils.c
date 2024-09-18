/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:00:43 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 19:59:45 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_args(char **args)
{
	int	iter;

	iter = 0;
	while (args[iter] != NULL)
	{
		free(args[iter]);
		iter++;
	}
	free(args);
}

static	char	*ft_get_cmd_path_from_path(char *cmd, char **path)
{
	int		iter;
	char	*cmd_path;

	iter = 0;
	while (path[iter])
	{
		cmd_path = ft_strjoin(path[iter], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		iter++;
	}
	return (ft_strdup(cmd));
}

static	char	**ft_strjoin_arr(char **arr, char *str)
{
	int		iter;
	char	**new_arr;
	char	*temp;

	iter = 0;
	while (arr[iter])
		iter++;
	new_arr = malloc(sizeof(char *) * (iter + 1));
	if (!new_arr)
		return (NULL);
	iter = 0;
	while (arr[iter])
	{
		temp = arr[iter];
		new_arr[iter] = ft_strjoin(arr[iter], str);
		free(temp);
		iter++;
	}
	new_arr[iter] = NULL;
	iter = 0;
	free(arr);
	return (new_arr);
}

char	*ft_get_cmd_path(char *cmd, char **envp)
{
	int		iter;
	char	**path;
	char	*cmd_path;

	iter = 0;
	while (envp[iter])
	{
		if (ft_strncmp(envp[iter], "PATH=", 5) == 0)
		{
			path = ft_split(envp[iter] + 5, ':');
			if (!path)
				return (NULL);
			path = ft_strjoin_arr(path, "/");
			if (!path)
				return (NULL);
			cmd_path = ft_get_cmd_path_from_path(cmd, path);
			free_args(path);
			return (cmd_path);
		}
		iter++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		iter;

	iter = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (*s1)
		joined[iter++] = *s1++;
	while (*s2)
		joined[iter++] = *s2++;
	joined[iter] = '\0';
	return (joined);
}
