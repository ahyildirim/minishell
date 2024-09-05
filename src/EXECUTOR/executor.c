#include "../../includes/minishell.h"

void execute_command(t_cmdlist *cmd, t_data *data) 
{
	char **envp = convert_env_table_to_envp(data->env_table); // Çevre değişkenlerini al
	char *buildtincmd;
	pid_t pid = fork();

	if (pid == 0) 
	{ // Child process
		if (cmd->input_file != -1) 
			dup2(cmd->input_file, STDIN_FILENO);
		if (cmd->output_file != -1)
			dup2(cmd->output_file, STDOUT_FILENO);
		close_unused_file_descriptors();
		buildtincmd = get_cmd(cmd->command);
		int is_b = is_builtin(buildtincmd);
		if (is_b)
		{
			printf("cmdbuilt : %s\n", cmd->command);
			print_parser(data);
			run_builtin(data, is_b);
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("cmdexec : %s\n", cmd->command);
			print_parser(data);
			if (execve(cmd->command, cmd->path, envp) < 0) 
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		
	}
	else if (pid > 0)// Parent process
		waitpid(pid, NULL, 0); // Çocuk sürecini bekle
	else 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	free(envp);
}

static void	run_multiple(t_data *data)
{
	int fd[2];
	int input_fd = STDIN_FILENO;
	t_cmdlist *cmd_table = data->cmd_table;
	while (cmd_table)
	{
		if (cmd_table->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			cmd_table->output_file = fd[1]; // Pipe'in yazma ucu
		}
		else
			cmd_table->output_file = STDOUT_FILENO; // Son komutun çıkışı, stdout'a yönlendir
		cmd_table->input_file = input_fd; // Mevcut komutun girişi
		execute_command(cmd_table, data);
		if (cmd_table->next)
			close(fd[1]); // Pipe'in yazma ucu, bir sonraki komutun çalışması için kapatılır
		// Pipe'ın okuma ucu, bir sonraki komutun girişi olarak kullanılır
		input_fd = fd[0]; 
		cmd_table = cmd_table->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

static void run_single(t_data *data, int *fd)
{
	if (data->cmd_table->input_file != SSTDERR && data->cmd_table->output_file != SSTDERR)
		exec_command(data, fd, -1);
}

void main_executor(t_data *data)
{
	if (!data->cmd_table)
		return ;
	else if (data->cnt_pipe == 1)
		run_single(data, NULL);//TODO builtin
	else
		run_multiple(data);//TODO
}
