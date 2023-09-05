#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Read a text file and print to STDOUT.
 * @filename: The name of the file to read.
 * @letters: The number of letters to read and print.
 *
 * Return: The actual number of bytes read and printed, or 0 on failure.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    char *buf;
    ssize_t fd, bytes_read, bytes_written, total_written;

    if (filename == NULL)
        return (0);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    buf = malloc(sizeof(char) * letters);
    if (buf == NULL)
    {
        close(fd);
        return (0);
    }

    total_written = 0;

    while ((bytes_read = read(fd, buf, letters)) > 0)
    {
        bytes_written = write(STDOUT_FILENO, buf, bytes_read);

        if (bytes_written == -1)
        {
            free(buf);
            close(fd);
            return (0);
        }

        total_written += bytes_written;
    }

    free(buf);
    close(fd);
    return (total_written);
}

