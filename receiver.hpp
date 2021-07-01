
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

public:
    Receiver(KeyType _rk) : rk(_rk) {}

    void receiveMess(Message mess) {
	messages.emplace_back(mess);
	if(messages.size() > keyShift)
	    checkMess();
    }

    void checkMess() {}

};
