/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:00 by euc               #+#    #+#             */
/*   Updated: 2024/10/19 13:54:06 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	com_pwd(t_cmdlist *cmd, t_data *data)
{
	char	pwd[4096];
	char	*path;

	path = getcwd(pwd, 4096);
	if (!path)
		return (perror("minishell: pwd: "));
	ft_putstr_fd(pwd, cmd->output_file);
	ft_putstr_fd("\n", cmd->output_file);
	data->last_output = 0;
}
