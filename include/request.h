#pragma once

#include "utils.h"
#include "client_context.h"


class Request 
{
    friend class ClientContext;
    friend std::ostream& operator<<(std::ostream&, const Request&);

private :
    HttpMethod _method;
    std::string _url;
    std::string _path;
    std::string _body;
    std::string _content_type;
    std::string _method_string;
    SSMap _headers;
    SSMap _data;
    SSMap _url_params;
    int _content_length;
    int _fd;
    bool _valid;
    bool _done;
    bool _keep_alive;

    const void set_special_headers();
    const void parse_request_line(const std::string& request_line);
    const void parse_headers(const std::string& headers);
    const void parse_body(const std::string& body);


public :
    void parse_request(const std::string &);
    const std::string& get_method_string() ;
    const HttpMethod get_method() const;
    const std::string& get_url() ;
    const std::string &get_path() ;
    const std::string& get_raw_body() ;
    const std::string& get_content_type() ;

    const SSMap& get_url_params() ;
    const SSMap& get_data() ;

    const int get_content_length() const;
    const bool is_valid()const;
    const bool is_keep_alive()const ;


protected :
    Request() = default;

}

std::ostream &operator<<(std::ostream &os, const Request &request);
