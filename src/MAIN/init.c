#include "../../includes/minishell.h"

void	init_metachars(t_data *data)
{
	char	**meta_chars;

	meta_chars = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	data->metachars = meta_chars;
	*(meta_chars++) = ft_strdup(DOUBLE_GREAT);
	*(meta_chars++) = ft_strdup(DOUBLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_GREAT);
	*(meta_chars++) = ft_strdup(PIPE);
	*(meta_chars++) = NULL;
}

void init_data(t_data *data)
{
	// Verilen tüm değerleri başlangıç değerlerine ayarlıyoruz.
	data->input = NULL;
	// malloc ile bellekte alan açıyoruz ve metachars başlangıç değerini atıyoruz (NULL).
	data->is_reading = 0;    // Okuma durumu başlangıçta false (0).
	data->last_output = 0;   // Başlangıçta son çıktı değeri yok.
	data->output = 0;        // Başlangıçta herhangi bir çıktı yok.
	data->main_pid = 0;      // Ana PID başlangıçta 0.
	data->heradoc_fd = -1;   // Heredoc file descriptor başlangıçta -1.
	data->cnt_pipe = 0;      // Pipe sayısı başlangıçta 0.
	data->env_table = NULL;
	data->cmd_table = NULL;
	data->lex_table = NULL;
	init_metachars(data);
}
