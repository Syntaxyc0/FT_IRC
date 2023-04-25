#ifndef	CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>


class	Client
{
	private:
			_username;
			_nickname;
	public:
			void	set_nickname(std::string name);
			void	set_username(std::string name);
};

#endif