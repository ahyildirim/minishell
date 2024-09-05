#include "../../includes/minishell.h"

void com_env(t_cmdlist *cmd_node, t_data *data)
{
    t_env *tmp_env;

    tmp_env = data->env_table;
    while (tmp_env)
    {
        if (tmp_env->content)
        {
            if (write(cmd_node->output_file, tmp_env->env_name, ft_strlen(tmp_env->env_name)) == -1)
            {
                perror("write env_name");
                exit(EXIT_FAILURE);
            }
            if (write(cmd_node->output_file, "=", 1) == -1)
            {
                perror("write '='");
                exit(EXIT_FAILURE);
            }
            if (write(cmd_node->output_file, tmp_env->content, ft_strlen(tmp_env->content)) == -1)
            {
                perror("write content");
                exit(EXIT_FAILURE);
            }
            if (write(cmd_node->output_file, "\n", 1) == -1)
            {
                perror("write newline");
                exit(EXIT_FAILURE);
            }
        }
        tmp_env = tmp_env->next;
    }
}
