#pragma once
#ifndef MYCAT_IO_HPP
#define MYCAT_IO_HPP

// 10Mb
#define BUF_SIZE 1048576

namespace IO {

    int my_open(const char *file_name, bool write);

    ssize_t my_read(int fd, char *buffer, ssize_t b_size);

    ssize_t my_write(int fd, char *buf, ssize_t b_size);

    int my_close(int fd);
}

#endif

