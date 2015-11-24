#include <iostream>
#include <UriParser.hpp>

int main(int argc, const char *argv[])
{
    std::string haystack = "http://user:password@www.google.com:80/path?search&a[]=1&a[]=3";
    for (long long i = 0; i < 100000000; i++) {
        http::url parsed = http::ParseHttpUrl(haystack);
    }
    std::cout << std::endl;

    return 0;
}
