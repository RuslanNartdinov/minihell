/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:33:30 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/17 18:33:30 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief it checks if the key is valid
///        by checking if it is alphanumeric or an underscore
/// @param str 
/// @return 
int	is_valid_key(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter] && str[iter] != '=')
	{
		if (ft_isalnum(str[iter]) || str[iter] == '_')
		{
			iter++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

/// @brief it checks for duplicate environment variables
///        and updates the value if found else adds a new one
/// @param shell
/// @param str 
/// @param sethide 
/// @return 
int	check_env_dupes(t_shell *data, char *str, int sethide)
{
	int		flag;
	char	**split;
	t_env	*curr;

	curr = data->enviro;
	flag = 1;
	split = ft_split(str, '=');
	data->temp = split[0];
	while (curr)
	{
		if (curr->key && !ft_strcmp(data->temp, curr->key))
		{
			free(curr->value);
			curr->value = ft_strdup(split[1]);
			if (sethide)
				curr->hide = 0;
			flag = 0;
			break ;
		}
		curr = curr->next;
	}
	if (split)
		free_split_from(split, 0);
	return (flag);
}

/// @brief it adds a token to the environment variables
/// @param data 
void	add_token_to_env(t_shell *data)
{
	if (check_env_dupes(data, data->checker, 0))
		ft_envadd_back(&data->enviro, data->checker, 1);
	if (data->checker)
		free(data->checker);
	data->checker = ft_strdup("");
}

/// @brief it finds the value of the environment variable key
/// @param data 
/// @param key 
/// @return 
char	*get_env_value(t_shell *data, char *key)
{
	t_env	*curr;

	curr = data->enviro;
	if (!key)
		return (NULL);
	while (curr)
	{
		if (curr->key && !ft_strcmp(key, curr->key))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
