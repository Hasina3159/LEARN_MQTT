#include "Callback.hpp"
#include <iostream>


void Callback::connected(const std::string &cause) {
    std::cout << "[CONNECTED] -> " << cause << std::endl;
}

void Callback::connection_lost(const std::string &cause) {
    std::cout << "[CONNECTION LOST] -> " << cause << std::endl;
}

void Callback::delivery_complete(mqtt::delivery_token_ptr token) {
    std::cout << "[Delivered " << token->get_topics() \
    << " From : " << token->get_client() << "] | ID : " \
    << token->get_message_id() << " | Payload : [" << token->get_message() << "]" << std::endl;
}

void Callback::message_arrived(mqtt::const_message_ptr message) {

}
