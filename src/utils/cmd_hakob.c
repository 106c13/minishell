#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

// List directory
// Command: ls
// opendir returns something like file descriptor, like open() funciton "open(filename, O_RDONLY)"
// readdir returns a struct of a file, it working like get_next_line, each time when you call it, it returns a
// file struct and switch to the next one.
void	list_dir(const char *path)
{
	DIR		*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		printf("%s", entry->d_name);
		entry = readdir(dir);
		if (entry)
			printf(" ");
	}
	printf("\n");
	closedir(dir);
}

// Print working directory
// Command: pwd
// when getcwd got NULL pointer as first argument, it will allocate memory by it self. We can give our own pointer, 
// but we can't calculate the size of the path.
void	pwd()
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	else
		printf("Error\n");
}
