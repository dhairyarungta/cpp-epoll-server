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

    }
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


}