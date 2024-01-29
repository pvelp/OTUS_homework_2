#include <vector>
#include <string>
#include <array>

int version();

class IPUtils
{
public:
    static void read_ip_pool(std::vector<std::array<uint8_t, 4>> &ip_pool);

    static std::vector<std::string> split(const std::string &str, char d);

    static void print(const std::vector<std::array<uint8_t, 4>> &l);
};

class IpFilter
{
private:
    std::vector<std::array<uint8_t, 4>> ip_pool;

public:
    explicit IpFilter(std::vector<std::array<uint8_t, 4>> ip_list);

    std::vector<std::array<uint8_t, 4>> filter(uint8_t first_byte);

    std::vector<std::array<uint8_t, 4>> filter(uint8_t first_byte, uint8_t second_byte);

    std::vector<std::array<uint8_t, 4>> filter_any(uint8_t byte_value);

    std::vector<std::array<uint8_t, 4>> get_ip_pool() const;

    ~IpFilter();
};