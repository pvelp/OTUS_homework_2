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


void IPUtils::read_ip_pool(std::vector<std::array<uint8_t, 4>> &ip_pool) {
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            break;
        }

        std::vector<std::string> str_vector = IPUtils::split(line, 't');
        std::array<uint8_t, 4> r{};

        auto split_ip = [](const std::string &ip) {
            std::array<uint8_t, 4> tmp{};
            std::istringstream iss(ip);
            std::string byte;
            for (int i = 0; i < 4; ++i) {
                std::getline(iss, byte, '.');
                tmp[i] = std::stoi(byte);
            }
            return tmp;
        };
        r = split_ip(str_vector.at(0));
        ip_pool.push_back(r);
    }
}


void IPUtils::print(const std::vector<std::array<uint8_t, 4>> &l) {
    for (auto const &ip: l) {
        for (size_t i = 0; i < 4; i++) {
            if (i == 3) {
                std::cout << +ip.at(i) << std::endl;
            } else {
                std::cout << +ip.at(i) << '.';
            }
        }
    }
}


IpFilter::IpFilter(std::vector<std::array<uint8_t, 4>> ip_list) : ip_pool(std::move(ip_list)) {}


std::vector<std::array<uint8_t, 4>> IpFilter::filter(uint8_t first_byte) {
    std::vector<std::array<uint8_t, 4>> res;
    for (auto const &ip: ip_pool) {
        if (ip.at(0) == first_byte) {
            res.push_back(ip);
        }
    }
    return res;
}


std::vector<std::array<uint8_t, 4>> IpFilter::filter(uint8_t first_byte, uint8_t second_byte) {
    std::vector<std::array<uint8_t, 4>> res;
    for (auto const &ip: ip_pool) {
        if (ip.at(0) == first_byte && ip.at(1) == second_byte) {
            res.push_back(ip);
        }
    }
    return res;
}


std::vector<std::array<uint8_t, 4>> IpFilter::filter_any(uint8_t byte_value) {
    std::vector<std::array<uint8_t, 4>> res;
    for (auto const &ip: ip_pool) {
        for (auto const &elem: ip) {
            if (elem == byte_value) {
                res.push_back(ip);
                break;
            }
        }
    }
    return res;
}

std::vector<std::array<uint8_t, 4>> IpFilter::get_ip_pool() const {
    return ip_pool;
}

IpFilter::~IpFilter() = default;
