/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:33:01 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:01 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it frees the split array from the given index
void	free_split_from(char **split, int from)
{
	while (split[from])
	{
		free(split[from]);
		from++;
	}
	free(split);
}

/// @brief it initializes the environment variables
void	pre_init(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->enviro = NULL;
	shell->tokens = NULL;
	shell->shell_flag = 0;
	shell->iter = 0;
	env_init(shell);
	add_to_env(shell, ft_strdup("?=0"), 1, 0);
	incr_shlvl(shell);
	set_pwd(shell);
}

/// @brief it initializes the shell, 
///			it sets the checker, tokens, type_flag, status and env_str
void	data_init(t_shell *shell)
{
	shell->iter = 0;
	shell->checker = ft_strdup("");
	shell->tokens = NULL;
	shell->type_flag = 0;
	shell->status = 0;
	shell->env_str = env_to_array(shell->enviro);
}

int	ft_envfullsize(t_env *enviro)
{
	t_env	*curr;
	int		iter;

	iter = 0;
	curr = enviro;
	while (curr)
	{
		if (curr->key && curr->value)
			iter++;
		curr = curr->next;
	}
	return (iter);
}

char	**env_to_array(t_env *enviro)
{
	int		size;
	char	*temp;
	char	**array;
	t_env	*curr;
	int		iter;

	iter = 0;
	size = ft_envfullsize(enviro);
	if (size == 0)
		return (NULL);
	array = malloc((size + 1) * sizeof(char *));
	curr = enviro;
	while (iter < size)
	{
		if (curr->key && curr->value)
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
