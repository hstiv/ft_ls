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

void 			file_reader(char *s)
{
	if (data.files == NULL)
	{
		data.files = new_file(s);
		data.file_count++;
	}
	else
	{
		data.files->next = new_file(s);
		data.files->next->prev = data.files;
		data.files = data.files->next;
		data.file_count++;
	}
}

void 			dir_reader(char *s)
{
	if (data.dirs == NULL)
	{
		data.dirs = new_file(s);
		data.dir_count++;
	}
	else
	{
		data.dirs->next = new_file(s);
		data.dirs->next->prev = data.dirs;
		data.dirs = data.dirs->next;
		data.dir_count++;
	}
}

void			arg_reader(int argc, char **argv)
{
	int			i;
	struct stat	file_stat;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		option_parsing(argv[i] + 1);
	}
	while (i < argc)
	{
		stat(argv[i], &file_stat);
		if (S_ISDIR(file_stat.st_mode))
			dir_reader(argv[i]);
		else
			file_reader(argv[i]);
		i++;
	}
	while (data.dir_count > 0 && data.dirs->prev != NULL)
		data.dirs = data.dirs->prev;
	while (data.file_count > 0 && data.files->prev != NULL)
		data.files = data.files->prev;
}
