#include "ft_ls.h"

/*
** fwp - filename with path *
*/

char 				*path_with_f_name(char *filename, char *path)
{
	char 			*s;
	char 			*result;

	s = ft_strjoin(path, "/");
	result = ft_strjoin(s, filename);
	free(s);
	return (result);
}

char 				*rmallocladir(char *s)
{
	int 			i;
	int 			l;
	char 			*result;

	i = 0;
	l = 0;
	while ()
}

t_file				*new_file(char *s)
{
	t_file			*new;
	struct stat		file_stat;
	char			*fwp;

	if ((new = (t_file *) malloc(sizeof(t_file))))
	{
		fwp = path_with_f_name(s, curr_dir);
		lstat((curr_dir) ? fwp : s, &file_stat);
		new->f_stat = new_tstat(file_stat);
		if (new->f_stat->permission[0] == 'd')
			data.arg_dir_count++;
		new->next = NULL;
		new->prev = NULL;
		new->filename = ft_strdup(s);
		return (new);
	}
	throw("memory ERROR\n");
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
	struct	dirent	*el;

	if ((dirp = opendir(path)) == NULL)
		throw(NOPEN);
	start = NULL;
	el = NULL;
	while ((el = readdir(dirp)) != NULL)
	{
		if (!data.option[2] && el->d_name[0] == '.')
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
