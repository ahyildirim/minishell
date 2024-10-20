/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:55 by euc               #+#    #+#             */
/*   Updated: 2024/10/17 16:07:48 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_array_len(char **ar)
{
	int	count;

	count = 0;
	while (ar && *(ar++))
		count++;
	return (count);
}

static int	is_all_num(char *text)
{
	while (text && *text)
	{
		if (!(*text >= '0' && *text <= '9') && !(*text == '-' || *text == '+'))
			return (0);
		text++;
	}
	return (1);
}

void	com_exit(t_cmdlist *cmd, t_data *data)
{
	int	array_len;

	array_len = get_array_len(&cmd->path[1]);
	if (array_len > 1)
	{
		print_error("bash: exit: too many arguments\n", NULL, NULL);
		data->last_output = 1;
		return ;
	}
	else if (array_len == 1)
	{
		if (is_all_num(cmd->path[1]))
			data->last_output = ft_atoi(cmd->path[1]);
		else
		{
			print_error("bash: exit ",
				cmd->path[1], ": numeric argument required\n");
			data->last_output = 255;
		}
	}
	else
		data->last_output = 0;
	free_loop(data);
	free_core(data);
	exit(data->last_output % 256);
}
