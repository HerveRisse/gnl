#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void test_file(const char *filename)
{
    int fd;
    char *line;
    int line_count = 0;

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
    // First create test files
    int fd1 = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd3 = open("test3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Write test content
    write(fd1, "Hello World!\nThis is a test file.\nWith multiple lines.\n", 54);
    write(fd2, "No newline at the end of this file", 33);
    write(fd3, "\nEmpty lines\n\nBetween text\n", 27);

    close(fd1);
    close(fd2);
    close(fd3);

    // Test with different files
    test_file("test1.txt");  // Normal case with newlines
    test_file("test2.txt");  // File without newline at the end
    test_file("test3.txt");  // File with empty lines

    // Clean up test files
    unlink("test1.txt");
    unlink("test2.txt");
    unlink("test3.txt");

    return (0);
}
