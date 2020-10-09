#include "ft_ls.h"

int				throw(char *s)
{
	write(1, s, ft_strlen(s));
	exit(0);
}

t_file			*new_file(char *s)
{
	t_file		*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		throw("memory ERROR\n");
	new->next = NULL;
	new->filename = ft_strdup(s);
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
	data.file = NULL;
}
