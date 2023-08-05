#pragma once
#include "handler.h"
#include "epoll_loop.h"
#include "utils.h"
#include <unordered_map>


#define LISTEN_BACKLOG 1024
#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024


class Request;
class Response ;
class EpollLoop ;

using RouteHandler = std::fucntion<void(Request&, Response&)>;


class HttpResource 
{
    friend class HttpServer;
private :
    std::unordered_map<HttpMethod,RouteHandler>_method_to_handler_map;


public :
    bool method_allowed(HttpMethod method) ;
    void handle (Request&, Response&) ;
    void add_handler(HttpMethod method, const RouteHandler& route_handler) ;
    
};

class HttpServer :public Handler
{
public :
    HttpServer(int port = DEFAULT_PORT);
    void start();

    void handle_read(epoll_event&)override;
    void handle_write(epoll_event&)override;
    void handle_closed(const int fd)override;
    std::pair <int , std::string> handle_accept(epoll_event&)override;
    void route_request(Request&, Respoinse&);
    void add_resource(const std::string& path, const HttpResource&);


private :
    sockaddr_in create_listening_addr();
    int _tcp_fd;
    int _port;
    std::unordered_map<std::string, HttpResource>_resource_map;
    EpollLoop& _epoll_loop;
}

