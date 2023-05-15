#include "Channel.hpp"

//****************************************************//
//                      Setter                        //
//****************************************************//

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

void	Channel::set_restriction_TOPIC_cmd()
{
	if (_restriction_TOPIC_cmd)
		_restriction_TOPIC_cmd = 0;
	else 
		_restriction_TOPIC_cmd = 1;
}

void	Channel::set_user_limit(int limit)
{
	if (limit < 0 && !_user_limit)
		throw ERR_NB_LIMIT();
	if (limit)
	{
		_user_limit = 1;
		_user_limit_nb = limit;
	}
	else
		_user_limit = 0;
}

//****************************************************//
//                      Getter                        //
//****************************************************//

bool	Channel::get_invite_only()
{
	return (_invite_only);
}

bool	Channel::get_channel_key()
{
	return (_channel_key);
}

bool Channel::get_restriction_TOPIC_cmd()
{
	return (_restriction_TOPIC_cmd);
}

bool	Channel::get_user_limit()
{
	return (_user_limit);
}

//****************************************************//
//                     Function                       //
//****************************************************//

std::string	Channel::operator_privilege(Client &me, Client &target)
{
	if (!is_primordial(me) || !is_operator(me))
		throw NoPrivilege();

	if (is_primordial(target))
		throw Primordial();

	if (!is_operator(target))
	{
		_operators.push_back(target);
		std::string message = target.get_nickname();
		message.append(" ");
	}
	
}

int	Channel::is_primordial(Client &me)
{
	if (_primordial.get_nickname()== me.get_nickname())
		return (1);
	return (0);
}

int	Channel::is_operator(Client &me)
{
	for (int i = 0; i < (int)_operators.size(); i++)
		if (_operators.at(i).get_nickname() == me.get_nickname())
			return (1);
	return (0);
}