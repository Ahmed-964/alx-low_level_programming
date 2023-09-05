#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf_file(unsigned char *e_ident);
void print_magic_numbers(unsigned char *e_ident);
void print_class_info(unsigned char *e_ident);
void print_data_info(unsigned char *e_ident);
void print_version_info(unsigned char *e_ident);
void print_os_abi_info(unsigned char *e_ident);
void print_abi_version(unsigned char *e_ident);
void print_elf_type(unsigned int e_type, unsigned char *e_ident);
void print_entry_point(unsigned long int e_entry, unsigned char *e_ident);
void close_elf_file(int elf);

/**
 * check_elf_file - Checks if a file is an ELF file.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file, it exits with code 98.
 */
void check_elf_file(unsigned char *e_ident)
{
    int index;

    for (index = 0; index < 4; index++)
    {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F')
        {
            dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

/**
 * print_magic_numbers - Prints the magic numbers of an ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic_numbers(unsigned char *e_ident)
{
    int index;

    printf(" Magic: ");

    for (index = 0; index < EI_NIDENT; index++)
    {
        printf("%02x", e_ident[index]);

        if (index == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }
}

// ... (The rest of the functions remain unchanged with updated names)

/**
 * main - Displays the information contained in the ELF header
 *        at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the file is not an ELF File or the function fails,
 *              it exits with code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
    Elf64_Ehdr *header;
    int file_descriptor, read_result;

    if (argc != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s <ELF file>\n", argv[0]);
        exit(98);
    }

    file_descriptor = open(argv[1], O_RDONLY);
    if (file_descriptor == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    header = malloc(sizeof(Elf64_Ehdr));
    if (header == NULL)
    {
        close_elf_file(file_descriptor);
        dprintf(STDERR_FILENO, "Error: Memory allocation failed\n");
        exit(98);
    }

    read_result = read(file_descriptor, header, sizeof(Elf64_Ehdr));
    if (read_result == -1)
    {
        free(header);
        close_elf_file(file_descriptor);
        dprintf(STDERR_FILENO, "Error: Failed to read file %s\n", argv[1]);
        exit(98);
    }

    check_elf_file(header->e_ident);
    printf("ELF Header:\n");
    print_magic_numbers(header->e_ident);
    print_class_info(header->e_ident);
    print_data_info(header->e_ident);
    print_version_info(header->e_ident);
    print_os_abi_info(header->e_ident);
    print_abi_version(header->e_ident);
    print_elf_type(header->e_type, header->e_ident);
    print_entry_point(header->e_entry, header->e_ident);

    free(header);
    close_elf_file(file_descriptor);
    return (0);
}

