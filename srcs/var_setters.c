#include "ft_ls.h"

void			add_stack(t_file *file)
{
	t_stack		*new;
	t_stack		*tmp;

	if (!(new = (t_stack *)malloc(sizeof(t_stack))))
		throw("memory ERROR\n");
	new->file = file;
	tmp = stack;
	new->next = tmp;
	stack = new;
}

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

int				throw(char *s)
{
	write(1, s, ft_strlen(s));
	exit(0);
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
	data.arg_file = NULL;
}
