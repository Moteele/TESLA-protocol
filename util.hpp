#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <vector>
#include <string>
#include <array>
#include <iostream>

using KeyType = std::array<unsigned char, SHA256_DIGEST_LENGTH>;

struct Message {
    std::string data;
    KeyType mac;
    KeyType disclosed_key;
};

std::vector<unsigned char> to_uchar(std::string const& str)
{
    return std::vector<unsigned char>(str.data(), str.data() + str.length() + 1);
}

KeyType sign(std::string mess, KeyType key) {
	// TODO hash the key before using it
	KeyType output;
	HMAC(EVP_sha256(), key.data(), SHA256_DIGEST_LENGTH, to_uchar(mess).data(), mess.length(), output.data(), nullptr);

	return output;
}

void testPrint(std::string preamble, KeyType key) {
    std::cout << preamble << ":   ";
    for(unsigned int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
       printf("%02x", key.data()[i]);
    }
    std::cout << std::endl;

}

