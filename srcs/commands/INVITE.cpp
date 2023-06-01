//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	invite_command(Channel &current, Client &me, std::string target)
{
	if ( !current.get_server()->find_client( target ) )
		me.send_to_client(ERR_NOSUCHCHANNEL(me.get_nickname(), current.get_name()));
	
	if ( !me.get_current_channel().size() )
		me.send_to_client(ERR_NOTONCHANNEL(me.get_nickname(), current.get_name()));
	
}
