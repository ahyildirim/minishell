#include "../../includes/minishell.h"

static size_t get_quote_len(const char *command)
{
    size_t len = 0;
    char c;

    while (*command)
    {
        if (*command == '\'' || *command == '"')
            break;
        command++;
    }
    if (*command == '\0')
        return len;

    c = *command;
    command++;
    len++;
    while (*command)
    {
        len++;
        if (*command == c)
            break;
        command++;
    }
    if (*command == '\0')
        ft_putstr_fd("Syntax error with quotes.\n", 2);
    return len;
}


static size_t	get_command_len(char *command, t_data *data)
{
	size_t	len;
	size_t	quote_len;
	char	*meta;

	len = 0;
	while(command && *command && *command != 32)
	{
		meta = is_meta_char(command, data);  //Command stringinin içinde meta karakter(", ', >, >>, <, << vb.) karakter var mı yok mu onun kontrolünü sağlayan fonksiyon.
		if(meta)
		{
			if(!len)
				len += ft_strlen(meta);
			break;
		}
		if(*command == *SINGLE_QUOTE || *command == *DOUBLE_QUOTE)
		{
			quote_len = get_quote_len(command); //eğer ' veya " bulunuyor ise bu işaretin aynısına gelene kadar boyutunu ölçüyoruz.
			len += quote_len; //Total boyutumuzu üstteki fonksiyondan bulduğumuz değere ekliyoruz.
			command += quote_len; //Stringi üstteki fonksiyondan bulduğumuz değer kadar ilerletiyoruz.
			continue ;
		}
		len++;
		command++;
	}
	return(len);
}

static void	parse_command(char **command, t_lexlist *last_node, t_data *data)
{
	size_t	len;
	char	*temp;

	len = get_command_len(*command, data); //Command stringinin boyutunu öğrenmemiz için gerekli fonksiyon.
	temp = malloc(len + 1);
	last_node->content = temp; //Contenti burada recursive bir şekilde dolduruyoruz.
	temp[len] = 0;
	while(len--)
		*(temp++) = *((*command)++);
}

void	create_lexlist(char *command, t_lexlist **lex_table, t_data *data)
{
	t_lexlist	*last_node;
	if(!command || !*command) //Commandi pass by reference ile ilerlettiğimiz için command bu fonksiyonda da ilerlemiş oluyor, bu sayede sona ulaştığımızda bu if kontrolü ile çıkabiliyoruz.
		return ;
	trim_left_spaces(&command); //Soldan başlayarak boşlukları silmeye yarayan fonksiyon.
	last_node = add_lex_node(lex_table); //Yeni bir lex node'u eklememizi sağlayan fonksiyon. push_swap'de kullandığımız node ekleme mantığının aynısı.
	parse_command(&command, last_node, data); //Elimizdeki command'in ne olduğunu parselamamızı sağlayan fonksiyon. Pass by reference mantığı ile tüm programdaki command'i ilerletiyoruz, bu sayede fonksiyondan çıkabiliyoruz.
	create_lexlist(command, lex_table, data);
}

void	lexer(t_data *data)
{
	data->lex_table = NULL;
	create_lexlist(data->input, &(data->lex_table), data); //Girilen komutları lex_table'daki contenti doldurmak için tokenleri oluşturan recursive fonksiyon.
	set_lex_types(data->lex_table, data); //Tokenlerin türünü belirlemek için kullanılan bir fonksiyon.
	check_syntax(data); //Syntaxı kontrol et.
}
