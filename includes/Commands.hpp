#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include "Client.hpp"
# include "Server.hpp"

class	Client;
class   Channel;

#include "Channel.hpp"
#include "Replies.hpp"
#include <sstream>

std::vector<std::string> parse(std::string input);
void	user(Client *client, std::vector<std::string> args);
bool	check_auth(Client *client);

void	kick_command(Channel &current, Client &me, std::string target);
void	invite_command(Channel &current, Client &me, std::string target);

// MODE COMMAND

void	mode_invite_only(Channel &current);
void	mode_channel_key(Channel &current, std::string password);
void	mode_restricion_topic_cmd(Channel &current);
void	mode_limit_user(Channel &current, int limit_nb);
void	mode_operator_privilege(Channel &current, Client &user, std::string target);

class NoMsg  : public std::exception{
	public:
	virtual const char* what() const throw(){
		return ("");
	}
};

#endif
