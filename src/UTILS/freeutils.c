/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:57 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:58 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_cpy(char **envlist)
{
	char	**temp_envlist;

	temp_envlist = envlist;
	while (*temp_envlist)
		free(*(temp_envlist++));
	free(envlist);
}

void	free_envtable(t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->env_table;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->env_name)
			free(tmp->env_name);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	free_metachars(t_data *data)
{
	char	**tmp;

	tmp = data->metachars;
	if (!tmp)
		return ;
	while (tmp && *tmp)
		free(*(tmp++));
	free(data->metachars);
}

void	free_core(t_data *data)
{
	free_metachars(data);
	free_envtable(data);
	rl_clear_history();
}

void	free_utils(t_data *data)
{
	free_metachars(data);
	free_envtable(data);
	rl_clear_history();
}
