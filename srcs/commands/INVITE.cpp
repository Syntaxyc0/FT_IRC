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
	if(current._server->find_client(target))
}
