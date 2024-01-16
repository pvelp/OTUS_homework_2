//#pragma once

#include <vector>
#include <string>

int version();

class IPUtils {
public:
    static void read_ip_pool(std::vector<std::string> &ip_pool);

    static std::vector<std::string> split(const std::string &str, char d);

    static std::vector<int> convertIp(const std::string &ip);

    static void print(const std::vector<std::string>& list);

    static bool compareIp(const std::string &a, const std::string &b);
};


class IpFilter {
private:
    std::vector<std::string> ip_pool;
public:
    explicit IpFilter(std::vector<std::string> ip_list);

    std::vector<std::string> filter(uint8_t first_byte);

    std::vector<std::string> filter(uint8_t first_byte, uint8_t second_byte);

    std::vector<std::string> filter_any(uint8_t byte_value);

    std::vector<std::string> get_ip_pool() const;

    ~IpFilter();
};