#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Channel.hpp"
#include <sstream>

std::vector<std::string> parse(std::string input);
void	user(Client *client, std::vector<std::string> args);

// MODE COMMAND

std::string	mode_invite_only(Channel &current);
std::string mode_channel_key(Channel &current, std::string password);
std::string mode_restricion_topic_cmd(Channel &current);
std::string mode_limit_user(Channel &current, int limit_nb);

#endif
