#include "util.hpp"

class Sender {
    std::vector<KeyType> keys;
    KeyType rk;
    int keyCounter = 0;
    int keyShift = 5;

    void makeKeyChain(int rounds, KeyType rootKey)
    {
	    KeyType output;
	    KeyType input = rootKey;

	    // can be faster reusing the context
	    for(int i = 0; i < rounds; i++) {
		EVP_Digest(input.data(), SHA256_DIGEST_LENGTH, output.data(), nullptr, EVP_sha256(), nullptr);
		keys.push_back(output);
		input = output;
	    }
    }


public:
    Sender(KeyType _rk, int keyChainLen) : rk(_rk) {
	makeKeyChain(keyChainLen, rk);
    }

    Message sendMessage(std::string data) {
	Message mess;
	mess.data = data;
	mess.mac = sign(data, keys[keys.size() - keyCounter - 1]);

	std::string preamble = "SENDER: key of " + std::to_string(keyCounter + 1) + ". message";
	testPrint(preamble, keys[keys.size() - keyCounter - 1]);
	preamble = "SENDER: mac of " + std::to_string(keyCounter + 1) + ". message";
	testPrint(preamble, mess.mac);
	
	keyCounter++;

	if(keyCounter > keyShift) {
	    mess.disclosed_key = keys[keys.size() - keyCounter + keyShift];
	    preamble = "SENDER: disclosed key of " + std::to_string(keyCounter - keyShift) + ". message";
	    testPrint(preamble, mess.disclosed_key);
	}
	return mess;
    }
};


