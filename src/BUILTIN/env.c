/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:53 by euc               #+#    #+#             */
/*   Updated: 2024/10/19 13:53:43 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	com_env(t_cmdlist *cmd_node, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->env_table;
	while (tmp_env)
	{
		if (tmp_env->content)
		{
			write(cmd_node->output_file, tmp_env->env_name,
				ft_strlen(tmp_env->env_name));
			write(cmd_node->output_file, "=", 1);
			write(cmd_node->output_file, tmp_env->content,
				ft_strlen(tmp_env->content));
			write(cmd_node->output_file, "\n", 1);
		}
		tmp_env = tmp_env->next;
	}
	data->last_output = 0;
}
