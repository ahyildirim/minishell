/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:50 by euc               #+#    #+#             */
/*   Updated: 2024/10/19 13:53:05 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	com_echo(t_cmdlist *cmd, t_data *data)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &cmd->path[1];
	if (*path && ft_strcmp(*path, "-n"))
	{
		is_n = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			ft_putstr_fd(*path, cmd->output_file);
		if (*(++path))
			ft_putstr_fd(" ", cmd->output_file);
	}
	if (!is_n)
		ft_putstr_fd("\n", cmd->output_file);
	data->last_output = 0;
}
