#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void test_file(const char *filename)
{
    int fd;
    char *line;
    int line_count = 0;

    printf("\n------------------------");
    printf("\nTesting file: %s\n", filename);
    printf("------------------------\n");
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }
    
    close(fd);
    printf("\nTotal lines read: %d\n", line_count);
}

int main(void)
{
    int fd1 = open("normal.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("no_newline.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd3 = open("empty_line.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int	fd4 = open("empty_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    write(fd1, "Hello World!\nThis is a test file.\nWith multiple lines.\n", 54);
    write(fd2, "No newline at the end of this file", 33);
    write(fd3, "\nEmpty lines\n\nBetween text\n", 27);

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);

    test_file("normal.txt");
    test_file("no_newline.txt");
    test_file("empty_line.txt");
    test_file("empty_file.txt");

    unlink("normal.txt");
    unlink("no_newline.txt");
    unlink("empty_line.txt");
    unlink("empty_file.txt");


    return (0);
}
