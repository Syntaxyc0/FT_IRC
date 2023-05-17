#include "Channel.hpp"

// !!!! la fonction membre user.send n'existe pas, à changer lorsque
// qu'une fonction d'envoie de message au client sera implementé !!!!

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

void	Channel::set_user_limit(int limit, Client &user)
{
	if (limit < 0 && !_user_limit)
	{
		user.send("Error: User limit can't be less than 1");
		return;
	}
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

void	Channel::operator_privilege(Client &me, std::string target)
{
	if (!is_primordial(me.get_nickname()) || !is_operator(me.get_nickname()))
	{
		me.send(ERR_CHANOPRIVSNEEDED(me.get_nickname(), this->_name));
		return;
	}

	if (is_primordial(target))
	{
		me.send(ERR_NOPRIMORDIAL(me.get_nickname(), this->_name));
		return;
	}

	if (!is_channelClient(target))
	{
		me.send("Client not found in this channel");
		return;
	}

	if (!is_operator(target))
	{
		_operators.push_back(find_client(target));
		std::string message = target;
		message.append(" is now channel operator");
		this->send_all(message);
	}

	if (is_primordial(me.get_nickname()) && is_operator(target) && me.get_nickname() != target)
	{
		std::string message2 = target;
		_operators.erase(_operators.begin() + find_operator_index(target));
		message2.append(" is not anymore operator");
		this->send_all(message2);
	}
}

int Channel::is_channelClient(std::string target)
{
	for (int i = 0; i < (int)_channelClients.size(); i++)
		if (_channelClients.at(i).get_nickname() == target)
			return (1);
	return (0);
}

int	Channel::is_operator(std::string target)
{
	for (int i = 0; i < (int)_operators.size(); i++)
		if (_operators.at(i).get_nickname() == target)
			return (1);
	return (0);
}

int	Channel::is_primordial(std::string target)
{
	if (_primordial.get_nickname() == target)
		return (1);
	return (0);
}

Client	Channel::find_client(std::string target)
{
	for (int i = 0; i < (int)_channelClients.size(); i++)
	{
		if (_channelClients.at(i).get_nickname() == target)
			return (_channelClients.at(i));
	}
}

int	Channel::find_operator_index(std::string target)
{
	for (int i = 0; i < (int)_operators.size(); i++)
	{
		if (_operators.at(i).get_nickname() == target)
			return (i);
	}
}