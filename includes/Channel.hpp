#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Replies.hpp"
# include <vector>

class Channel
{
	private:

		std::string			_name;
		std::string			_topic;
		std::vector<Client> _channelClients;	// Tout les client du channel sont dans _channelClient;
		std::vector<Client>	_operators;		// Les modo dont dans _channelClient && _operators;
		Client				_primordial;		// Le primordial est dans les 3

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
		void				set_channel_key(std::string password);
		void				set_user_limit(int limit, Client &user);
		void				set_restriction_TOPIC_cmd();

// GETTER
		bool				get_invite_only();
		bool				get_channel_key();
		bool				get_user_limit();
		bool				get_restriction_TOPIC_cmd();

// FUNCTION

		void				operator_privilege(Client &me, std::string target);
		int					is_primordial(std::string target);
		int					is_operator(std::string target);
		int					is_channelClient(std::string target);
		Client				find_client(std::string target);
		int					find_operator_index(std::string target);
};

#endif