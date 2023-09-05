#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads and prints a text file.
 * @filename: The name of the file to read.
 * @letters: The number of letters to read and print.
 *
 * Return: The actual number of letters read and printed, 0 on failure.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    if (filename == NULL)
        return (0);

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    char buffer[1024];
    ssize_t bytes_read, bytes_written, total_written = 0;

    while (letters > 0)
    {
        bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            break;

        if (bytes_read > (ssize_t)letters)
            bytes_read = letters;

        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);

        if (bytes_written == -1)
        {
            close(fd);
            return (0);
        }

        total_written += bytes_written;
        letters -= bytes_written;
    }

    close(fd);
    return (total_written);
}

