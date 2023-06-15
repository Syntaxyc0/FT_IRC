//****************************************************//
//                   Commande KICK                    //
//****************************************************//

#include "Commands.hpp"

// "/KICK [user.nickname]" Le client kick un autre client sur le channel sur lequel il est.
// Le client doit au moins etre operateur pour pouvoir kick, 
// il ne peut pas kick d'autre operateur (s'il essaie un message d'erreur lui sera retourné).
// Un message confirmant son action lui sera envoyé, ainsi qu'au client ayant été sujet au kick.

void	kick_command(Channel &current, Client &me, std::string target)
{
	if (!target.size())
	{
		me.send_message( ERR_NEEDMOREPARAMS( me.get_nickname(), "KICK" ) );
		return;
	}
	if ( !current.is_channelClient( target ) )
	{
		me.send_message( ERR_NOTONCHANNEL( target, current.get_name() ) );
	}
	if ( !current.is_operator( me.get_nickname() ) )
	{
		me.send_message( ERR_CHANOPRIVSNEEDED( me.get_nickname(), current.get_name() ) );
		return;
	}
	if ( current.is_operator( target ) )
	{
		me.send_message( ERR_CANTKICKOPE( target, current.get_name() ) );
		return;
	}

// remove client to channel's list
	current.kick_client( target );

// remove channel to client's _current_channel
	current.get_server()->find_client( target )->set_current_channel("");

	std::string message = target;
	target.append(" was kicked");
	me.send_message(message);
}
