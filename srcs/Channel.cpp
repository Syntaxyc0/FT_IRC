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

void	Channel::set_user_limit(int limit, Client &user)
{
	if (limit < 0 && !_user_limit)
	{
		user.send_to_client("Error: User limit can't be less than 1");
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

std::string	Channel::get_name()
{
	return (_name);
}

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

Server *Channel::get_server()
{
	return (_server);
}

//****************************************************//
//                     Function                       //
//****************************************************//

void	Channel::operator_privilege(Client &me, std::string target)
{
	if ( !is_primordial(me.get_nickname()) || !is_operator(me.get_nickname()) )
	{
		me.send_to_client( ERR_CHANOPRIVSNEEDED( me.get_nickname(), _name ) );
		return;
	}

	if (is_primordial(target))
	{
		me.send_to_client( ERR_NOPRIMORDIAL( me.get_nickname(), _name ) );
		return;
	}

	if (!is_channelClient(target))
	{
		me.send_to_client("Client not found in this channel");
		return;
	}

	if (!is_operator(target))
	{
		_operators.erase( _operators.begin() + find_client_index( target ) );
		std::string message = target;
		message.append( " is now channel operator" );
		this->send_all( message );
	}

	if (is_primordial( me.get_nickname()) && is_operator(target) && me.get_nickname() != target )
	{
		std::string message2 = target;
		_operators.erase( _operators.begin() + find_operator_index( target )) ;
		message2.append( " is not anymore operator" );
		this->send_all( message2 );
	}
}

int Channel::is_channelClient( std::string target )
{
	for (int i = 0; i < (int)_channelClients.size(); i++)
		if (_channelClients.at(i) == target)
			return (1);
	return (0);
}

int	Channel::is_operator( std::string target )
{
	for (int i = 0; i < (int)_operators.size(); i++)
		if (_operators.at(i) == target)
			return (1);
	return (0);
}

int	Channel::is_primordial( std::string target )
{
	if (_primordial == target)
		return (1);
	return (0);
}

int	Channel::find_client_index( std::string target )
{
	for (int i = 0; i < (int)_channelClients.size(); i++)
	{
		if (_channelClients.at(i) == target)
			return (i);
	}
	return (-1);
}

int	Channel::find_operator_index( std::string target )
{
	for (int i = 0; i < (int)_operators.size(); i++)
	{
		if (_operators.at(i) == target)
			return (i);
	}
	return (-1);
}

void	Channel::send_all( std::string message )
{
	for (int i = 0; i < (int)_channelClients.size(); i++)
		_server->find_client( _channelClients.at(i) )->send_to_client( message );
}

void	Channel::kick_client( std::string user )
{
	_channelClients.erase(_channelClients.begin() + find_client_index( user ) );
}