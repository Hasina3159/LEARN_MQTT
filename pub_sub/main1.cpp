#include "subscriber.hpp"
#include <iostream>
#include <chrono>

int main() {
    const std::string SERVER_ADRESS("tcp://127.0.0.1:1883");
    const std::string CLIENT_ID("subscriber_client");
    const std::string TOPIC("trano/#");
    const std::string WILL_TOPIC("trano/pub");
    const std::string WILL_MSG("[Disconnected]");
    const int QOS = 1;

    mqtt::async_client client(SERVER_ADRESS, CLIENT_ID);
    mqtt::message will(WILL_TOPIC, WILL_MSG, QOS, true);
    Callback callback;
    client.set_callback(callback);

    mqtt::connect_options conn_opts = mqtt::connect_options_builder()
    .keep_alive_interval(std::chrono::seconds(20))
    .clean_start(false)
    .will(will)
    .automatic_reconnect(std::chrono::seconds(5), std::chrono::seconds(30))
    .finalize();

    try {
        client.connect(conn_opts)->wait();
        client.subscribe(TOPIC, QOS)->wait();

        std::cout << "Abonné a : " << TOPIC << std::endl;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const mqtt::exception &exception) {
        std::cerr << "Erreur : " << exception.what() << std::endl;
        return (1);
    }

    return (0);
}
