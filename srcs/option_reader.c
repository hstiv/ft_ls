//
// Created by Hallie Stiv on 10/7/20.
//
#include "ft_ls.h"

void 			set_filename(char *str, t_data *data)
{
	char 		**new_arr;
	char		*s;
	int			i;

	i = 0;
	s = ft_strdup(str);
	new_arr = (char **)malloc(sizeof(char *) * (data->file_count + 1));
	while (i < data->file_count)
	{
		new_arr[i] = data->filenames[i];
		data->filenames[i] = NULL;
		i++;
	}
	data->file_count++;
	new_arr[i] = s;
	free(data->filenames);
	data->filenames = new_arr;
}

static void 	option_parsing(char *s, t_data *data)
{
	while (*s)
	{
		(*s == 'l') ? data->option[0] = 1 : 0;
		(*s == 'R') ? data->option[1] = 1 : 0;
		(*s == 'a') ? data->option[2] = 1 : 0;
		(*s == 'r') ? data->option[3] = 1 : 0;
		(*s == 't') ? data->option[4] = 1 : 0;
		if (ft_strchr(OPT, (int)*s) == NULL) {
			write(1, IL_OPT, ft_strlen(IL_OPT));
			write(1, &(*s), 1);
			write(1, USAGE, ft_strlen(USAGE));
			exit(0);
		}
		s++;
	}
}

void			option_reader(int argc, char **argv, t_data *data)
{
	int 		i;
	char 		*s;

	i = 0;
	s = NULL;
	set_data(data);
	while (++i < argc && argv[i][0] == '-')
	{
		s = argv[i];
		option_parsing(s + 1, data);
	}
}
