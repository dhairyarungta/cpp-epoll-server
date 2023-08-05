#include "../include/epoll_loop.h" 

EpollLoop::EpollLoop()
{
    _epfd = epoll_create1(0)
    if(_epfd==-1)
    {
        exit(1);
        
    }
}

void EpollLoop::setnonblocking (const int fd)
{

}

void EpollLoop::set_tcp_fd(const int fd)
{

}

void EpollLoop::start()
{

}