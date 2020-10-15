#include "ft_ls.h"

void				swap_files(t_file *p1, t_file *p2)
{
	t_stat			*t_tmp;
	char 			*c_tmp;

	t_tmp = p1->f_stat;
	c_tmp = p1->filename;
	p1->f_stat = p2->f_stat;
	p1->filename = p2->filename;
	p2->f_stat = t_tmp;
	p2->filename = c_tmp;
}

int					throw(char *s)
{
	write(1, "ft_ls: ", 7);
	perror(s);
	exit(EXIT_FAILURE);
}

char 				*rmallocladir(char *s)
{
	int 			i;
	char 			*result;

	i = 0;
	while (s[i + 1] != '\0')
		i++;
	while (s[i] != '/' && i > 0)
		i--;
	if (i > 0)
	{
		result = ft_strncpy(ft_strnew(i), s, i);
		free(s);
		return (result);
	}
	free(s);
	return (NULL);
}

void				del_file(t_file *node)
{
	free(node->f_stat->month);
	free(node->f_stat->day);
	free(node->f_stat->hour);
	free(node->f_stat->min);
	free(node->f_stat);
	free(node->filename);
	free(node);
}

void			set_data(void)
{
	data.option[0] = 0;
	data.option[1] = 0;
	data.option[2] = 0;
	data.option[3] = 0;
	data.option[4] = 0;
	data.arg_files_count = 0;
	data.arg_dir_count = 0;
	data.alley_mlen[0] = 0;
	data.alley_mlen[1] = 0;
	data.alley_mlen[2] = 0;
	data.alley_mlen[3] = 0;
	data.alley_mlen[4] = 0;
	data.print_enter = 0;
	data.arg_file = NULL;
}
