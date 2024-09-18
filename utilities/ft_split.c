/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:27:21 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:14 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_sep_c(char c, char sep)
{
	if (c == sep)
		return (1);
	else
		return (0);
}

static int	count_str(char const *str, char sep)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	while (str[iter] != '\0')
	{
		if (is_sep_c(str[iter], sep) == 0
			&& (is_sep_c(str[iter + 1], sep) == 1 || str[iter + 1] == '\0'))
			count++;
		iter++;
	}
	return (count);
}

static char	*add_word(char const *str, int len)
{
	char	*word;
	int		iter;

	iter = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (iter < len)
	{
		word[iter] = *str++;
		iter++;
	}
	word[iter] = '\0';
	return (word);
}

static void	split_words(char **splitted, int words, char const *s, char c)
{
	int		w;
	int		jter;

	w = 0;
	jter = 0;
	while (w < words)
	{
		jter = 0;
		while (*s && is_sep_c(*s, c) == 1)
			s++;
		while (*s && is_sep_c(*s, c) == 0)
		{
			s++;
			jter++;
		}
		splitted[w++] = add_word(s - jter, jter);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		words;

	if (!s)
		return (NULL);
	words = count_str(s, c);
	splitted = (char **) malloc ((words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	split_words(splitted, words, s, c);
	splitted[words] = NULL;
	return (splitted);
}
