#include "ft_ls.h"

static void			recursive(t_file *ptr)
{
	t_file			*files;
	int 			print_enter;
	char 			*s;

	ptr = only_dirs(ptr);
	print_enter = 0;
	while (ptr)
	{
		(curr_dir == NULL) ? curr_dir = ft_strdup(".") : 0;
		files = ptr;
		(print_enter == 1) ? write(1, "\n", 1) : 0;
		print_dir_name(ptr);
		s = path_with_f_name(ptr->filename, curr_dir);
		free(curr_dir);
		curr_dir = s;
		ft_ls(read_dir(curr_dir));
		s = rmladir(curr_dir);
		free(curr_dir);
		curr_dir = s;
		ptr = ptr->next;
		print_enter = 1;
		del_file(files);
	}
}

void 		ft_ls(t_file *ptr)
{
	t_file			*files;

	files = ptr;
	sort(files, (data.option[4]) ? MTIME : ASCII);
	print(files, 0);
	if (data.option[1] == 1)
		recursive(files);
}

static void			arg_handler(void)
{
	t_file			*file;
	int 			print_enter;

	file = data.arg_file;
	print_enter = 0;
	sort(file, (data.option[4]) ? MTIME : ASCII);
	while (file)
	{
		if (file->f_stat->permission[0] != 'd')
			print(file, 1);
		file = file->next;
	}
	data.arg_file = only_dirs(data.arg_file);
	while (data.arg_file)
	{
		file = data.arg_file;
		(print_enter == 1) ? write(1, "\n", 1) : 0;
		print_dir_name(data.arg_file);
		ft_ls(read_dir(data.arg_file->filename));
		data.arg_file = data.arg_file->next;
		print_enter = 1;
		del_file(file);
	}
}

static void 		current_dir(void)
{
	t_file 			*file;

	file = new_file(".");
	write(1, "total ", 6);
	ft_putnbr(file->f_stat->blocks);
	write(1, "\n", 1);
	ft_ls(read_dir("."));
	del_file(file);
}

int					main(int argc, char **argv)
{
	set_data();
	(argc > 1 && argv[1] != NULL) ? arg_reader(argc, argv) : 0;
	if (data.arg_files_count == 0 || data.arg_file == NULL)
		current_dir();
	else
		arg_handler();
	return (0);
}
