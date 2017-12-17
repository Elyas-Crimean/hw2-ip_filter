#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

        // TODO reverse lexicographically sort

        std::sort(ip_pool.begin(),ip_pool.end(),[](std::vector<std::string> a,std::vector<std::string> b){
            auto i = 0u;
            auto s=a.size();
            while (i<s && (a.at(i).compare(b.at(i)) == 0)) {
                ++i;
            }
            if(i==s){
                --i;
            }
//            std::cout << a.at(0);std::cout << b.at(0);std::cout << std::endl;
            return (stoi(a.at(i)) > stoi(b.at(i)));
        });

        for(auto ip : ip_pool)
        {
            auto not_first=0;
            for(auto ip_part : ip)
            {
                if (not_first++)
                {
                    std::cout << ".";
                }
                std::cout << ip_part;
            }
            std::cout << std::endl;
        }


        // filter by first byte and output
        // ip = filter(1)
        for(auto ip : ip_pool)
        {
			if(stoi(ip.at(0)) == 1){
            auto not_first=0;
            for(auto ip_part : ip)
            {
                if (not_first++)
                {
                    std::cout << ".";
                }
                std::cout << ip_part;
            }
            std::cout << std::endl;
		}
        }

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        for(auto ip : ip_pool)
        {
			if(stoi(ip.at(0)) == 46 && stoi(ip.at(1)) == 70){
            auto not_first=0;
            for(auto ip_part : ip)
            {
                if (not_first++)
                {
                    std::cout << ".";
                }
                std::cout << ip_part;
            }
            std::cout << std::endl;
		}
        }

        // filter by any byte and output
        // ip = filter(46)
        for(auto ip : ip_pool)
        {
			if(stoi(ip.at(0)) == 46 || stoi(ip.at(1)) == 46 || stoi(ip.at(2)) == 46 || stoi(ip.at(3)) == 46){
            auto not_first=0;
            for(auto ip_part : ip)
            {
                if (not_first++)
                {
                    std::cout << ".";
                }
                std::cout << ip_part;
            }
            std::cout << std::endl;
		}
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
