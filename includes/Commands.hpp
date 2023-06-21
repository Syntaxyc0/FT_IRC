#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include "Client.hpp"
# include "Server.hpp"
# include "Channel.hpp"
# include "Replies.hpp"
# include <sstream>
# include <cstdlib>

class	Client;
class   Channel;

enum state
{
	NOT_REGISTERED = 0,
	PASS_CHECKED = 1,
	NICK_CHECKED = 2,
	REGISTERED = 3,
	DISCONNECTED = 4
};


class	Client;
class   Channel;
class	Server;


std::vector<std::string> parse(std::string input);
bool					check_auth(Client *client);

void		kick_command( Channel &current, Client &me, std::string target );
void		invite_command( Client *client, std::vector<std::string> received, Server &server );
bool		invite_error( Client *client, std::vector<std::string> received, Server &server );
void		join_command( Client *client, std::vector<std::string> received, Server &server );
bool		join_error( Client *client, std::vector<std::string> received, Server &server );
std::string	join_message_reply( std::vector<std::string> received, Server &server );

// MODE COMMAND

void	mode_manager(Client *client, std::vector<std::string> received, Server &server);
int		mode_error(Client *client, std::vector<std::string> received, Server &server);
void	mode_invite_only(Channel *current, Client *user, char sign);
void	mode_channel_key(Channel *current, Client *user, std::vector<std::string> received);
void	mode_restricion_topic_cmd(Channel *current, Client *user, std::vector<std::string> received);
void	mode_limit_user(Channel *current, Client *user, std::vector<std::string> received);
void	mode_operator_privilege(Channel *current, Client *user, std::string target);


void	User(Client *client, std::vector<std::string> args, Server &serv);
void	Nick(Client *client, std::vector<std::string> args, Server &serv);
void    Pass(Client *client, std::vector<std::string> args, Server &serv);
void	Privmsg(Client *client, std::vector<std::string> args, Server &serv);
void	Quit(Client *client, std::vector<std::string> args, Server &serv);
void	Ping(Client *client, std::vector<std::string> args, Server &server);
void	Topic(Client *client, std::vector<std::string> args, Server &serv);
void	Part(Client *client, std::vector<std::string> args, Server &serv);



class NoMsg  : public std::exception{
	public:
	virtual const char* what() const throw(){
		return ("");
	}
};

#endif
