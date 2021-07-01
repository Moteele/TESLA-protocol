#include "sender.hpp"
#include "receiver.hpp"

KeyType rk = {'l', 'a', 'l'};
std::string test_mess("mejdej");
std::vector<KeyType> keys;


int main() {
	Sender sender(rk, 2);
	sender.sendMessage(test_mess);
	sender.sendMessage(test_mess);

}
