#include "SimpleClient.h";
#include <iostream>
#include <string>

using namespace std;

int main() {

	Config config;
	config.host = "127.0.0.1";
	config.port = 54000;
	config.loggingEnabled = true;

	SimpleClient client{ config };

	while (true) {
		string packet;
		cout << "> ";
		getline(cin, packet);
		string res = client.transmit(packet);
		cout << res << endl;
	}

	return 0;
}