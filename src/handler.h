#pragma once

#include <set>
#include <climits>
#include <map>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <cstdio>
#include <signal.h>
#include <string.h>
#include <cerrno>
#include <unorderd_map>

class Handler
{
public :
    virtual void handle_read(epoll_event &event) = 0;
    virtual void  handle_write(epoll_event &event)  =0;
    virtual void handle_close(const int fd) = 0;
    virtual std::pair<int, std::string> handle_accept(epoll_event &event) =0;
};
