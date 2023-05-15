#include "Replies.hpp"
#include "Client.hpp"

// 		/PASS <password>

// PASS ne requiert pas du client d'etre authentifie
// 

void    Pass(Client *client, std::vector<std::strings> args)
{
    if (args.empty())
    {
        client->send_reply(ERR_NEEDMOREPARAMS(Client->get_hostname(), "PASS"));
        return ;
    }
    else if (client->get_registered())
    {
        client->send_reply(ERR_ALREADYREGISTERED(Client->get_nickname()));
        return ;
    }
    //il faut checker que le mot de passe fourni correspond a celui du serveur, petit soucis, comment acceder au mdp du serveur?
    // else if (??)
    // {
    //     std::cerr<<ERR_PASSWDMISMATCH(client->get_hostname())<<std::endl;
    //     return ;
    // }
    
    //checker si on a nick user et pass d'effectuer, si oui changer le is_registered a 1

}