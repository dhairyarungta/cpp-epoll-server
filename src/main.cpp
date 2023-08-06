#include "../include/http_server.h"
#include <iostream>
#include <fstream>
#include <nlohamnn/json.hpp>


using json = nlohmann::json;

void get_post_echo(Request& reqeust, Response& response)
{
    SSMap data = requst.get_data();
    SSMap url_params = request.get_url_params();

    json v;
    for (auto&it :data)
    {
        v["data_received"][it.first] = it.second;

    }
    for (auto&it :url_params)
    {
        v["url_params_received"][it.first] = it.second;
    }
    response.set_data(v.dump());
}

void get_home(Request& request, Response& response) 
{
    response.set_data("Hello there!\n");
}

void get_index(Request& reqeust, Response& response)
{
    std::ifstream ifs("../public/dtml.html");
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));
    
    response.set_data(content);
    response.set_header("Content-Type", "text/html");


}


void get_dtl(Request& reqeust, Response& response)
{
    std::ifstream ifs("../public/dtl.html");
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::streambuf_iterator<char>()));

    response.set_data(content); 
    response.set_header("Content-Type", "text/html");

}

int main()
{
    HttpServer server;

    HttpResource echo_resource;
    echo_resource.add_handler(HttpMethod::POST, get_post_echo);
    echo_resouce.add_handler(HttpMethod::GET,get_post_echo);
    server.add_resource("/echo", echo_resource);

    HttpResource home_resouce;
    home_resouce.add_handler(HttpMethod::GET,get_home);
    server.add_resouce("/home",home_resouce);

    HttpResource index_resouce;
    index_resouce.add_handler(HttpMethod::GET,get_index);
    server.add_resouce("/", index_resouce);

    

    server.start();
    return 0;

}