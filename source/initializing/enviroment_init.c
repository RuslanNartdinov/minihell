/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:32:35 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:32:35 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it initializes the environment variables
/// @param env 
/// @return 
t_env	*ft_envlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_envclear(t_env **env)
{
	t_env	*curr;
	t_env	*temp;

	curr = *env;
	while (curr)
	{
		temp = curr;
		if (curr->key && curr->value)
		{
			free(curr->value);
			free(curr->key);
		}
		curr = curr->next;
		if (temp)
			free(temp);
	}
	*env = NULL;
}

/// @brief it creates a new environment variable node
/// @param word 
/// @param hide 
/// @return 
t_env	*ft_envnew(char *word, int hide)
{
	t_env	*node;
	char	**split;

	node = (t_env *) malloc(sizeof(t_env));
	node->key = NULL;
	node->value = NULL;
	node->hide = hide;
	if (!node)
		return (NULL);
	split = ft_split(word, '=');
	if (split[0] && split[1])
	{
		node->key = ft_strdup(split[0]);
		node->value = ft_strdup(split[1]);
	}
	node->next = NULL;
	free_split_from(split, 0);
	return (node);
}

/// @brief it adds a new environment variable to the end of the list
/// @param env 
/// @param s 
/// @param hide 
void	ft_envadd_back(t_env **env, char *string, int show)
{
	t_env	*temp;

	if (*env == NULL)
		*env = ft_envnew(string, show);
	else
	{
		temp = ft_envlast(*env);
		temp->next = ft_envnew(string, show);
	}
}

/// @brief it returns the size of the environment variables
/// @param env
/// @return 
int	ft_envsize(t_env *env)
{
	t_env	*curr;
	int		iter;

	iter = 0;
	curr = env;
	while (curr)
	{
		if (curr->key && curr->value && !curr->hide)
			iter++;
		curr = curr->next;
	}
	return (iter);
}
