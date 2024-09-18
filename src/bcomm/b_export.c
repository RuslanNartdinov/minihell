/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:20:57 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:39:42 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	b_env(t_shell *shell)
{
	t_env	*curr;

	curr = shell->enviro;
	while (curr)
	{
		if (curr->key && curr->value && !curr->hide)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	b_sort(char **arr, int size)
{
	int		swap;
	char	*temp;
	int		i;

	swap = 1;
	while (swap)
	{
		i = 0;
		swap = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swap = 1;
			}
			i++;
		}
	}
}

char	**exp_to_array(t_env *enviro)
{
	int		size;
	char	*temp;
	char	**array;
	t_env	*curr;
	int		i;

	i = 0;
	size = ft_envsize(enviro);
	if (size == 0)
		return (NULL);
	array = malloc((size + 1) * sizeof(char *));
	curr = enviro;
	while (i < size)
	{
		if (curr->key && curr->value && !curr->hide)
		{
			temp = ft_strjoin(curr->key, "=");
			array[i] = ft_strjoin(temp, curr->value);
			free(temp);
			i++;
		}
		curr = curr->next;
	}
	array[size] = NULL;
	return (array);
}

void	print_export(t_shell *shell)
{
	char	**tempenv;
	int		i;

	i = 0;
	tempenv = exp_to_array(shell->enviro);
	b_sort(tempenv, ft_envsize(shell->enviro));
	while (tempenv[i])
	{
		printf("%s\n", tempenv[i++]);
	}
	free_split_from(tempenv, 0);
}

void	b_export(t_shell *shell, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		print_export(shell);
	else
	{
		while (cmd[i])
		{
			if (ft_strrchr(cmd[i], '=') && ft_strlen(cmd[i]) > 1
				&& cmd[i][0] != '=' && is_valid_key(cmd[i]))
				add_to_env(shell, ft_strdup(cmd[i]), 0, 1);
			i++;
		}
	}
}
