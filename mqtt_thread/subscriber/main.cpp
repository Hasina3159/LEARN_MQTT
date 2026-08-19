#include "Callback.hpp"
#include "mqtt/async_client.h"
#include <chrono>
#include <iostream>

int subscribe(const std::string &server_adress, const std::string &client_id, const std::string &sub_topic, const std::string &will_topic) {
    const std::string WILL_MSG("[Client " + client_id + " #disconnected]");
    const int QOS = 1;

    mqtt::async_client client(server_adress, client_id);
    mqtt::message will(will_topic, WILL_MSG, QOS, true);

    Callback callback;
    client.set_callback(callback);

    mqtt::connect_options conn_opts = mqtt::connect_options_builder()
        .clean_session(true)
        .clean_start(false)
        .keep_alive_interval(std::chrono::seconds(30))
        .automatic_reconnect(std::chrono::seconds(5), std::chrono::seconds(5))
        .will(will)
        .finalize();

    try {
        client.connect(conn_opts)->wait();
        std::cout << "=== CONNECTED SUCCESSFULLY TO THE BROKER ===" << std::endl;
        client.subscribe(sub_topic, QOS)->wait();
        std::cout << "=== SUBSCRIBED SUCCESSFULLY TO " << sub_topic << std::endl;
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const mqtt::exception &exception) {
        std::cerr << "Error : " << exception.what() << std::endl;
        return (1);
    }
    return (0);
}

int main() {
    subscribe()
    return(0);
}