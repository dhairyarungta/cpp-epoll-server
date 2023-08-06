#include "../include/client_context.h"



ClientContext::ClientContext(int fd, const std::string& ip_addr)
    :fd(fd), ip_addr(ip_addr)
{ }


Request& ClientContext::get_request()
{
    return _request;
}

Response& ClientContext::get_response()
{
    return _response;
}

