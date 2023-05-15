//****************************************************//
//                   Commande MODE                    //
//****************************************************//


#include "Commands.hpp"

// -i set/remove invite-only channel :
//  "/MODE -i" active le invite only, s'il est désactivé et inversement. 
// La fonction retourne un message indiquant l'état du mode. Par defaut [désactivé]

std::string	mode_invite_only(Channel &current)
{
	current.set_invite_only();
	if (current.get_invite_only())
		return ("Invite-only mode is ON");
	return ("Invite-only mode is OFF");
}

// -k set/remove channel key (pw)
// "/MODE -k (password)" active l'utilisation d'un mot de passe pour JOIN le channel s'il est précisé. Si il n'est pas précisé, il désactive la demande de mot de passe.
// Si un mot de passe est précisé alors qu'il y en avait déja un, il est alors modifié par le nouveau.
// La fonction retourne un message indiquant l'état du mode. Par defaut [désactivé]

std::string mode_channel_key(Channel &current, std::string password)
{
	current.set_channel_key(password);
	if (current.get_channel_key())
		return ("Channel key is ON");
	return ("Channel key is OFF");
}


// -t set/remove restriction of the topic command to channel operator
// "/MODE -t" active la restriction à tous les clients du Channel de changer le TOPIC. S'il était activé, le désactive.
// La fonction retourne un message indiquant l'état du mode. Par defaut [désactivé]

std::string mode_restricion_topic_cmd(Channel &current)
{
	current.set_restriction_TOPIC_cmd();
	if (current.get_restriction_TOPIC_cmd())
		return ("Restriciton to TOPIC command is ON");
	return ("Restriciton to TOPIC command is OFF");
}

// -l set/remove the user limit to Channel:
// "/MODE -l (nb)" active le nombre de Client admis dans le Channel si (nb) est précisé. Sinon, désactive la limite.
// La fonction retourne un message indiquant l'état du mode. Par defaut [désactivé]

std::string mode_limit_user(Channel &current, int limit_nb)
{
	if (!limit_nb)
	{
		current.set_user_limit(0);
		return ("User limit is OFF");
	}
	std::string message = "User limit is ";
	std::stringstream ss;
	ss << limit_nb;

	message.append(ss.str());
	current.set_user_limit(limit_nb);
	return (message);
}

// -o give/take channel operator privilege
// "MODE -o [target]"

// std::string	mode_give_operator_privilege(Channel &current, std::string target)
// {
// 	for (int i = 0; i <)
// }
