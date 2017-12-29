#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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
              const std::vector<std::vector<std::string>> &ip_pool,
              std::function<bool (const std::vector<std::string> &a)> filter)
{
    for(auto ip : ip_pool)
    {
        auto dot_skip=true;
        if(filter(ip))
        {
            for(auto ip_part : ip)
            {
                if (dot_skip) {
					dot_skip = false;
                }else{
					stream << ".";
				}
                stream << ip_part;
            }
            stream << std::endl;
        }
    }
}

bool filter_begin(const std::vector<std::string> &ip, int b1)
{
    return std::stoi(ip.at(0)) == b1;
}

bool filter_begin(const std::vector<std::string> &ip, int b1, int b2)
{
    return std::stoi(ip.at(0)) == b1 && std::stoi(ip.at(1)) == b2;
}

bool filter_any(const std::vector<std::string> &ip, int b)
{
    return any_of(ip.begin(),ip.end(),[b](std::string ip_part){return std::stoi(ip_part) == b;}) ;
}
                                                                         
int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        //reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),[](std::vector<std::string> a,std::vector<std::string> b){
            auto i = 0u;
            auto s=a.size();
            while (i<s && (a.at(i) == b.at(i))) {
                ++i;
            }
            if(i==s){
                --i;
            }
            return (stoi(a.at(i)) > stoi(b.at(i)));
        });
        ip_print(std::cout,ip_pool,[](const std::vector<std::string>& ){return true;});

        // filter by first byte and output
        //ip = filter(1)
        ip_print(std::cout,ip_pool,[](const std::vector<std::string> &a){return filter_begin(a, 1);});

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        ip_print(std::cout,ip_pool,[](const std::vector<std::string> &a){return filter_begin(a, 46, 70);});

        // filter by any byte and output
        // ip = filter(46)
        ip_print(std::cout,ip_pool,[](const std::vector<std::string> &ip){return filter_any(ip,46);});
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
