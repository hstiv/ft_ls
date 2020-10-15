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

static void 	file_reader(char *s)
{
	if (data.arg_file == NULL)
	{
		data.arg_file = new_file(s);
		data.arg_files_count++;
	}
	else
	{
		data.arg_file->next = new_file(s);
		data.arg_file->next->prev = data.arg_file;
		data.arg_file = data.arg_file->next;
		data.arg_files_count++;
	}
}

void			arg_reader(int argc, char **argv)
{
	int			i;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
		option_parsing(argv[i] + 1);
	while (i < argc)
		file_reader(argv[i++]);
	while (data.arg_files_count > 0 && data.arg_file->prev != NULL)
		data.arg_file = data.arg_file->prev;
}
