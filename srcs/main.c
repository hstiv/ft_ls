#include "ft_ls.h"

void 				ft_ls(t_file *ptr)
{
	t_file			*files;

	files = ptr;
	sort(files, (data.option[4]) ? MTIME : ASCII);
	print(files, 0);
	if (data.option[1] == 1)
	{
		ptr = only_dirs(files);
		files = ptr;
		while (ptr)
		{
			files = ptr;
			ft_ls(read_dir(ptr->filename));
			ptr = ptr->next;
			del_file(files);
		}
	}
}

void 				arg_handler(void)
{
	t_file			*file;

	file = data.arg_file;
	sort(file, (data.option[4]) ? MTIME : ASCII);
	while (file)
	{
		if (file->f_stat->permission[0] == '-')
			print(file, 1);
		file = file->next;
	}
	data.arg_file = only_dirs(data.arg_file);
	while (data.arg_file)
	{
		file = data.arg_file;
		ft_ls(read_dir(data.arg_file->filename));
		data.arg_file = data.arg_file->next;
		del_file(file);
	}
}

int					main(int argc, char **argv)
{
	t_file			*files;

	set_data();
	(argc > 1 && argv[1] != NULL) ? arg_reader(argc, argv) : 0;
	if (data.arg_files_count == 0 || data.arg_file == NULL)
		ft_ls(read_dir("."));
	else
		arg_handler();
	return (0);
}
