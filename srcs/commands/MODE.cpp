//****************************************************//
//                   Commande MODE                    //
//****************************************************//

#include "Commands.hpp"

void	mode_manager(Client *client, std::vector<std::string> received, Server &server)
{
	if ( received[3] == "-i")
		mode_invite_only( server.find_channel( received[1] ), client );
	else if ( received[2] == "-k" )
		mode_channel_key( server.find_channel( received[1] ), client, received[2] );
	else if ( received[2] == "-t" )
		mode_restricion_topic_cmd( server.find_channel( received[1] ), client );
	else if ( received[2] == "-l" )
		mode_restricion_topic_cmd(server.find_channel( received[1] ), client);
	else if ( received[2] == "-o" )
		mode_operator_privilege(server.find_channel( received[1] ), client, received[2]);
}

// -i set/remove invite-only channel :
//  "/MODE -i" active le invite only, s'il est désactivé et inversement. 
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_invite_only(Channel *current, Client *user)
{
	current->set_invite_only();
	if (current->get_invite_only())
		user->send_reply("Invite-only mode is ON");
	else
		user->send_reply("Invite-only mode is OFF");
}

// -k set/remove channel key (pw)
// "/MODE -k (password)" active l'utilisation d'un mot de passe pour JOIN le channel s'il est précisé. Si il n'est pas précisé, il désactive la demande de mot de passe.
// Si un mot de passe est précisé alors qu'il y en avait déja un, il est alors modifié par le nouveau.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_channel_key(Channel *current, Client *user, std::string password)
{
	current->set_channel_key(password);
	if (current->get_channel_key())
		user->send_reply("Channel key is ON");
	else
		user->send_reply("Channel key is OFF");
}


// -t set/remove restriction of the topic command to channel operator
// "/MODE -t" active la restriction à tous les clients du Channel de changer le TOPIC. S'il était activé, le désactive.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_restricion_topic_cmd(Channel *current, Client *user)
{
	current->set_restriction_TOPIC_cmd();
	if (current->get_restriction_TOPIC_cmd())
		user->send_reply("Restriciton to TOPIC command is ON");
	else
		user->send_reply("Restriciton to TOPIC command is OFF");
}

// -l set/remove the user limit to Channel:
// "/MODE -l (nb)" active le nombre de Client admis dans le Channel si (nb) est précisé. Sinon, désactive la limite.
// Envoie un message indiquant l'état du mode au client. Par defaut [désactivé]

void	mode_limit_user(Channel *current, Client *user, int limit_nb)
{
	if (!limit_nb)
	{
		current->set_user_limit(0, user);
		user->send_reply("User limit is OFF");
		return;
	}
	std::string message = "User limit is ";
	std::stringstream ss;
	ss << limit_nb;

	message.append(ss.str());
	current->set_user_limit(limit_nb, user);
	user->send_reply(message);
}

// -o give/take channel operator privilege
// "MODE -o [target]" Si le client est au moins operator, il peut donner les pivilèges à n'importe qui.
// Seul le primordial peut retirer les privilèges. Envoie un message annonçant le nouvel operator, ou le client aayant été retrogradé.

void	mode_operator_privilege(Channel *current, Client *user, std::string target)
{
	current->operator_privilege(user, target);
} 