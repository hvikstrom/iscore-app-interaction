#pragma once
#include <ossia/ossia.hpp>
//#include <publicservice.h>

using namespace ossia;
using namespace std;
//using namespace DNSSD;

namespace connection
{

class Connection final
{
private:
    ossia::net::generic_device mDevice;


public:
    Connection(std::string device_name);
    ~Connection();

    std::vector<ossia::value> sendInteraction(const std::string interaction);

};
}
