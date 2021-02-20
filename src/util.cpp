#include "util.h"
#include "IO.h"

void util::copy(size_t fd1, size_t fd2) {
    char buffer[BUF_SIZE];
        ssize_t b_used = 1;
        while (b_used > 0) {
            b_used = IO::my_read(fd1, buffer, BUF_SIZE);
            b_used = IO::my_write(fd2, buffer, b_used);
        }
}