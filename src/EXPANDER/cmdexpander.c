/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexpander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:42 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:43 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_content(char **envs, char *arg_name)
{
	char	*ptr;
	char	*temp_envs;
	int		len;

	len = 0;
	temp_envs = *envs;
	while (*temp_envs && *temp_envs != ':')
	{
		len++;
		temp_envs++;
		(*envs)++;
	}
	if (!len)
		return (NULL);
	if (**envs)
		(*envs)++;
	ptr = (char *)malloc(len + 1);
	ptr[len] = '\0';
	while (--len > -1)
		ptr[len] = *(--temp_envs);
	str_append_char(&ptr, '/');
	ft_strjoin(&ptr, arg_name);
	return (ptr);
}

static void	expand_env_content(char **cmd, char *content)
{
	char	*path;

	while (content && *content)
	{
		path = get_env_content(&content, *cmd);
		if (access(path, F_OK) == 0)
		{
			free(*cmd);
			*cmd = path;
			return ;
		}
		free(path);
	}
}

void	cmd_expander(char **cmd, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->env_table;
	while (tmp_env && *cmd && **cmd)
	{
		if (ft_strcmp("PATH", tmp_env->env_name))
		{
			expand_env_content(cmd, tmp_env->content);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}
