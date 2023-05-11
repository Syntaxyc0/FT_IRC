#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

class Channel
{
	private:

		std::string	_name;
		std::string	_topic;
		Client		*_channelClients;	// Tout les client du channel sont dans *_channelClient;
		Client		*_operators;		// Les modo dont dans *_channelClient && *_operators;
		Client		_primordial;		// Le primordial est dans les 3

// MODE
		bool		_invite_only;			//set to 0 when init
		bool		_channel_key; 			//set to 0 when init
		std::string _password;
		bool		_restriction_TOPIC_cmd;	//set to 0 when init
		bool		_user_limit; 			//set to 0 when init
		int			_user_limit_nb;

	public:

// SETTER
		void		set_invite_only();
		void		set_channel_key(std::string password);
		void		set_user_limit(int limit);
		void		set_restriction_TOPIC_cmd();

// GETTER
		bool		get_invite_only();
		bool		get_channel_key();
		bool		get_user_limit();
		bool		get_restriction_TOPIC_cmd();

	class ERR_NB_LIMIT : public std::exception{
		public:
		virtual const char* what() const throw(){
			return ("\033[1;31mError: limit of user can't be less than 1.\033[0m");
		}
	};

};

#endif