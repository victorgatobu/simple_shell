#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
    info_t info[] = { INFO_INIT }; // Initialize info_t struct
    int fd = STDERR_FILENO; // Default file descriptor

    // Update fd using inline assembly
    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY); // Open the provided file
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    populate_env_list(info); // Populate the environment list
    read_history(info); // Read history from file
    hsh(info, argv); // Execute shell

    return EXIT_SUCCESS;
}
