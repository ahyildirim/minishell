#include "../../includes/minishell.h"

void close_unused_file_descriptors() {
    int fd;
    
    // 0 (stdin), 1 (stdout), ve 2 (stderr) dışında tüm dosya tanıtıcılarını kapat
    for (fd = 3; fd < 1024; fd++) {
        close(fd);
    }
}

char **convert_env_table_to_envp(t_env *env_table) {
    t_env *env_data;
    char **env;
    int i;
    int env_count;
    // Çevre değişkenlerinin sayısını hesapla
    env_count = 0;
    env_data = env_table;
    while (env_data) 
	{
        env_count++;
        env_data = env_data->next;
    }
    // Belleği ayır
    env = malloc(sizeof(char *) * (env_count + 1));
    if (!env) 
	{
        perror("malloc");
        return NULL;
    }
    // Çevre değişkenlerini diziye kopyala
    env_data = env_table;
    i = 0;
    while (env_data) 
	{
        env[i++] = env_data->content; // İlgili alanı kullan
        env_data = env_data->next;
    }
    env[i] = NULL; // Dizinin sonunu işaretle

    return env;
}
