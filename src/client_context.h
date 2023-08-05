#include "utils.h"
#include "response.h
#include "request.h"

#include 
class ClientContext
{
public :
    ClientContext(int fd, const std::string& ip_addr);
    void *ptr;
    int fd;
    std::string ip_addr;
    Response& get_response();
    Request& get_request();


private:
    Response _response;
    Request _request;


};
