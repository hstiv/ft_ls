#include "ft_ls.h"

void 				print_n_times(char c, int n)
{
	int 			i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void 				print_l(t_file *file)
{
	write(1, file->f_stat->permission, ft_strlen(file->f_stat->permission));
	print_n_times(' ', data.alley_mlen[0] - file->f_stat->len[0]);
	ft_putnbr(file->f_stat->nlink);
	print_n_times(' ', data.alley_mlen[1] - file->f_stat->len[1]);
	write(1, file->f_stat->pw_name, ft_strlen(file->f_stat->pw_name));
	print_n_times(' ', data.alley_mlen[2] - file->f_stat->len[2]);
	write(1, file->f_stat->gr_name, ft_strlen(file->f_stat->gr_name));
	print_n_times(' ', data.alley_mlen[3] - file->f_stat->len[3]);
	ft_putnbr(file->f_stat->size);
	write(1, " ", 1);
	write(1, file->f_stat->month, ft_strlen(file->f_stat->month));
	print_n_times(' ', data.alley_mlen[4] - file->f_stat->len[4]);
	write(1, file->f_stat->day, ft_strlen(file->f_stat->day));
	write(1, " ", 1);
	write(1, file->f_stat->hour, 2);
	write(1, ":", 1);
	write(1, file->f_stat->min, 2);
	write(1, " ", 1);
	write(1, file->filename, ft_strlen(file->filename));
}

void				print(t_file *start)
{
	t_file			*file;

	file = start;
	if (data.option[3])
	{
		while (file->next)
			file = file->next;
		while (file)
		{
			(data.option[0] == 1) ? print_l(file) :
			write(1, file->filename, ft_strlen(file->filename));
			(data.option[0] == 1) ? write(1, "\n", 1) : write(1, "\t", 1);
			file = file->prev;
		}
	}
	else
	{
		while (file)
		{
			(data.option[0] == 1) ? print_l(file) :
			write(1, file->filename, ft_strlen(file->filename));
			(data.option[0] == 1) ? write(1, "\n", 1) : write(1, "\t", 1);
			file = file->next;
		}
	}
}
