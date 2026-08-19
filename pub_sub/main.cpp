#include "subscriber.hpp"
#include "mqtt/async_client.h"
#include <chrono>

int main () {
    const std::string SERVER_ADRESS("tcp://localhost:1883");
    const std::string CLIENT_ID("subscriber_client");
    const std::string SUB_TOPIC("trano/#");
    const std::string WILL_TOPIC("trano/will");
    const std::string WILL_MSG(CLIENT_ID + ": [Disconnected]");
    const int QOS = 1;

    mqtt::async_client client(SERVER_ADRESS, CLIENT_ID);
    mqtt::message will(WILL_TOPIC, WILL_MSG);

    Callback callback;
    client.set_callback(callback);

    mqtt::connect_options conn_opt = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(30))
        .clean_start(false)
        .clean_session(true)
        .automatic_reconnect(std::chrono::seconds(5), std::chrono::seconds(10))
        .will(will)
        .finalize();

    try {
        client.connect(conn_opt)->wait();
        client.subscribe(SUB_TOPIC, QOS)->wait();

        std::cout << "Abonné à : " << SUB_TOPIC << std::endl;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (mqtt::exception &exception) {
        std::cerr << "Erreur : " << exception.what() << std::endl;
    }


    return (0);
}