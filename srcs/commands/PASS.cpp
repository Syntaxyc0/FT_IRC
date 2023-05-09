#include "Replies.hpp"
#include "Client.hpp"

// 		/PASS <password>

// PASS ne requiert pas du client d'etre authentifie
// 

void    Pass(Client *client, std::vector<std::strings> args)
{
    if (args.empty())
    {
        std::cerr<<ERR_NEEDMOREPARAMS(Client->get_hostname(), "PASS")<<std::endl;
        return ;
    }
    else if (client->get_registered())
    {
        std::cerr<<ERR_ALREADYREGISTERED(Client->get_nickname())<<std::endl;
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