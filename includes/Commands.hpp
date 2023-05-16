#ifndef COMMANDS_HPP

# define COMMANDS_HPP

# include <vector>
# include "Client.hpp"
# include "Server.hpp"

class	Client;

std::vector<std::string> parse(std::string input);
void	user(Client *client, std::vector<std::string> args);
bool	check_auth(Client *client);



#endif
