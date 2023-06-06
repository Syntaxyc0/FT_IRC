#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Replies.hpp"
# include "Server.hpp"
# include <vector>

class Server;
class Client;

class Channel
{
	private:

		std::string					_name;
		std::string					_topic;
		std::vector<std::string>	_channelClients;	// Tout les client du channel sont dans _channelClient;
		std::vector<std::string>	_operators;			// Les modo dont dans _channelClient && _operators;
		std::string					_primordial;		// Le primordial est dans les 3
		Server						*_server;

// MODE
		bool				_invite_only;			//set to 0 when init
		bool				_channel_key; 			//set to 0 when init
		std::string			_password;
		bool				_restriction_TOPIC_cmd;	//set to 0 when init
		bool				_user_limit; 			//set to 0 when init
		int					_user_limit_nb;

	public:

// SETTER
		void				set_invite_only();
		void				set_channel_key( std::string password );
		void				set_user_limit( int limit, Client &user );
		void				set_restriction_TOPIC_cmd();

// GETTER

		std::string			get_name();

		bool				get_invite_only();
		bool				get_channel_key();
		bool				get_user_limit();
		bool				get_restriction_TOPIC_cmd();

// FUNCTION

		void				operator_privilege( Client &me, std::string target );

		int					is_primordial( std::string target );
		int					is_operator( std::string target );
		int					is_channelClient( std::string target );

		int					find_client_index( std::string target );
		int					find_operator_index( std::string target );

		void				send_all( std::string message );
		void				kick_client( std::string user );
};

#endif