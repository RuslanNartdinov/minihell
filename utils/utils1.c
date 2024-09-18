/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:36:27 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:50:06 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlen(const char *string)
{
	size_t	iter;

	iter = 0;
	while (string[iter] != '\0')
		iter++;
	return (iter);
}

char	*ft_strdup(const char *string)
{
	char	*dup;
	int		iter;

	iter = 0;
	dup = (char *) malloc(ft_strlen(string) + 1);
	if (!dup)
		return (NULL);
	while (string[iter])
	{
		dup[iter] = string[iter];
		iter++;
	}
	dup[iter] = '\0';
	return (dup);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = 0;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	iter;

	iter = 0;
	if (n == 0)
		return (0);
	while (s1[iter] && s2[iter] && iter < n - 1 && s1[iter] == s2[iter])
		iter++;
	return ((unsigned char) s1[iter] - (unsigned char) s2[iter]);
}

char	*ft_strrchr(const char *string, int c)
{
	int	iter;

	iter = ft_strlen(string);
	while (iter >= 0)
	{
		if (string[iter] == (char)c)
			return ((char *)string + iter);
		iter--;
	}
	return (NULL);
}
