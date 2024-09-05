#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (ft_strcmp(cmd, "cd"))
		return (CD);
	else if (ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (ft_strcmp(cmd, "env"))
		return (ENV);
	else if (ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset"))
		return (UNSET);
	return (0);
}

void	run_builtin(t_data *data, int builtin)//TODO
{
	printf("Running builtin command: %d\n", builtin);

	if (data->cmd_table->input_file != -1) 
        dup2(data->cmd_table->input_file, STDIN_FILENO);  // Input yönlendirme
    if (data->cmd_table->output_file != -1)
        dup2(data->cmd_table->output_file, STDOUT_FILENO);
	
	/* if (fd)
		create_dup(data->cmd_table, data, fd, fd_index); */
	if (builtin == ECHO)
		printf("ECHO");
	else if (builtin == CD)
		printf("CD");
	else if (builtin == PWD)
		printf("PWD");
	else if (builtin == EXPORT)
		printf("EXPORT");
	else if (builtin == UNSET)
		printf("UNSET");
	else if (builtin == ENV)
		com_env(data->cmd_table, data);
	else if (builtin == EXIT)
		printf("EXIT");
	
	if (data->cmd_table->input_file != -1)
        close(data->cmd_table->input_file);
    if (data->cmd_table->output_file != -1)
        close(data->cmd_table->output_file);
}
