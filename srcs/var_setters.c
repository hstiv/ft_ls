//
// Created by Hallie Stiv on 10/7/20.
//

#include "ft_ls.h"

void			set_data(t_data *data)
{
	data->option[0] = 0;
	data->option[1] = 0;
	data->option[2] = 0;
	data->option[3] = 0;
	data->option[4] = 0;
	data->file_count = 0;
	data->filenames = (char **)malloc(sizeof(char *) * 1);
	data->filenames[0] = NULL;
}
