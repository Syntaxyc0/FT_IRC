#include <vector>
#include "Client.hpp"
#include "Replies.hpp"

#define WHITESPACES "\t\n\r\v\f "


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
	std::string tmp;
	std::stringstream	rest(input);
	while (rest >> tmp )
		args.push_back(tmp);
	return args;
}

// //exceptions possibles
// -la commande n'existe pas
// -l'utilisateur n'est pas bien authentifie
// -l'utilisateur n'a pas les droits

// => retour exception propre a chaque commande

// l'authentification complete /PASS /USER /NICK avant ca pas d'autres commandes 


