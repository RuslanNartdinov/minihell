/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:29:54 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:14 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*itoa;
	int			len;
	long long	nl;

	nl = n;
	len = ft_numlen(nl);
	itoa = malloc(sizeof(char) * (len + 1));
	if (!(itoa))
		return (NULL);
	itoa[len--] = '\0';
	if (nl == 0)
		itoa[0] = '0';
	else if (nl < 0)
	{
		itoa[0] = '-';
		nl = -nl;
	}
	while (nl > 0)
	{
		itoa[len--] = (nl % 10) + 48;
		nl /= 10;
	}
	return (itoa);
}

int	ft_atoi(const char *str)
{
	int	iter;
	int	s;
	int	r;

	iter = 0;
	r = 0;
	s = 1;
	while (str[iter] == ' ' || (str[iter] >= 9 && str[iter] <= 13))
		iter++;
	if (str[iter] == '-' || str[iter] == '+')
	{
		if (str[iter++] == '-')
			s *= -1;
	}
	while (str[iter] >= '0' && str[iter] <= '9')
	{
		r *= 10;
		r += str[iter++] - '0';
	}
	return (r * s);
}

void	*ft_memset(void *str, int x, size_t n)
{
	size_t			iter;
	unsigned char	*ptr;

	iter = 0;
	ptr = (unsigned char *) str;
	while (iter < n)
		ptr[iter++] = x;
	str = ptr;
	return (str);
}
