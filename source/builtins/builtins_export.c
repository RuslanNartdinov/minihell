/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:20:57 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:14 by mbabayan         ###   ########.fr       */
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
	int		iter;

	swap = 1;
	while (swap)
	{
		iter = 0;
		swap = 0;
		while (iter < size - 1)
		{
			if (ft_strcmp(arr[iter], arr[iter + 1]) > 0)
			{
				temp = arr[iter];
				arr[iter] = arr[iter + 1];
				arr[iter + 1] = temp;
				swap = 1;
			}
			iter++;
		}
	}
}

char	**exp_to_array(t_env *enviro)
{
	int		size;
	char	*temp;
	char	**array;
	t_env	*curr;
	int		iter;

	iter = 0;
	size = ft_envsize(enviro);
	if (size == 0)
		return (NULL);
	array = malloc((size + 1) * sizeof(char *));
	curr = enviro;
	while (iter < size)
	{
		if (curr->key && curr->value && !curr->hide)
		{
			temp = ft_strjoin(curr->key, "=");
			array[iter] = ft_strjoin(temp, curr->value);
			free(temp);
			iter++;
		}
		curr = curr->next;
	}
	array[size] = NULL;
	return (array);
}

void	print_export(t_shell *shell)
{
	char	**tempenv;
	int		iter;

	iter = 0;
	tempenv = exp_to_array(shell->enviro);
	b_sort(tempenv, ft_envsize(shell->enviro));
	while (tempenv[iter])
	{
		printf("%s\n", tempenv[iter++]);
	}
	free_split_from(tempenv, 0);
}

void	b_export(t_shell *shell, char **cmd)
{
	int	iter;

	iter = 0;
	if (!cmd[1])
		print_export(shell);
	else
	{
		while (cmd[iter])
		{
			if (ft_strrchr(cmd[iter], '=') && ft_strlen(cmd[iter]) > 1
				&& cmd[iter][0] != '=' && is_valid_key(cmd[iter]))
				add_to_env(shell, ft_strdup(cmd[iter]), 0, 1);
			iter++;
		}
	}
}
