//****************************************************//
//                   Commande MODE                    //
//****************************************************//

#include "Commands.hpp"

void	mode_manager(Client *client, std::vector<std::string> received, Server &server)
{
	if ( mode_error(client, received, server))
		return ;

	for (int i = 1; i < (int)received.size(); i++)
	{
		if ( received[i][1] == 'i' )
			mode_invite_only( server.find_channel( received[1] ), client, received[i][0]);
		else if ( received[i][1] == 'k' )
			i += mode_channel_key( server.find_channel( received[1] ), client, received , i);
		else if ( received[i][1] == 't' )
			mode_restricion_topic_cmd( server.find_channel( received[1] ), client, received,  i );
		else if ( !strncmp("-l", received[i].c_str(), 2) )
			mode_limit_user( server.find_channel( received[1] ), client, received );
		else if ( received[i][1] == 'o' )
			mode_operator_privilege(server.find_channel( received[1] ), client, received[2]);
	}
}

int	mode_error(Client *client, std::vector<std::string> received, Server &server)
{

}

// -i set/remove invite-only channel :
//  "/MODE -i" désactive invite-only mode.
//  "/MODE +i" active invite-only mode.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

int	mode_invite_only(Channel *current, Client *user, char sign)
{
	if ( sign == '+' )
	{
		current->set_invite_only(1);
		user->send_message_in_channel( current->get_name(), "Invite-only mode is ON" );
	}
	else if ( sign == '-' )
	{
		current->set_invite_only(0);
		user->send_message_in_channel( current->get_name(), "Invite-only mode is OFF" );
	}
}

// -k set/remove channel key (pw)
// "/MODE -k" desactive le channel-key;
// "/MODE +k [password]" active le channel-key, ou change le mdp si deja activé. 
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

int	mode_channel_key( Channel *current, Client *user, std::vector<std::string> received, int i)
{
	if ( received[i][0] == '-' )
	{
		current->set_channel_key(0, "");
		user->send_message_in_channel( current->get_name(), "Channel key is OFF" );
		return (0);
	}
	else if ( current->get_channel_key() && received[i][0] == '+' )
	{
		current->set_channel_key(1, received[i + 1]);
		user->send_message_in_channel( current->get_name(), "Channel key has been changed" );
	}
	else if ( !current->get_channel_key() && received[i][0] == '+' )
	{
		current->set_channel_key(1 , received[i + 1]);
		user->send_message_in_channel( current->get_name(), "Channel key is ON" );
	}
	return (1);
}


// -t set/remove restriction of the topic command to channel operator
// "/MODE -t" désactive la restriction à tous les clients du Channel de changer le TOPIC.
// "/MODE +t" active la restriction à tous les clients du Channel de changer le TOPIC.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_restricion_topic_cmd(Channel *current, Client *user, std::vector<std::string> received, int i)
{
	if ( received[i][0] == '-' )
	{
		current->set_restriction_TOPIC_cmd(0);
		user->send_message_in_channel( current->get_name(), "Restriction to TOPIC command is ON" );
	}
	else
	{
		current->set_restriction_TOPIC_cmd(1);
		user->send_message_in_channel( current->get_name(), "Restriction to TOPIC command is OFF" );
	}
}

// -l set/remove the user limit to Channel:
// "/MODE -l" désactive le nombre de Client admis dans le Channel.
// "/MODE -l [nb]" active le nombre de Client admis dans le Channel, ou change le nombre si deja activé.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_limit_user(Channel *current, Client *user, std::vector<std::string> received)
{
	std::string message = "PRIVMSG ";
	message += current->get_name() + " :";

	if ( user_limit_int_number( received[2] ) )
	{
		int limit_nb = atoi( received[2].c_str() );
		if ( limit_nb < (int)current->get_channelClients().size() )
			user->send_message( message += "Error : the limit cannot be less than the current number of users in that channel");
		else
		{
			current->set_user_limit( limit_nb, user , current->get_name());
			user->send_message( message += "User limit is " + received[2].erase( 0, 2 ) );
		}
	}
	else 
	{
		current->set_user_limit( -1, user, current->get_name());
		user->send_message( message += "User limit is OFF" );
	}
}

int	user_limit_int_number(std::string l)
{
	int i;

	if ( l.size() == 2 )
		return (0);
	else
	{
		l.erase( 0, 2 );
		i = atoi( l.c_str() );
	}
	return ( i );
}

// -o give/take channel operator privilege
// "MODE -o [target]" Si le client est au moins operator, il peut donner les pivilèges à n'importe qui.
// Seul le primordial peut retirer les privilèges. Envoie un message annonçant le nouvel operator, ou le client aayant été retrogradé.

void	mode_operator_privilege(Channel *current, Client *user, std::string target)
{
	current->operator_privilege(user, target);
} 