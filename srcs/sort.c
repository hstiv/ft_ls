#include "ft_ls.h"

static void 		swap_files(t_file *p1, t_file *p2)
{
	t_stat			*t_tmp;
	char 			*c_tmp;

	t_tmp = p1->f_stat;
	c_tmp = p1->filename;
	p1->f_stat = p2->f_stat;
	p1->filename = p2->filename;
	p2->f_stat = t_tmp;
	p2->filename = c_tmp;
}

void 				sort_files(t_file *files)
{
	t_file			*ptr;
	t_file			*ptr1;
	int				swapped;

	if (files == NULL)
		return;
	ptr1 = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = files;
		while (ptr->next != ptr1)
		{
			if (ft_strcmp(ptr->filename, ptr->next->filename) > 0) {
				swap_files(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		ptr1 = ptr;
	}
}