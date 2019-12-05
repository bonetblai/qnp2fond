// (c) 2017 Blai Bonet

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

namespace Utils {

inline float read_time_in_seconds(bool add_stime = true) {
    struct rusage r_usage;
    float time = 0;

    getrusage(RUSAGE_SELF, &r_usage);
    time += float(r_usage.ru_utime.tv_sec) +
            float(r_usage.ru_utime.tv_usec) / float(1e6);
    if( add_stime ) {
        time += float(r_usage.ru_stime.tv_sec) +
                float(r_usage.ru_stime.tv_usec) / float(1e6);
    }

    getrusage(RUSAGE_CHILDREN, &r_usage);
    time += float(r_usage.ru_utime.tv_sec) +
            float(r_usage.ru_utime.tv_usec) / float(1e6);
    if( add_stime ) {
        time += float(r_usage.ru_stime.tv_sec) +
                float(r_usage.ru_stime.tv_usec) / float(1e6);
    }

    return time;
}

inline std::string normal() { return "\x1B[0m"; }
inline std::string bold() { return "\x1B[1m"; }
inline std::string red() { return "\x1B[31;1m"; }
inline std::string green() { return "\x1B[32;1m"; }
inline std::string yellow() { return "\x1B[33;1m"; }
inline std::string blue() { return "\x1B[34;1m"; }
inline std::string magenta() { return "\x1B[35;1m"; }
inline std::string cyan() { return "\x1B[36;1m"; }
inline std::string error() { return "\x1B[31;1merror: \x1B[0m"; }
inline std::string warning() { return "\x1B[35;1mwarning: \x1B[0m"; }
inline std::string internal_error() { return "\x1B[31;1minternal error: \x1B[0m"; }

inline std::string cmdline(int argc, const char *argv[]) {
    std::string cmd = argv[0];
    for( int j = 1; j < argc; ++j )
        cmd += std::string(" ") + argv[j];
    return cmd;
}

};

#endif

