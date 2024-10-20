/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:07 by euc               #+#    #+#             */
/*   Updated: 2024/10/20 15:13:46 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*valid_env(char *env, t_data *data)
{
	if (!*env)
		return (NULL);
	if (!((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
			|| *env == '_'))
		return (NULL);
	env++;
	while (*env && *env != ' ' && *env != '=')
	{
		if (!(((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
					|| (*env >= '0' && *env <= '9') || *env == '_')))
			return (NULL);
		if (is_meta_char(env, data))
			return (NULL);
		env++;
	}
	return (env);
}

static char	*env_name_control(char *env, t_data *data)
{
	char	*env_tmp;

	if (!env || *env == ' ' || *env == '=')
		return (NULL);
	env_tmp = env;
	env_tmp = valid_env(env_tmp, data);
	if (!env_tmp || (*env_tmp != '=' && *env_tmp))
		return (NULL);
	if (*env_tmp == '=')
		return (++env_tmp);
	else
		return (env_tmp);
}

int	env_arg_control(char *env, t_data *data)
{
	if (env_name_control(env, data))
		return (1);
	print_error("-bash: export: `", env, "': not a valid identifier\n");
	data->last_output = 1;
	return (0);
}

int	update_env(t_data *data, char *env_name, char *new_arg)
{
	t_env	*env;

	env = data->env_table;
	while (env)
	{
		if (ft_strcmp(env->env_name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			ft_strjoin(&env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
