#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include "IO.h"

int IO::my_open(const char *file_name, bool write) {
    int fd;
    int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH; /* rw-rw-rw- */
    if (write) {
        fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, filePerms);
    } else {
        fd = open(file_name, O_RDONLY);
    }

    if (fd == -1) {
        if (errno == EINTR) {
            return my_open(file_name, write);
        } else {
            std::cout << strerror(errno) << " " << file_name << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return fd;
}

ssize_t IO::my_read(int fd, char *buf, ssize_t b_size) {
    ssize_t b_read = read(fd, buf, b_size);

    if (b_read == -1) {
        if (errno == EINTR) {
            return my_read(fd, buf, b_size);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    return b_read;
}

ssize_t IO::my_write(int fd, char *buf, ssize_t b_size) {
    ssize_t b_written = write(fd, buf, b_size);

    if (b_written == -1) {
        if (errno == EINTR) {
            return my_write(fd, buf, b_size);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return b_written;
}

int IO::my_close(int fd) {
    int status = close(fd);

    if (status == -1) {
        if (errno == EINTR) {
            return my_close(fd);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return status;
}