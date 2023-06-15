#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include "Client.hpp"
# include "Server.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include <sstream>

class	Client;
class   Channel;
class	Server;


std::vector<std::string> parse(std::string input);
void	user(Client *client, std::vector<std::string> args);
bool	check_auth(Client *client);

void	kick_command(Channel &current, Client &me, std::string target);
void	invite_command(Channel &current, Client &me, std::string target);
void	join_command(Client *client, std::vector<std::string> received, Server &server);
bool	join_error( Client *client, std::vector<std::string> received, Server &server );

// MODE COMMAND

void	mode_manager(Client *client, std::vector<std::string> received, Server &server);
void	mode_invite_only(Channel *current, Client *user);
void	mode_channel_key(Channel *current, Client *user, std::string password);
void	mode_restricion_topic_cmd(Channel *current, Client *user);
void	mode_limit_user(Channel *current, Client *user, int limit_nb);
void	mode_operator_privilege(Channel *current, Client *user, std::string target);

class NoMsg  : public std::exception{
	public:
	virtual const char* what() const throw(){
		return ("");
	}
};

#endif
