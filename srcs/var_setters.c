#include "ft_ls.h"

int				throw(char *s)
{
	write(1, s, ft_strlen(s));
	exit(0);
}

t_file			*new_file(char *s)
{
	t_file		*new;
	struct stat file_stat;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		throw("memory ERROR\n");
	if (data.option[0] == 1)
	{
		stat(s, &file_stat);
		new->f_stat = new_tstat();
		put_stats(new->f_stat, file_stat);
	}
	new->next = NULL;
	new->prev = NULL;
	new->filename = ft_strdup(s);
	return (new);
}

t_stat			*new_tstat(void)
{
	t_stat		*new;

	if (!(new = (t_stat*)malloc(sizeof(t_stat))))
		throw("memory ERROR\n");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			set_data(void)
{
	data.option[0] = 0;
	data.option[1] = 0;
	data.option[2] = 0;
	data.option[3] = 0;
	data.option[4] = 0;
	data.file_count = 0;
	data.dir_count = 0;
	data.alley_mlen[0] = 0;
	data.alley_mlen[1] = 0;
	data.alley_mlen[2] = 0;
	data.files = NULL;
	data.f_stat = NULL;
}
