#include "ft_ls.h"

static	void	option_parsing(char *s)
{
	while (*s)
	{
		(*s == 'l') ? data.option[0] = 1 : 0;
		(*s == 'R') ? data.option[1] = 1 : 0;
		(*s == 'a') ? data.option[2] = 1 : 0;
		(*s == 'r') ? data.option[3] = 1 : 0;
		(*s == 't') ? data.option[4] = 1 : 0;
		if (ft_strchr(OPT, (int)*s) == NULL)
		{
			write(1, IL_OPT, ft_strlen(IL_OPT));
			write(1, &(*s), 1);
			throw(USAGE);
		}
		s++;
	}
}

void			arg_reader(int argc, char **argv)
{
	int			i;
	t_file		*file;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		option_parsing(argv[i] + 1);
	}
	while (i < argc)
	{
		if (data.file == NULL)
		{
			data.file = new_file(argv[i]);
			file = data.file;
			data.file_count++;
		}
		else
		{
			file->next = new_file(argv[i]);
			file = file->next;
			data.file_count++;
		}
		i++;
	}
}
