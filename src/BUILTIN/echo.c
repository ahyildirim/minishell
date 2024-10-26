/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:50 by euc               #+#    #+#             */
/*   Updated: 2024/10/24 15:13:59 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_util(char **path, int *i, int *j, int *is_n)
{
	while (path[*i] && path[*i][0] == '-' && path[*i][1] == 'n')
	{
		*j = 1;
		while (path[*i][*j] == 'n')
			(*j)++;
		if (path[*i][*j] != '\0')
			break ;
		*is_n = 1;
		(*i)++;
	}
}

void	com_echo(t_cmdlist *cmd, t_data *data)
{
	char	**path;
	int		is_n;
	int		i;
	int		j;

	is_n = 0;
	j = 0;
	path = cmd->path;
	i = 1;
	echo_util(path, &i, &j, &is_n);
	while (path[i])
	{
		if (*path)
			ft_putstr_fd(path[i], cmd->output_file);
		if (path[i + 1])
			ft_putstr_fd(" ", cmd->output_file);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", cmd->output_file);
	data->last_output = 0;
}
