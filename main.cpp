#include <iostream>
#include <string>
#include <vector>
#include "lib.hpp"


int main(__attribute__((unused)) int argc, __attribute__((unused)) char const *argv[])
{
    try
    {
        std::vector<std::string> ip_pool;
        IPUtils::read_ip_pool(ip_pool);
        std::sort(ip_pool.begin(), ip_pool.end(), IPUtils::compareIp);

        IpFilter ipFilter = IpFilter(ip_pool);
        IPUtils::print(ipFilter.get_ip_pool());

        std::vector<std::string> res;

        res = ipFilter.filter(1);
        IPUtils::print(res);

        res = ipFilter.filter(46, 70);
        IPUtils::print(res);

        res = ipFilter.filter_any(46);
        IPUtils::print(res);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
