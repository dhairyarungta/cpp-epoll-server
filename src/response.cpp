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