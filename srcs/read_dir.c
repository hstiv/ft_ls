#include "ft_ls.h"

/*
** fwp - filename with path *
*/

char 				*path_with_f_name(char *filename)
{
	char 			*s;
	char 			*result;

	s = ft_strjoin(file_path, "/");
	result = ft_strjoin(s, filename);
	free(s);
	return (result);
}

t_file			*new_file(char *s)
{
	t_file		*new;
	struct stat file_stat;
	char 		*fwp;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		throw("memory ERROR\n");
	fwp = path_with_f_name(s);
	lstat((file_path) ? fwp : s, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
		data.arg_dir_count++;
	new->f_stat = new_tstat(file_stat);
	new->next = NULL;
	new->prev = NULL;
	new->filename = ft_strdup(s);
	file_path = NULL;
	return (new);
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
		file_path = path;
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
