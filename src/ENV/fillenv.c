/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:09 by euc               #+#    #+#             */
/*   Updated: 2024/10/05 19:27:10 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*add_new_envnode(t_env **env_table, char *env)
{
	t_env	*last_node;
	char	*content;

	if (!(*env_table))
	{
		*env_table = (t_env *)malloc(sizeof(t_env));
		last_node = *env_table;
	}
	else
	{
		last_node = *env_table;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env));
		last_node = last_node->next;
	}
	last_node->env_name = get_env_name(env);
	content = env + ft_strlen(last_node->env_name);
	if (*content == '=' && *(content + 1))
		last_node->content = ft_strdup(content + 1);
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}

void	fill_envs(t_data *data, char **env)
{
	while (*env && env)
		add_new_envnode(&data->env_table, *(env++));
}
