#pragma once
#include "handler.h"

#define MAX_EVENTS 10500

class EpollLoop
{
public :
    static EpollLoop& Instance()
    {
        static EpollLoop instance;
        return instance;
    }

    void set_tcp_fd(const int fd);
    void setnonblocking(const int fd);
    void start();
    Handler * handler;

protected:
    EpollLoop();
    ~EpollLoop();
    EpollLoop(const EpollLoop&) = delete;
    EpollLoop& operator=(const EpollLoop&) = delete;

private :
    int _epfd;
    int _tcp_fd;


};