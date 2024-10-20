/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:03 by euc               #+#    #+#             */
/*   Updated: 2024/10/19 13:55:01 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_env(char *name, t_data *data)
{
	t_env	*env;
	t_env	*tmp_env;

	env = data->env_table;
	while (env)
	{
		if (ft_strcmp(env->env_name, name))
		{
			if (env->content)
				free(env->content);
			free(env->env_name);
			if (data->env_table == env)
				data->env_table = data->env_table->next;
			else
				tmp_env->next = env->next;
			free(env);
			break ;
		}
		tmp_env = env;
		env = env->next;
	}
	data->last_output = 0;
}

void	com_unset(t_cmdlist *cmd, t_data *data)
{
	char	**tmp_name;
	int		ar_len;

	ar_len = get_array_len(cmd->path);
	if (ar_len > 1)
	{
		tmp_name = cmd->path;
		while (*(++tmp_name))
		{
			if (!env_arg_control(*tmp_name, data))
			{
				print_error("-bash: unset: `", *tmp_name,
					"': not a valid identifier\n");
				data->last_output = 1;
				continue ;
			}
			else
				delete_env(*tmp_name, data);
		}
	}
}
