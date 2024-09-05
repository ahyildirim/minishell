#include "../../includes/minishell.h"

static int	get_env_len(t_data *data)
{
	t_env	*env_list;
	int		count;

	env_list = data->env_table;
	count = 0;
	while (env_list)
	{
		if (env_list->content)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	**get_env_cpy(t_data *data)
{
	int		env_len;
	char	**envlist;
	char	*temp_env;
	t_env	*temp_envlist;

	env_len = get_env_len(data);
	envlist = (char **)malloc(sizeof(char *) * (env_len + 1));
	envlist[env_len] = NULL;
	temp_envlist = data->env_table;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			ft_strjoin(&temp_env, temp_envlist->env_name);
			ft_strjoin(&temp_env, "=");
			ft_strjoin(&temp_env, temp_envlist->content);
			envlist[--env_len] = temp_env;
		}
		temp_envlist = temp_envlist->next;
		
	}
	return (envlist);
	
}

static void	run_execve(t_data *data, int *fd, int fd_index)
{
	char	**envlist;

	data->cmd_table->pid = fork();
	if (!data->cmd_table->pid)
	{
		create_dup(data->cmd_table, data, fd, fd_index);
		envlist = get_env_cpy(data);
		if (execve(data->cmd_table->command, data->cmd_table->path, envlist) == -1)	
		{
			if (data->cmd_table->command)
				print_error(data->cmd_table->command, " command not found\n", NULL);
			free_env_cpy(envlist);
			free_loop(data);
			free_core(data);
			exit(127);
		}
	}
	if (fd && data->cmd_table->pid)
		clear_pipe(fd);
	waitpid(data->cmd_table->pid, &data->last_output, 0);
	data->last_output = WEXITSTATUS(data->last_output);
	
}

char	*get_cmd(char *cmd)
{
	int	cmd_len;

	cmd_len = 0;
	while (*cmd)
	{
		cmd_len++;
		if (*cmd == '/')
			cmd_len = 0;
		cmd++;
	}
	return (cmd - cmd_len);
}

void exec_command(t_data *data, int *fd, int fd_index)
{
	char	*cmd;
	int		builtin_index;

	if (data->cmd_table && !data->cmd_table->command)
		return ;
	cmd = get_cmd(data->cmd_table->command);
	builtin_index = is_builtin(cmd);
	if (builtin_index)
		run_builtin(data, builtin_index);
	else
		run_execve(data, fd, fd_index);
}
