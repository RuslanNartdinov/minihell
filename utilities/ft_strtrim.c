/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:46:25 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:14 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_set_c(char c, char const *sep)
{
	int	iter;

	iter = 0;
	while (sep[iter])
	{
		if (sep[iter] == c)
		{
			return (1);
		}
		iter++;
	}
	return (0);
}

static	int	start_index(char const *s1, char const *set)
{
	int	iter;

	iter = 0;
	while (s1[iter] && is_set_c(s1[iter], set))
		iter++;
	return (iter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*ret;
	size_t	end;

	if (!s1)
		return (NULL);
	s1 += start_index(s1, set);
	if (*s1 == '\0')
	{
		trimmed = (char *)malloc(1);
		if (!trimmed)
			return (NULL);
		*trimmed = 0;
		return (trimmed);
	}
	end = ft_strlen(s1) - 1;
	trimmed = ft_strdup(s1);
	if (!trimmed)
		return (NULL);
	while (end && is_set_c(trimmed[end], set))
		end--;
	trimmed[end + 1] = '\0';
	ret = ft_strdup(trimmed);
	free(trimmed);
	return (ret);
}
