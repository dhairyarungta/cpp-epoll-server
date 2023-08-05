#include "utils.h"
#include "client_context.h"


class Response 
{
    friend class ClientContext;
private :
    SSMap _headers; 
    std::string _data;
    std::string _status_message;
    std::string _response_message;
    int _status_code;
    bool _prepared;
    friend std::ostream& operator<<(std::ostream&os ,const Response& response);

protected:
    Response() = default;

public :
    void set_header (const std::string& key, const std::string &value);
    void set_status_code (int status_code);
    void set_status_message (const std::string &status_message);
    void set_data (const std::string &data);
    void prepare(bool keep_alive);
    std::string& get_response_string(bool keep_alive);

};
