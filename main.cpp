#include "Client.hpp"
#include "Commands.hpp"
#include <iostream>
#include <string>
#include "Replies.hpp"

int main()
{
	// parse("space 1 2 3 4 5 6 6");
	// parse("tab\tsvuivbe  ji j h");
	// parse("\nnewline\n\n456\n\n\nvwevew vew vewv ");
	// parse("carriagereturn\rvyeuw vew vw eve\r\t wv wev we v");
	// parse("verticaltab\vvewv ve wv ewv\r\t ew ");
	// parse("formfeed\fvewvewv ewv\r\t ewv ");
	// parse("");

	Client	test(0, "127.0.0.1");
	std::vector<std::string> args = parse("vyuevywbuvbwuibve v fd f d f");
	user(&test, args);

}