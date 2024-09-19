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

static void init_env(t_env **env_table)
{
	*env_table = NULL;
}

static void init_cmdlist(t_cmdlist **cmd_table)
{
	*cmd_table = NULL;
}

static void init_lexlist(t_lexlist **lex_table)
{
	*lex_table = NULL;
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

	// Listeleri başlatma (NULL) fonksiyonları.
	init_env(&(data->env_table));
	init_cmdlist(&(data->cmd_table));
	init_lexlist(&(data->lex_table));
}
