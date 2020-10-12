#include "ft_ls.h"

static void 		sort_conditions(t_file *ptr, int order, int sort_by, int *swapped)
{
	int 			tmp;

	tmp = 0;
	if (sort_by == MTIME)
		tmp = ptr->f_stat->mtime - ptr->next->f_stat->mtime;
	else if (sort_by == ASCII)
		tmp = ft_strcmp(ptr->filename, ptr->next->filename);
	if (tmp > 0 && order == ASC)
	{
		swap_files(ptr, ptr->next);
		*swapped = 1;
	}
	else if (tmp < 0 && order == DESC)
	{
		swap_files(ptr, ptr->next);
		*swapped = 1;
	}
}

void 				sort(t_file *files, int order, int sort_by)
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
			sort_conditions(ptr, order, sort_by, &swapped);
			ptr = ptr->next;
		}
		ptr1 = ptr;
	}
}

t_file				*reverse_list(t_file *head)
{
	t_file			*prev;
	t_file			*curr;

	sort(head, ASC, ASCII);
	prev = head;
	head = head->next;
	curr = head;
	prev->next = NULL;
	prev->prev = curr;
	while (head != NULL)
	{
		head = head->next;
		curr->next = prev;
		prev = curr;
		curr = head;
		prev->prev = curr;
	}
	return (prev);
}

t_file				*only_dirs(t_file *head)
{
	t_file			*ptr;

	while (head)
	{
		if (head->f_stat->permission[0] == '-')
		{
			if (head->next)
				head->next->prev = head->prev;
			if (head->prev)
				head->prev->next = head->next;
			ptr = (head->next != NULL) ? head->next : head->prev;
			del_file(head);
			head = ptr;
		}
		else
			head = head->next;
	}
	head = ptr;
	while (head->prev)
		head = head->prev;
	return (head);
}
