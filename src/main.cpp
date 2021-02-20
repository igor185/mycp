// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <string>
#include <vector>
#include "util.h"
#include "IO.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

struct args {
    bool f;
    bool r;
    std::vector<std::string> files;
};

args process_arg(int argc, char **argv) {
    std::string arg;
    args args = {false, false, {}};
    for (int i = 0; i < argc; i++) {
        arg = argv[i];
        if (arg == "-h" || arg == "--help") {
//            print help
            exit(EXIT_SUCCESS);
        } else if (arg == "-f") {
            args.f = true;
        } else if(arg == "-R"){
            args.r = true;
        } else {
            args.files.push_back(arg);
        }
    }
    return args;
}

int main(int argc, char **argv) {

//    args args = process_arg(argc, argv);

    std::string file1 = "./CMakeLists.txt";
    std::string file2 = "./new/copy.txt";

    size_t fd1 = IO::my_open(file1.c_str(), false);
    size_t fd2 = IO::my_open(file2.c_str(), true);

    util::copy(fd1, fd2);

//    std::cout << open(file1.c_str(),  O_RDONLY) << std::endl;
//    std::cout << strerror(errno) << " " << file1 << std::endl;

    return EXIT_SUCCESS;
}
