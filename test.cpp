#include "sender.hpp"
#include "receiver.hpp"

KeyType rk = {'l', 'a', 'l'};
std::string test_mess("mejdej");
std::vector<KeyType> keys;


int main() {
	Sender s(rk, 10);
	Receiver r(rk);

	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));
	r.receiveMess(s.sendMessage(test_mess));

}
