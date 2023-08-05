#include "../include/epoll_loop.h" 

EpollLoop::EpollLoop()
{
    _epfd = epoll_create1(0)
    if(_epfd==-1)
    {
        exit(1);
        
    }
}

void EpollLoop::setnonblocking (const int & fd)
{
    int old_flags= fcntl(fd, F_GETFL, 0);
    fcntl(fd,F_SETFL, old_flags | O_NONBLOCK);
}

void EpollLoop::set_tcp_fd(const int fd)
{
    setnonblocking(fd);
    epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = fd;
    epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event);

    _tcp_fd = fd;
}

void EpollLoop::start()
{
    epoll_event events[MAX_EVENTS];
    std::cout<<"[INFO] epoll loop start\n";
    while(1)
    {
        int nfds = epoll_wait(_epfd, events, MAX_EVENTS,-1);
        for(int i =0;i<nfds, ++i)
        {
            epoll_event& event = events[i];
            if(event.data.fd==_tcp_fd)
            {
                auto [client_fd,client_ip] = handler->handle_accept(event);
                setnonblocking(client_fd);
                epoll_event nevent;
                nevent.events = EPOLLIN|EPOLLET;
                epoll_ctl(_epfd, EPOLL_CTL_MOD,(()))

            }else if(event.events & EPOLLIN)
            {
                handler->handle_read(event);
                epoll_event nevent;
                nevent.events = EPOLLOUT|EPOLLET;
                epoll_ctl(_epfd, EPOLL_CTL_MOD,((ClientContext*)event.data.ptr)->fd,&nevent);
            }else if(event.events & EPOLLOUT)
            {
                handler->handle_write(event);
                int fd = ((ClientContext*)event.data.ptr)->fd;
                epoll_ctl(_epfd, EPOLL_CTL_DEL,fd,NULL);
                close(fd);
            }else 
            {
                std::<<cout <<"None in epoll event type\n";
                
            }
        }
    }
}

EpollLoop::~EpollLoop()
{
    free(handler);
}