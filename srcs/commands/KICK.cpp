//****************************************************//
//                   Commande KICK                    //
//****************************************************//

#include "Commands.hpp"

// "/KICK [user.nickname]" L'e client doit au moins etre operateur pour pouvoir kick, 
// il ne peut kick d'autre operateur (s'il essaie un message d'erreur lui sera retrouné).
// Un message confirmant son action lui sera envoyé, ainsi qu'au client ayant été sujet au kick.

void	kick_command(Channel &current, Client &me, Client &target)
{

	if ( !current.is_operator( me.get_nickname() ) )
	{
		me.send(ERR_CHANOPRIVSNEEDED(me, current));
		return;
	}
	if ( current.is_operator ( target.get_nickname() ) )
	{
		me.send(ERR_CANTKICKOPE(target, current));
		return;
	}
	current.	
}
