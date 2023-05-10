// commande operateur

// modes:

// -i set/remove invite-only channel
// -k set/remove channel key (pw)

// -t set/remove restriction of the topic command to channel operator
// -o give/take channel operator privilege

#include "Commands.hpp"

std::string	mode_invite_only(Channel &current)
{
	if (current.get_invite_only())
		cu
}