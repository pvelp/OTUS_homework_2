#include "lib.hpp"
#include "version.h"
#include <iostream>
#include <sstream>
#include <utility>

int version() {
    return PROJECT_VERSION_PATCH;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

std::vector<std::string> IPUtils::split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void IPUtils::read_ip_pool(std::vector<std::string> &ip_pool) {
    for(std::string line; std::getline(std::cin, line); )
    {
        if (line.empty()){
            break;
        }

        std::vector<std::string> v = IPUtils::split(line, '\t');
        ip_pool.push_back(v.at(0));
    }
}

std::vector<int> IPUtils::convertIp(const std::string &ip) {
    std::vector<int> result;
    std::stringstream ss(ip);
    std::string temp;
    while (getline(ss, temp, '.')) {
        result.push_back(stoi(temp));
    }
    return result;
}


void IPUtils::print(const std::vector<std::string>& l) {
    for (auto const& ip : l){
        std::cout << ip << std::endl;
    }
}


bool IPUtils::compareIp(const std::string &a, const std::string &b) {
    std::vector<int> ip1 = IPUtils::convertIp(a);
    std::vector<int> ip2 = IPUtils::convertIp(b);
    return ip1 > ip2;
}


IpFilter::IpFilter(std::vector<std::string> ip_list) : ip_pool(std::move(ip_list)) {}


std::vector<std::string> IpFilter::filter(uint8_t first_byte) {
    std::vector<std::string> res;
    for (auto const& ip : ip_pool){
        std::vector<std::string> r = IPUtils::split(ip, '.');
        if (r.at(0) == std::to_string(first_byte)){
            res.push_back(ip);
        }
    }
    return res;
}


std::vector<std::string> IpFilter::filter(uint8_t first_byte, uint8_t second_byte) {
    std::vector<std::string> res;
    for (auto const& ip : ip_pool){
        std::vector<std::string> r = IPUtils::split(ip, '.');
        if (r.at(0) == std::to_string(first_byte) && r.at(1) == std::to_string(second_byte)){
            res.push_back(ip);
        }
    }
    return res;
}


std::vector<std::string> IpFilter::filter_any(uint8_t byte_value) {
    std::vector<std::string> res;
    for (auto const& ip : ip_pool){
        std::vector<std::string> r = IPUtils::split(ip, '.');
        for (auto const& elem : r){
            if (elem == std::to_string(byte_value)){
                res.push_back(ip);
                break;
            }
        }
    }
    return res;
}


std::vector<std::string> IpFilter::get_ip_pool() const{
    return ip_pool;
}

IpFilter::~IpFilter() = default;
