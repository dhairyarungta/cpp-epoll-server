#include "../include/http_server.h"


sockaddr_in HttpServer::create_listening_addr()
{
    sockaddr_in ret;
    memset(&ret, 0, sizeof(ret));
    ret.sin_family = AF_INET;
    ret.sin_port = htons(_port);
    ret.sin_addr.s_addr = htonl(INADDR_ANY);
    return ret;
}

HttpServer::HttpServer(int port = DEFAULT_PORT) 
    :_port (port), _epoll_loop(EpollLoop::Instance())
{
    _tcp_fd =socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsocketopt(_tcp_fd,SOL_SOCKET,SO_REUSEADDR,&opt, sizeof(opt));
    sockaddr_in addr{create_listening_addr()};
    bind(_tcp_fd, LISTEN_BACKLOG);
    listen(_tcp_fd, LISTEN_BACKLOG);
    std::count<<"[INFO] Server running at"<<inet_ntoa(add.sin_addr)<<":"<<ntohs(addr.sin_port)<<"\n";
    _epoll_loop.set_tcp_fd(_tcp_fd);
    _epoll_loop.handler = dynamic_cast<Handler*>(this);

}

HttpServer::handle_read(epoll_event& event) 
{
    ClientContext* client_context = (ClientContext*)event.data.ptr;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int fd = client_context->fd;
    read(fd, buffer,BUFFER_SIZE);
    client_context->get_request().parse_request(buffer);
    route_request(client_context->get_request(),client_context->get_response());

}
void HttpServer::start() {_epoll_loop.start();}


void HttpServer::route_request(Request& request, Respons& response) 
{
    if(!_resource_map.count(reqeust.get_path()))
    {
        response.set_status_code(404);
        response.set_status_message("Not Found");
        response.set_data("Path='"+request.get_path()+"' not found.");
        return ;
    }
    HttpServer resouce = _resouce_map[request.get_path()];
    if(!resouce.method_allowed(reqeust.get_method()))
    {
        response.set_status_code(405);
        response.set_status_message("Not Allowed");
        response.set_data("Path='" + request.get_path() + "' does not allow HttpMethod='" +  request.get_method_string() + "'.");
        return;
    }

    try{
        resource.handle(request,response);
        response.set_status_code(200);
        response.set_status_message("OK");
    }catch(...) 
    {
        response.set_status_code(500);
        response.set_status_message("Internal Server Error");

    }
}

void HttpServer::handle_write(epoll_event &event)
{
    ClientContext *client_context = (ClientContext*)event.data.ptr;
    std::string response_string = client_context->get_response().get_response_string(
        client_context->get_request().is_keep_alive());

    write (client_context->fd,response_string.data(), response_string.size());
}

void HttpServer::handle_close(const int fd)
{
    close(fd);   
}

void HttpServer::add_resource(const std::string& path, const HttpResource& resource)
{
    _resource_map[path] = resource;
}

void HttpResource::add_handler(HttpMethod method, const RouteHandler& route_handler)
{
    _method_to_handler[method] = route_handler;
}

void HttpResource::handle (Request& request, Response& response) 
{
    _method_to_handler[request.get_method()](request,response);
}

void HttpResource::method_allowed(HttpMethod method) 
{
    return (_method_to_handler.count(method) !=0);

}
