/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:18:36 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 19:58:17 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					get_block_size(char *s)
{
	DIR				*d;
	struct dirent	*el;
	struct stat		filestat;
	int				size;
	char			*path;

	if (!(d = opendir(s)))
		throw(s);
	size = 0;
	while ((el = readdir(d)) != NULL)
	{
		if (el->d_name[0] == '.')
			continue ;
		path = path_with_f_name(el->d_name, s);
		stat(path, &filestat);
		size += filestat.st_blocks;
		free(path);
	}
	closedir(d);
	return (size);
}

char				*path_with_f_name(char *filename, char *path)
{
	char			*s;
	char			*result;

	if (path == NULL)
		return (NULL);
	s = ft_strjoin(path, "/");
	result = ft_strjoin(s, filename);
	free(s);
	return (result);
}

static void			sort_conditions(t_file *ptr, int sort_by, int *swapped)
{
	int				tmp;

	tmp = 0;
	if (sort_by == MTIME)
		tmp = ptr->next->f_stat->mtime - ptr->f_stat->mtime;
	else if (sort_by == ASCII)
		tmp = ft_strcmp(ptr->filename, ptr->next->filename);
	if (tmp > 0)
	{
		swap_files(ptr, ptr->next);
		*swapped = 1;
	}
}

void				sort(t_file *files, int sort_by)
{
	t_file			*ptr;
	t_file			*ptr1;
	int				swapped;

	if (files == NULL)
		return ;
	ptr1 = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = files;
		while (ptr->next != ptr1)
		{
			sort_conditions(ptr, sort_by, &swapped);
			ptr = ptr->next;
		}
		ptr1 = ptr;
	}
}

t_file				*only_dirs(t_file *head)
{
	t_file			*ptr;

	ptr = head;
	while (head)
	{
		if (head->f_stat->permission[0] != 'd')
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
	while (head && head->prev)
		head = head->prev;
	return (head);
}
