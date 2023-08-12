#include "../include/request.h"
#include <sstream>
// #include <nlohmann/json.hpp>

const SSMap& Request::get_url_params(){return _url_params;}

const SSMap& Request::get_data(){return _data;}

const int Request::get_content_length()const {return _content_length;}

const std::string& Request::get_content_type() {return _content_type;}

const std::string& Request::get_method_string(){return _method_string;}

const HttpMethod Request::get_method()const {return _method;}

const std::string& Request::get_raw_body(){return _body;}

const std::string& Request::get_url(){return _url;}

const std::string& Request::get_path(){return _path;}

const bool Request::is_valid()const {return _valid;}

const bool Request::is_keep_alive()const {return _keep_alive;}

void Request::parse_request(const std::string &raw)
{
    size_t pos_request_line_end = raw.find(LINE_SEP);
    if(pos_request_line_end ==std::string::npos)
    {
        return;
    }

    size_t pos_headers_end = raw.find(LINE_SEP+LINE_SEP, pos_request_line_end);
    size_t pos_headers_start = pos_request_line_end+LINE_SEP.size();
    std::string request_line = raw.substr(0,pos_request_line_end);
    std::string headers = raw.substr(pos_headers_start, pos_headers_end-pos_headers_start);

    parse_request_line(request_line);
    parse_headers(headers);
    if(_method==HttpMethod::POST)
    {
        size_t pos_body_start = pos_headers_end + (LINE_SEP+LINE_SEP).size();
        size_t  body_lenght = raw.size()-pos_body_start+1;
        if(_content_length<body_lenght)
        {
            std::cerr<<"Request Legnth error\n";
        }
        parse_body(raw.substr(pos_body_start,_content_length));
    }

    
}


const void Request::parse_headers(const std::string& headers)
{
    size_t prev = 0;
    size_t cur;
    while(cur!=std::string::npos)
    {
        cur = headers.find(LINE_SEP, prev);
        size_t pos_sep = headers.find(":", prev);
        std::string key = trim(headers.substr(prev, pos_sep-prev));
        std::string value= trim(headers.substr(pos_sep+1, cur-pos_sep-1));
        _headers.emplace(std::move(key), std::move(value));
        prev = cur+1;

    }
    set_special_headers();
}


const void Request::set_special_headers()
{
    _keep_alive = _headers.count("Connection")&&_headers["Connection"] =="Keep-Alive";

    _content_type = _headers["Content-Type"] ;
    _content_length = _headers.count("Content-Length")?std::stoi(_headers["Content-Length"]):0;

}


const void Request::parse_request_line(const std::string& request_line)
{
    size_t pos_method_end =request_line.find("");
    size_t pos_path_end = request_line.find(" ",pos_method_end+1);
    size_t pose_protocol_end = request_line.find(" ",pos_path_end+1);
    _method_string= request_line.substr(0,pos_path_end);

    if(!method_to_enum.count(_method_string))
    {
       std::cerr<<"Log error in parse request line\n";
    }

    _method = method_to_enum[_method_string];
    _url = request_line.substr(pos_method_end+1,
            pos_path_end-pos_method_end-1);

    std::string protocol = request_line.substr(pos_path_end+1,request_line.size()-pos_path_end-1);
    if(protocol!="HTTP/1.1")
    {
        std::cerr<<"Wrong HTTP version\n";
    }
    size_t url_params_start = _url.find("?");
    _path = _url.substr(0, url_params_start);
    if(url_params_start==std::string::npos)
    {
        return;

    }

    size_t params_length = _url.size()-url_params_start;
    std::istringstream params(_url.substr(url_params_start+1, params_length));
    std::string kvpair;

    while(std::getline(params, kvpair, '&'))
    {
        size_t pos_sep =kvpair.find("=");
        std::string key = kvpair.substr(0, pos_sep);
        std::string value = kvpair.substr(pos_sep+1);
        _url_params[key]= value;
        
    }
}


const void Request::parse_body(const std::string& body)
{
    using json = nlohmann::json;
    try
    {
        json json_data = json::parse(body);
        for(auto it = json_data.begin();it!=json_data.end();++i)
        {
            _data[it.key()]= it.value();
        }
    }
    catch(json::parse_error &e)
    {
        std::cerr << "Error parsing JSON body on POST request \n";
        return;
    }
    
}

std::ostream& operator<<(std::ostream&os, const Request &request) 
{
    os<<"METHOD :"<<request._method<<"\n";
    os<<"PATH :"<<request._url<<"\n";
    os<<"BODY"<<request._body<<"\n";
    os<<"CONTENT LENGTH"<<request._content_length<<"\n";
    os<<"CONTENT_TYPE"<<request._content_type;
    return os;


}