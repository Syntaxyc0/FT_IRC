#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Channel.hpp"

std::vector<std::string> parse(std::string input);
void	user(Client *client, std::vector<std::string> args);

// MODE COMMAND

std::string	mode_invite_only(Channel &current);


#endif
