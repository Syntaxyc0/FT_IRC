#include <vector>
#include "Client.hpp"
#include "Replies.hpp"
#include <algorithm>

#define WHITESPACES " "


std::string	get_command(std::string line)
{
	std::string ret = "";
	size_t start = line.find_first_not_of(WHITESPACES);
	if (start != std::string::npos)
		ret = line.substr(start);
	size_t	end = line.find_first_of(WHITESPACES);
	if (end != std::string::npos)
		ret = ret.substr(0, end);
	ret = ret.substr(0, ret.find(' '));
	return (ret);
}

std::vector<std::string> parse(std::string input)
{
	std::vector<std::string> args;
	size_t index = 0;
	if (input.empty())
		return args;
	std::replace( input.begin(), input.end(), '\r', ' ');
	std::replace( input.begin(), input.end(), '\t', ' ');
	std::replace( input.begin(), input.end(), '\v', ' ');
	std::replace( input.begin(), input.end(), '\f', ' ');
	while ((index = input.find(WHITESPACES)) != std::string::npos)
	{
		args.push_back(input.substr(0, index));
		input.erase(0, index + 1);
	}
	if (!input.empty())
		args.push_back(input);
	return args;
}


