#include <string>
#include "SimpleConfiguration.h"


int main()
{
    SimpleConfiguration& config = SimpleConfiguration::getInstance();

    // Set configuration values
    config.setConfigValue("name", "John Doe");
    config.setConfigValue("age", 30);
    config.setConfigValue("isStudent", false);

    // Save configuration to file
    if (config.save("config.json")) {
        std::cout << "Configuration saved successfully." << std::endl;
    } else {
        std::cout << "Failed to save configuration." << std::endl;
    }

    // Load configuration from file
    if (config.load("config.json")) {
        std::cout << "Configuration loaded successfully." << std::endl;

    } else {
        std::cout << "Failed to load configuration." << std::endl;
        return -1;
    }


    SimpleConfiguration& configPreloaded = SimpleConfiguration::getInstance();
    // Get configuration values
    std::string name;
    int age;
    bool isStudent;
    std::string agef;

    if (configPreloaded.getConfigValue("name", name)) {
        std::cout << "Name: " << name << std::endl;
    }

    if (configPreloaded.getConfigValue("age", age)) {
        std::cout << "Age: " << age << std::endl;
    }

    //should fail
    if (configPreloaded.getConfigValue("age", agef)) {
        std::cout << "Age: " << age << std::endl;
    }

    if (configPreloaded.getConfigValue("isStudent", isStudent)) {
        std::cout << "Is Student: " << std::boolalpha << isStudent << std::endl;
    }

    return 0;
}
