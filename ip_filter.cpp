#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <tuple>
#include <initializer_list>
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

struct Ip4
{
    Ip4(std::vector<std::string> ip_s){
        ip = std::make_tuple(std::stoi(ip_s.at(0)),
                             std::stoi(ip_s.at(1)),
                             std::stoi(ip_s.at(2)),
                             std::stoi(ip_s.at(3)));
    }
    std::tuple<uint8_t,uint8_t,uint8_t,uint8_t> ip;
    bool operator>(const Ip4& other) const {
        return ip > other.ip;
    }
};

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void ip_print(std::ostream &stream,
              const std::vector<Ip4> &ip_pool,
              std::function<bool (const Ip4 &a)> filter)
{
    for(auto ip4 : ip_pool)
    {
//        auto dot_skip=true;
        if(filter(ip4))
        {
/*            for(auto ip_part : ip)
            {
                if (dot_skip) {
					dot_skip = false;
                }else{
					stream << ".";
				}
                stream << ip_part;
            }*/
            stream << (int)std::get<0>(ip4.ip) <<'.'<<(int)std::get<1>(ip4.ip)
                   <<'.'<<(int)std::get<2>(ip4.ip)<<'.'<<(int)std::get<3>(ip4.ip);
            stream << std::endl;
        }
    }
}
/*
bool filter_begin(const Ip4 &ip, int b1)
{
    return std::get<0>(ip.ip) == b1;
}

bool filter_begin(const Ip4 &ip, int b1, int b2)
{
    return std::get<0>(ip.ip) == b1 && std::get<1>(ip.ip) == b2;
}
*/
template<int n>
bool filter_helper(const Ip4& ip, int byte)
{
    return std::get<n>(ip.ip) == byte;
}

template<typename ...Args>
bool filter_begin(const Ip4 &ip, int b1, Args... bytes)
{
    bool result = std::get<0>(ip.ip) == b1;
    constexpr int N = sizeof...(Args);
    if(result && N == 1) {
        int bs[] = {bytes...};
        result = filter_helper<N>(ip, bs[0]);
    }
    return result;
}


bool filter_any(const Ip4 &ip, int b)
{
    return std::get<0>(ip.ip) == b ||std::get<1>(ip.ip) == b ||std::get<2>(ip.ip) == b ||std::get<3>(ip.ip) == b;
}
                                                                         
int main(int argc, char const *argv[])
{
    try
    {
//        std::vector<std::vector<std::string> > ip_pool;
        std::vector<Ip4> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        //reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),std::greater<Ip4>());
        ip_print(std::cout,ip_pool,[](const Ip4& ){return true;});

        // filter by first byte and output
        //ip = filter(1)
        ip_print(std::cout,ip_pool,[](const Ip4 &a){return filter_begin(a, 1);});

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        ip_print(std::cout,ip_pool,[](const Ip4 &a){return filter_begin(a, 46, 70);});

        // filter by any byte and output
        // ip = filter(46)
        ip_print(std::cout,ip_pool,[](const Ip4 &ip){return filter_any(ip,46);});
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
