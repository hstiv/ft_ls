/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:18:30 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 19:57:56 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** fwp - filename with path *
*/

static void			set_link_path(t_file *new, char *path)
{
	size_t			bufsize;
	char			*buf;
	ssize_t			nbytes;
	char			*s;

	bufsize = new->f_stat->size + 1;
	if (new->f_stat->permission[0] == 'l')
	{
		if ((buf = (char *)malloc(sizeof(char) * bufsize)))
		{
			nbytes = readlink(path, buf, bufsize);
			s = ft_strncpy(ft_strnew(nbytes), buf, nbytes);
			new->f_stat->linked_path = s;
			free(buf);
		}
		else
			throw(path);
	}
	else
		new->f_stat->linked_path = NULL;
}

static void			set_xattr(t_file *new, char *s)
{
	char			*buf;
	size_t			size;

	size = listxattr(s, NULL, 0, XATTR_SHOWCOMPRESSION);
	if (size < 0)
		throw(s);
	buf = (char *)malloc(sizeof(char) * size);
	size = listxattr(s, buf, size, XATTR_SHOWCOMPRESSION);
	if (size > 0)
		new->f_stat->permission[10] = '@';
	free(buf);
}

t_file				*new_file(char *s)
{
	t_file			*new;
	struct stat		file_stat;
	char			*fwp;

	if ((new = (t_file *)malloc(sizeof(t_file))))
	{
		fwp = path_with_f_name(s, g_curr_dir);
		if ((lstat((g_curr_dir) ? fwp : s, &file_stat)) == -1)
			throw(s);
		new->f_stat = new_tstat(file_stat);
		set_link_path(new, (g_curr_dir) ? fwp : s);
		set_xattr(new, (g_curr_dir) ? fwp : s);
		if (new->f_stat->permission[0] == 'd')
			g_data.arg_dir_count++;
		(fwp != NULL) ? free(fwp) : 0;
		new->next = NULL;
		new->prev = NULL;
		new->filename = ft_strdup(s);
		return (new);
	}
	throw(s);
	return (NULL);
}

static t_file		*add_file_to_node(t_file *curr, char *d_name)
{
	curr->next = new_file(d_name);
	curr->next->prev = curr;
	curr = curr->next;
	return (curr);
}

t_file				*read_dir(char *path)
{
	DIR				*dirp;
	t_file			*start;
	t_file			*curr;
	struct dirent	*el;

	if ((dirp = opendir(path)) == NULL)
		throw(path);
	start = NULL;
	el = NULL;
	while ((el = readdir(dirp)) != NULL)
	{
		if (!g_data.option[2] && el->d_name[0] == '.')
			continue ;
		if (start == NULL)
		{
			start = new_file(el->d_name);
			curr = start;
		}
		else
			curr = add_file_to_node(curr, el->d_name);
	}
	closedir(dirp);
	return (start);
}
