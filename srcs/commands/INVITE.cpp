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
	{
		me.send_to_client( ERR_NOSUCHCHANNEL( me.get_nickname(), current.get_name() ) );
		return;
	}
	if ( !me.get_current_channel().size() )
	{
		me.send_to_client( ERR_NOTONCHANNEL( me.get_nickname(), current.get_name() ) );
		return;
	}
	if ( !current.is_operator( me.get_nickname() ) )
	{
		me.send_to_client( ERR_CHANOPRIVSNEEDED( me.get_nickname(), current.get_name() ) );
		return;
	}
	if ( current.is_channelClient( target ) )
	{
		me.send_to_client( ERR_USERONCHANNEL( me.get_nickname(), target,  current.get_name() ) );
		return;
	}

	current.add_client( target );
	current.get_server()->find_client( target ).
}
