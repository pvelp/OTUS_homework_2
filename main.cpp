#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "lib.hpp"


int main()
{
    try
    {
        std::vector<std::array<uint8_t , 4>> ip_pool;
        IPUtils::read_ip_pool(ip_pool);
        std::sort(ip_pool.rbegin(), ip_pool.rend());
        IpFilter ipFilter = IpFilter(ip_pool);
//        IPUtils::print(ipFilter.get_ip_pool());

        std::vector<std::array<uint8_t, 4>> res;

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
