#include "../include/response.h"

void Response::set_header(const std::string&key, const std::string&value);
{
    _header[key] = value;
}

void Response::set_status_code(int status_code)
{
    _status_code = status_code;

}

void Response::set_status_message(const std::string& status_message)
{
    _status_message = status_message;
} 

void Response::set_data(const std::String& data)
{
    _data = data;
}

void Response::prepare(bool keep_alive)
{
    std::ostringstream oss;
    oss<<"HTTP/1.1"<<" "<<_status_code<<" "<<_status_message__LINE_SEP;
    if(!_headers.count("Content-Type"))
    {
        oss<"Content-Type: application/json"<<LINE_SEP;

    }
    if(!_headers.count("Content-Length"))
    {
        oss<<"Content-Length: "<<_data.size()<<LINE_SEP;

    }
    oss<<"Connection: "<<(keep_alive?"Keep-Alive":"close")<<LINE_SEP;
    

    
    for(auto& it: _headers)
    {
        os<<it.first<<": "<<it.second<<LINE_SEP;
    }

    oss<<LINE_SEP;
    oss<<_data;
    _response_string = os.str();
}


std::string& Response::get_response_string(bool keep_alive)
{
    if(!_prepared) 
    {
        prepare(keep_alive);
        _prepared = true;
    }
    return _response_string;
}