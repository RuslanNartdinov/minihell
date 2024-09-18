/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:32:18 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:14 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	iter;
	size_t	slen;

	iter = 0;
	slen = 0;
	while (src[slen])
		slen++;
	if (n == 0)
		return (slen);
	while (src[iter] && iter < n - 1)
	{
		dest[iter] = src[iter];
		iter++;
	}
	dest[iter] = '\0';
	return (slen);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	iter;

	iter = 0;
	while (s1[iter] && s2[iter] && s1[iter] == s2[iter])
		iter++;
	return ((unsigned char) s1[iter] - (unsigned char) s2[iter]);
}

int	ft_isalnum(int c)
{
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57));
}

void	set_filename(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->next && (temp->type == 12 || temp->type == 13
				|| temp->type == 14))
		{
			temp->next->type = 16;
		}
		else if (temp->next && temp->type == 15)
		{
			temp->next->type = 17;
		}
		temp = temp->next;
	}
}
