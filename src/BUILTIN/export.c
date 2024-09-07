#include "../../includes/minishell.h"

static int	change_env(char *envname, t_data *data, char *arg, int is_equal)
{
	t_env	*env;

	env = data->env_table;
	while (env)
	{
		if (ft_strcmp(envname, env->env_name))
		{
			if (is_equal)
				update_env(data, envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	double_export_arg(char *env_cmd, t_data *data)
{
	char	*arg;
	int		is_equal;
	t_env	*env;
	char	*temp_envname;

	if (!env_arg_control(env_cmd, data))
		return ;
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(temp_envname, data, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = data->env_table;
	add_new_envnode(&env, env_cmd);
	if (!is_equal)
		update_env(data, env_cmd, NULL);
	free(temp_envname);
}

static void	single_export_arg(t_cmdlist *cmd, t_data *data)
{
	t_env	*env;

	env = data->env_table;
	while (env)
	{
		write(cmd->output_file, "declare -x ", 11);
		write(cmd->output_file, env->env_name, ft_strlen(env->env_name));
		if (!env->content)
		{
			write(cmd->output_file, "\n", 1);
			env = env->next;
			continue ;
		}
		write(cmd->output_file, "=\"", 2);
		write(cmd->output_file, env->content, ft_strlen(env->content));
		write(cmd->output_file, "\"\n", 2);
		env = env->next;
	}
}

void	com_export(t_cmdlist *cmd_node, t_data *data)
{
	int		array_len;
	char	**temp_path;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
	{
		temp_path = cmd_node->path;
		while (*(++temp_path))
			double_export_arg(*temp_path, data);
	}
	else
		single_export_arg(cmd_node, data);
}
