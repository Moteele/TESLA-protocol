
struct ReceiverMessage {
    Message mess;
    KeyType authKey;
    bool verified = false;
    ReceiverMessage(Message _mess) : mess(_mess) {}
};

class Receiver {
    std::vector<ReceiverMessage> messages;
    KeyType rk;
    unsigned int keyShift = 5;
    unsigned int counter = 0;

    void failed() {
	std::cout << "incorrect message\n";
    }

public:
    Receiver(KeyType _rk) : rk(_rk) {}

    void receiveMess(Message mess) {
	messages.emplace_back(mess);
	if(messages.size() > keyShift + 1) {
	    checkIntegrity();
	    checkKey();
	}
	counter++;
    }

    void checkIntegrity() {
	KeyType computedMAC = sign(messages[counter - keyShift].mess.data, messages[counter].mess.disclosed_key);

	std::string preamble = "RECEIVER: mac of " + std::to_string(counter + 1 - keyShift) + ". message";
	testPrint(preamble, computedMAC);

	if (computedMAC != messages[counter - keyShift].mess.mac)
	    failed();
	else
	    messages[counter].verified = true;

    }
    void checkKey() {
	KeyType output;
	EVP_Digest(messages[counter].mess.disclosed_key.data(), SHA256_DIGEST_LENGTH,
		output.data(), nullptr, EVP_sha256(), nullptr);
	std::string preamble = "RECEIVER: key of " + std::to_string(counter - keyShift) + ". message";
	testPrint(preamble, output);
	if(output != messages[counter - 1].mess.disclosed_key)
	    failed();
    }


};
