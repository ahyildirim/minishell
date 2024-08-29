#include "../../includes/minishell.h"

static int complete_arg(t_lexlist *lex_table, t_data *data)
{
	char	*str;

	str = get_arg(data); //pipe'dan sonraki argümanı al.
	if(!str)
		return (1);
	create_lexlist(str, &lex_table, data); //yeni alınan argüman için lexer'ı çalıştır.
	set_lex_types(lex_table, data); //türünü belirle.
	str_append_char(&data->input, ' '); //input'a buradaki str'ı strjoin ile ekleyeceğin için sonuna bir boşluk ekle
	ft_strjoin(&data->input, str); //input ile str'ı birleştir.
	free(str);
	if(ft_strcmp(lex_table->next->content, PIPE)) //eğer content pipe ise çık.
		return (-1);
	return (1);
}

static int	check_pipe_error(t_lexlist *lex_table, t_data *data)
{
	if(lex_table->next && lex_table->next->type == SIGN_PIPE) //pipe'dan sonra bir tane daha pipe karakteri var ise hata ver.
		return (print_lex_error(lex_table));
	else if(!lex_table->next) //pipe'dan sonra eksik bir komut veya argüman var ise tamamlamaya çalış (ls | ca) örneğinde pipedan hemen sonra gelen ca harflerini okur ve parse'lama işlemini baştan yapmaya çalışır.
		return (complete_arg(lex_table, data));
	return (1);
}

static int	check_file(t_lexlist *lex_table)
{
	if(!lex_table->next || (lex_table->next && lex_table->next->type != TEXT)) //Node'un nexti yok ise veya var ise de conteni text değil ise;
	{
		if(lex_table->next) //Nexti var ise (> <<, >> <, etc.)
		{
			print_error("-bash syntax error near unexpected token '", lex_table->next->content, "'\n");
			//TODO
			return (1);
		}
		else //Nexti yok ise (>>, <<, <, etc.)
		{
			print_error("-bash syntax error near unexpected token '", "newline", "'\n");
			//TODO
			return (1);
		}
	}
	return (1);
}

static int	check_errors(t_lexlist *lex_table, t_data *data)
{
	int	pipe_error;

	if(lex_table == data->lex_table && lex_table->type == SIGN_PIPE) //Bu fonksiyona gelen node ilk node'mu kontrolü yap ve yazılan ilk eleman (ilk node) type'ı eğer PIPE(|) ise error ver (| cat).
	{
		print_lex_error(lex_table);
		return (-1);
	}
	else if(lex_table->type != TEXT && lex_table->type != SIGN_PIPE) //Node'un type'ı text değil ise ve pipe değil ise ne olduğunu kontrol et (>, <, >> etc.).
	{
		if(check_file(lex_table))
			return(-1);
	}
	else if(lex_table->type == SIGN_PIPE) //Gelen node'un type'ı pipe ise(ls | cat);
	{
		pipe_error = check_pipe_error(lex_table, data); //pipe için error kontorlü yap.
		if (pipe_error < 0)
			return (0);
		else if (pipe_error == 0)
			return (-1);
	}
	return (1);
}

void	check_syntax(t_data *data)
{
	t_lexlist	*lex_table;
	int			error;

	lex_table = data->lex_table;
	while(lex_table)
	{
		error = check_errors(lex_table, data); //Error kontrolüne ilk başladığımız fonksiyon.
		if (error == -1) //Hata ile karşılaşıldıysa döngüden çık.
			break;
		else if(error == 0) //Hata ile karşılaşılmadıysa bir sonraki iterasyona geç.
			continue;
		if(data->lex_table) //Node varsa bir sonraki node'a geç, yoksa NULL ata.
			lex_table = lex_table->next;
		else
			lex_table = NULL;
	}
}