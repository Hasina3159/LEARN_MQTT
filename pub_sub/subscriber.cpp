#include "mqtt/async_client.h"
#include "subscriber.hpp"

void Callback::connected(const std::string &cause) {
    std::cout << "Connecté au broker" << std::endl;
}

void Callback::connection_lost(const std::string &cause) {
    std::cout << "Connexion perdu" << std::endl;
}

void Callback::message_arrived(mqtt::const_message_ptr message) {
    std::cout << "Topic : " << message->get_topic() << std::endl;
    std::cout << "Payload : " << message->to_string() << std::endl;
}

void Callback::delivery_complete(mqtt::delivery_token_ptr token) {
    std::cout << "Delivery completed!" << std::endl;
}