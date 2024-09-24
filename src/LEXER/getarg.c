#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	exit(SIGNAL_C);
}

static int	is_valid_arg(char *str)
{
	char	*tmp;

	if(!str)
		return (0);
	tmp = str;
	trim_left_spaces(&tmp);
	if(!*tmp)
	{
		free(str);
		return (0);
	}
	return (1);
}

static void	read_arg_value(int *fd, t_data *data)
{
	char	*str;

	signal(SIGINT, handle_sigint);
	close(fd[0]); //Sadece yazmayı kullanacağımız için fd[0]'a ihtiyaç yok
	while(1)
	{
		str = readline("> "); //readline ile kullanıcıdan argüman bekle.
		if(!is_valid_arg(str)) //girilen argüman geçerli mi kontrol et, geçerli ise iterasyona devam et.
			continue;
		if (str)
			write(fd[1], str, ft_strlen(str)); //girilen argümanı write ile fd[1]'e yazdır.
		close(fd[1]);
		free(str);
		free_loop(data);
		free_utils(data);
		exit(EXIT_SUCCESS);
	}
}

static int	read_arg(int *fd, t_data *data)
{
	int	pid;
	int	ret;

	pid = fork(); //fork ile bir child process oluştur.
	data->is_reading = 1; //Sanırım ileride gerekli olacak bir kontrol?
	if(pid == 0) //Child process içinde girilen argümanı yazmak için bir fonksiyon kullan.
		read_arg_value(fd, data);
	close(fd[1]);
	waitpid(pid , &ret, 0);  //child processin bitmesini bekle, ret değerine hangi değerle çıktığını al.
	data->is_reading = 0;
	ret = WEXITSTATUS(ret); //WEXITSTATUS ile ret'in hangi exit durumuna denk geldiğini kontrol et.
	if(ret == SIGNAL_C) //Eğer CTRL+C geldiyse fonksiyondan çık.
	{
		close(fd[0]);
		free_loop(data);
		return (0);
	}
	return (1);
}

char	*get_arg(t_data *data)
{
	char	*str;
	int		fd[2];
	char	buf[1];

	if(pipe(fd) == -1) //pipe fonksiyonu ile iki process içinde iletişim kurmak için yazma ve okuma uçlu boru hattı aç, (fd[0]-> okuma, fd[1]-> yazma). Bilmiyorsan Code Vaulttan Pipe in c videosunu izle.
		return (NULL);
	if(!read_arg(fd, data)) //argümanı okumak için bir fonksiyon.
		return (NULL);
	str = NULL;
	while(read(fd[0], buf, 1)) //argümanı oku, buffera at ve buffera her attığın karakteri str'ın sonuna ekle
		str_append_char(&str, *buf);
	close(fd[0]);
	return (str);
}
