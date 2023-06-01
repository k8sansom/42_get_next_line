#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd;
	char *line;

	// Open the file for reading
	fd = open("tester.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the file\n");
		return 1;
	}

	// Call get_next_line repeatedly until the end of file is reached
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	// Close the file
	close(fd);

	return 0;
}
