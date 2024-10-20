/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:46 by euc               #+#    #+#             */
/*   Updated: 2024/10/20 15:43:54 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_pwd_from_export(t_data *data, char *pwd_name,
		char *pwd_content)
{
	t_env	*temp_env;
	char	*temp_pwd;

	if (!update_env(data, pwd_name, pwd_content))
	{
		temp_env = data->env_table;
		temp_pwd = NULL;
		ft_strjoin(&temp_pwd, pwd_name);
		ft_strjoin(&temp_pwd, "=");
		ft_strjoin(&temp_pwd, pwd_content);
		add_new_envnode(&temp_env, temp_pwd);
		free(temp_pwd);
		return (0);
	}
	return (1);
}

static int	change_dir(t_data *data, char *path)
{
	char	pwd[256];
	int		is_pwdaccess;
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(path);
	if (error == -1)
	{
		if (oldpwd)
			free(oldpwd);
		return (0);
	}
	is_pwdaccess = update_pwd_from_export(data, "PWD", getcwd(pwd, 256));
	if (is_pwdaccess)
		update_pwd_from_export(data, "OLDPWD", oldpwd);
	else
		delete_env("OLDPWD", data);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

static void	cd_multiple_arg(t_data *data, t_cmdlist *cmd_node)
{
	if (!change_dir(data, cmd_node->path[1]))
	{
		print_error("--bash: cd: ", cmd_node->path[1],
			": No such file or directory\n");
		data->last_output = 1;
		return ;
	}
	else
		data->last_output = 0;
}

static void	cd_single_arg(t_data *data)
{
	t_env	*temp_env;
	char	*content;

	temp_env = data->env_table;
	while (temp_env)
	{
		if (ft_strcmp("HOME", temp_env->env_name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			data->last_output = 0;
			change_dir(data, content);
			return ;
		}
		temp_env = temp_env->next;
	}
	print_error("-bash: cd: HOME not set\n", NULL, NULL);
	data->last_output |= 1;
}

void	com_cd(t_data *data, t_cmdlist *cmd_node)
{
	int	array_len;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
		cd_multiple_arg(data, cmd_node);
	else
		cd_single_arg(data);
}
