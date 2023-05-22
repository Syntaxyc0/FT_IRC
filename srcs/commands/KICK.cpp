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
		me.send( ERR_NEEDMOREPARAMS( me.get_nickname(), "KICK" ));
		return;
	}
	if ( !current.is_channelClient(target))
	{
		me.send( ERR_NOTONCHANNEL( target, current.get_name() ) )
	}
	if ( !current.is_operator( me.get_nickname() ) )
	{
		me.send( ERR_CHANOPRIVSNEEDED( me.get_nickname(), current.get_name() )) ;
		return;
	}
	if ( current.is_operator( target ) )
	{
		me.send( ERR_CANTKICKOPE( target, current.get_name() ) );
		return;
	}
	current.kick_client( target );
	std::string message = target;
	target.append(" was kicked");
	me.send(message);
}
