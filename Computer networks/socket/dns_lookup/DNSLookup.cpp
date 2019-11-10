#include <netinet/in.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <string>

struct in_addr IPv4addr;
struct hostent *host;

int main(int argc, char** argv) {
	char hostname[50] = "localhost";
	bool localhost = false;

	if(argc == 1) {
		host = gethostbyname(hostname);
		localhost = true;
	}

	if (argc > 2) {
		std::cout << std::endl << "Usage :" << std::endl;
		std::cout << "./DNSLookup [hostname/IP Address]" << std::endl << std::endl;
		return(1);
	}

	if(!localhost) {
		std::strcpy(hostname, argv[1]);
		if(hostname[0] >= 48 && hostname[0] <= 57) {
			inet_pton(AF_INET, hostname, &IPv4addr);
			host = gethostbyaddr(&IPv4addr, sizeof(IPv4addr), AF_INET);   //get hostent by IP address
		}
		else
			host = gethostbyname(hostname);  //get hostent by  domain name

		if(host == NULL) { 
			std::cout << "undefined hostname : " <<  hostname << std::endl; 
			return(2);
		}
	}

	std::cout << "------- Hostname info -------" << std::endl << std::endl;
	std::cout << "Name : " <<  host->h_name << std::endl;
	
	for (int i = 0; host->h_aliases[i]; ++i)
		std::cout << "Aliases : " << host->h_aliases[i] << std::endl;

	std::cout << "Address type : " << host->h_addrtype << std::endl;
	std::cout << "Length : " << host->h_length << std::endl;
	std::cout << "Address : " << inet_ntoa(*(struct in_addr*)host->h_addr) << std::endl;

	return (0);
}