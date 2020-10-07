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

void			option_reader(int argc, char **argv, t_data *data)
{
	set_data(data);
}
