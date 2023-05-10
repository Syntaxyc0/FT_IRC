#include "Channel.hpp"

void	Channel::set_invite_only()
{
	if (_invite_only)
		_invite_only = 0;
	else
		_invite_only = 1;
}

void	Channel::set_channel_key(std::string password)
{
	if (!password.size())
		_channel_key = 0;
	else
	{
		_channel_key = 1;
		_password = password;
	}
}

void	Channel::set_user_limit(int limit)
{
	if (limit <= 0 && !_user_limit)
		throw ERR_NB_LIMIT();
	if (!_user_limit)
	{
		_user_limit = 1;
		_user_limit_nb = limit;
	}
}

bool	Channel::get_invite_only()
{
	return (_invite_only);
}

bool	Channel::get_channel_key()
{
	return (_channel_key);
}

bool	Channel::get_user_limit()
{
	return (_user_limit);
}