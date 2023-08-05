#pragma once //

#include "utils.h"

using SSMap = std::map<std::string, std::string>;

class Response 
{

}


class ClientConnect 
{
public :
    ClientConnect(int fd, const std::string& ip_addr);
    void* ptr;
    int fd;
    std::string ip_addr;
    Response& get_response();
    Request& get_request();

private:
    Response _response;
    Request& _request;

}