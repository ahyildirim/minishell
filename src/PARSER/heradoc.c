#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	exit(SIGNAL_C);
}

static void	set_heradoc_values(t_cmdlist *cmd_table, int *fd, t_data *data)
{
	char	buf[1];

	if(cmd_table->heradoc_values) //Eğer önceden kalan bir heradoc değeri var ise free'le ve NULL at
	{
		free(cmd_table->heradoc_values);
		cmd_table->heradoc_values = NULL;
	}
	while(read(fd[0], buf, 1)) //pipe'ın okuma ucundan birer birer oku ve buf içine at.
		str_append_char(&cmd_table->heradoc_values, *buf); //heradoc değerine teker teker buf'ın içindeki değerleri at.
	close(fd[0]);
	str_append_char(&data->input, '\n'); //newline at
	ft_strjoin(&data->input, cmd_table->heradoc_values); //asıl inputun içine heradoc değerlerini birleştir.
}

static char	*get_heradoc_values(char *eof)
{
	char	*line;
	char	*new_line; 
	int		*is_started;

	line = NULL;
	is_started = 0; //Yazılan ilk değer olup olmadığının kontrol flagi
	signal(SIGINT, handle_sigint);
	while(1)
	{
		new_line = readline("> "); //readline ile bir sonraki değer'i al
		if(ft_strcmp(eof, new_line)) //eğer eof stringi geldiyse yani "CAT << EOF"'daki EOF stringi geldi ise free'leyip döngüden çık.
		{
			free(new_line);
			break;
		}
		else if(is_started++) //İlk satırda line içine '\n' olmayacağı için ilk döngüde ekleme ki ilk komut '\n' olmasın, bir sonraki döngülerde eklemeye başla.
			str_append_char(&line, '\n');
		ft_strjoin(&line, new_line); //orijinal line ile readline'dan alınan new_line değerlerini birleştir.
		if(new_line) //new_line içini boşalt ki memory leak olmasın, sonraki döngüde temiz bir şekilde readline ile bir daha oku.
			free(new_line);
	}
	str_append_char(&line, '\n'); //En sonda line sonuna bir '\n' daha ekle.
	return (line);
}

static void	fill_heradoc(char *eof, int *fd, t_data *data)
{
	char	*lines;

	close(fd[0]); //Okuma ucu ile bir işimiz olmadığı için fd[0]'ı kapatıyoruz.
	lines = get_heradoc_values(eof); //Bu fonksiyon ile heradoc içindeki değerleri alıyoruz
	write(fd[1], lines, ft_strlen(lines)); //Heradoc içindeki değerleri pipe'ın yazma ucuna yani fd[1]'e yazdır.
	close(fd[1]); //BU fonksiyonda fd[1] ile işimiz kalmadığı için kapat.
	free(lines);
	free_loop(data);
	free_utils(data);
	exit(EXIT_SUCCESS);
}

static int	read_heradoc_value(t_cmdlist *cmd_table, char *eof, t_data *data)
{
	int	pid;
	int	fd[2];
	int	ret;

	pipe(fd); //getarg.c dosyasında olduğu gibi parent ve child process arasında iletişim kurmak için yazma ve okuma uçlu bir boru açıyoruz.
	pid = fork(); //Girilen değerleri almak için bir childp process oluşturuyoruz.
	data->is_reading = 1; //Okuyor flag'ini 1 yapyıoruz.
	if(pid == 0)
		fill_heradoc(eof, fd, data); //Child process içinde heradoc'un içeriğini dolduruyoruz
	close(fd[1]); //yazma ile işimiz olmadığı için fd[1]'i kapat.
	waitpid(pid, &ret, 0); //child process'in işinin bitmesini bekle ve fonksiyondan çıkan sinyali ret'in içine at.
	data->is_reading = 0; //Okuma flag'ini 0 la;
	ret = WEXITSTATUS(ret); //Çıkış sinyalinin ne olduğunu tanımla.
	if(ret == SIGNAL_C) //Signal C yakalandı ise çıkış yap.
	{
		close(fd[0]);
		//update_history(data->input); //TODO
		free_loop(data);
		return (0);
	}
	set_heradoc_values(cmd_table, fd, data); //Yazılan değerleri okuyup inputa aktar.
	return (1);
}

void	start_heradoc(t_cmdlist *cmd_table, t_data *data)
{
	t_filelist	*tmp;

	if(!cmd_table)
		return;
	while(cmd_table) //tüm cmd node'ların içinde gezerek herhangi birinde "<<" var mı diye bakıyoruz. Çünkü heradoc [COMMAND] << EOF şeklinde çalışıyor.
	{
		tmp = cmd_table->files;
		if(!tmp)
			return;
		while(tmp)
		{
			if(tmp->meta_char[1] == DOUBLE_LESS[1]) //Eğer "<<" var ise heradoc değerlerini okumaya başlıyoruz.
			{
				if(!read_heradoc_value(cmd_table, tmp->file_name, data))
					return ;
				tmp->fd = HERADOC;
			}
			tmp = tmp->next;
		}
		cmd_table = cmd_table->next;
	}
}
