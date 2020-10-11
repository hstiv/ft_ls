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

int				throw(char *s)
{
	write(1, s, ft_strlen(s));
	exit(0);
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
	data.arg_file = NULL;
}
