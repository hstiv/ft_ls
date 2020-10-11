#include "ft_ls.h"

t_file			*new_file(char *s)
{
	t_file		*new;
	struct stat file_stat;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		throw("memory ERROR\n");
	stat(s, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
		data.arg_dir_count++;
	new->f_stat = new_tstat(file_stat);
	new->next = NULL;
	new->prev = NULL;
	new->filename = ft_strdup(s);
	return (new);
}

t_file				*add_file_to_node(t_file *curr, char *d_name)
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

	dirp = opendir(path);
	start = NULL;
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
