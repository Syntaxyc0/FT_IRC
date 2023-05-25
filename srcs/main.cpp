/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:43:12 by elise             #+#    #+#             */
/*   Updated: 2023/05/25 15:57:24 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// void errorin(int err, const std::string msg)
// {
//     if (err == 1)
//     {
//         std::cerr << msg << std::endl;
//         exit(EXIT_FAILURE);
//     }
// }

void	sig_handler(int)
{
	exit_state = 1;
}

//Code snippet
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }
    try{
        Server ircserv(argv[1], argv[2]);
        signal(SIGINT, &sig_handler);
        while (!ircserv.shut_down())
            ircserv.monitoring();
    }
    catch(std::exception &e)
    {
        std::cout << "/!\\ "<< e.what();
    }
}
