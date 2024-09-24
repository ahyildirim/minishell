#include "../../includes/minishell.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

/* void	ctrl_d(int sig)
{
	(void)sig;// 'sig' parametresi kullanılmıyor, bu yüzden görmezden geliniyor
	rl_on_new_line();// Yeni bir satır başlatır ve imleci satırın başına taşır
	printf("\033[K");// Terminaldeki mevcut satırı temizler (ANSI escape code ile)
	rl_redisplay();// Readline ile satırı yeniden görüntüler
	g_sig = 0;// Global 'g_sig' değişkenini 0 yapar, bu bir durum bayrağı olabilir
} */

void	ctrl_c(int sig)
{
	(void)sig;// 'sig' parametresi kullanılmıyor, bu yüzden görmezden geliniyor
	if (g_sig == 2)// Eğer 'g_sig' 2 ise, özel bir davranış tetiklenir
	{
		/* write(1, "\033[A", 3);// Terminalde bir satır yukarı çıkmak için escape kodu gönderilir
		ioctl(0, TIOCSTI, "\n"); // Terminale yeni bir satır eklemek için 'ioctl' kullanılır */
		printf("\n");
		//exit(SIGNAL_C);
	}
	else// 'g_sig' 2 değilse, normal Ctrl+C davranışı uygulanır
	{
		write(1, "\n", 1);// Terminalde yeni bir satır oluşturur
		rl_on_new_line();// Yeni bir satır başlatır ve imleci satırın başına taşır
		rl_replace_line("", 0);// Mevcut satırı boş bir satır ile değiştirir
		rl_redisplay();// Terminali yeniden görüntüler
	}
	g_sig = 1;// 'g_sig' değişkenini 1 yapar, bu sonraki sinyallerde farklı davranışı tetikleyebilir
}

void	tcseta(void)// Terminal ayarlarını değiştiren fonksiyon
{
	struct termios term1;// 'termios' yapılandırma yapısını tanımlar

	if (tcgetattr(STDIN_FILENO, &term1) != 0)// Terminalin mevcut ayarlarını 'term1' yapısına yükler
		exit((perror("error"), -1));// Eğer başarısız olursa, hata mesajı basar ve programı sonlandırır
	else
	{
		term1.c_cc[VQUIT] = _POSIX_VDISABLE;// VQUIT sinyalini devre dışı bırakır (Ctrl+\ etkisiz hale gelir)
		term1.c_lflag |= ECHOE | ICANON;// ECHOE ve ICANON bayraklarını etkinleştirir
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)// Terminal ayarlarını hemen uygular
			exit((perror("error"), -1));// Eğer başarısız olursa, hata mesajı basar ve programı sonlandırır
		if (tcgetattr(STDIN_FILENO, &term1) != 0)// Yeni ayarları kontrol etmek için terminalin ayarlarını tekrar okur
			exit((perror("error"), -1));// Eğer başarısız olursa, hata mesajı basar ve programı sonlandırır
	}
}

void	handle_signal(void)
{
	tcseta();// Terminal ayarlarını yapılandırmak için 'tcseta' fonksiyonunu çağırır
	signal(SIGINT, ctrl_c);// SIGINT (Ctrl+C) sinyali alındığında 'ctrl_c' işlevini çalıştırır
	signal(SIGQUIT, SIG_IGN);// SIGQUIT (Ctrl+D) sinyali alındığında 'ctrl_d' işlevini çalıştırır
}
