/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:13:25 by mbabayan          #+#    #+#             */
/*   Updated: 2024/08/11 14:05:10 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_flag(char *arg)
{
	int jindex = 2;
	while (arg[jindex] == 'n')
		jindex++;
	if (arg[jindex] != '\0')
		return 0;
	return 1;
}

void print_echo(char **args, int index, int flag)
{
	while (args[index])
	{
		printf("%s", args[index]);
		if (args[index + 1])
			printf(" ");
		index++;
	}
	if (flag == 0)
		printf("\n");
}

int echo(char **args, int index)
{
	int flag;

	flag = 0;
	while (args[index] && args[index][0] == '-' && args[index][1] == 'n')
	{
		if (!check_flag(args[index]))
			break;
		flag = 1;
		index++;
	}
	print_echo(args, index, flag);
	return 0;
}

int main()
{
	char *args1[] = {"echo", "Hello", "World", NULL};
	echo(args1, 1); // Output: Hello World

	char *args2[] = {"echo", "-n", "Hello", "World", NULL};
	echo(args2, 1); // Output: Hello World

	return 0;
}