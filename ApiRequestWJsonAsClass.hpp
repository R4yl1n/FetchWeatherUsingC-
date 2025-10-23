#ifndef APIREQUESTWJSONASCLASS_HPP
#define APIREQUESTWJSONASCLASS_HPP

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class ApiRequestWJsonAsClass
{
private:

static size_t write_to_string(void* contents, size_t size, size_t nmemb, void* userp);
static std::string getUserInput();
    
public:
static json startQuery();
};
#endif // APIREQUESTWJSONASCLASS_HPP