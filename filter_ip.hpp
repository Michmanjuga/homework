#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct ip_addr
{
    uint8_t byte[4];
};

bool operator>(ip_addr, ip_addr);

std::vector<ip_addr> parse(std::istream&);
ip_addr convert(std::vector<std::string>);
std::vector<std::string> split(const std::string&, char);

std::vector<ip_addr> filter(std::vector<ip_addr>, uint8_t);
std::vector<ip_addr> filter(std::vector<ip_addr>, uint8_t, uint8_t);
std::vector<ip_addr> filter_any(std::vector<ip_addr>, uint8_t);
