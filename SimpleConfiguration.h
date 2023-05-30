#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class SimpleConfiguration {
private:
    json configJson;
    std::string configFilePath;

    SimpleConfiguration() {}  // Private constructor to prevent direct instantiation

public:
    SimpleConfiguration(const SimpleConfiguration&) = delete;  // Delete copy constructor
    SimpleConfiguration& operator=(const SimpleConfiguration&) = delete;  // Delete assignment operator

    static SimpleConfiguration& getInstance() {
        static SimpleConfiguration instance;
        return instance;
    }

    bool load(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cout << "Failed to open configuration file: " << filePath << std::endl;
            return false;
        }

        try {
            file >> configJson;
            configFilePath = filePath;
            return true;
        } catch (const std::exception& e) {
            std::cout << "Error parsing configuration file: " << e.what() << std::endl;
            return false;
        }
    }

    bool save(const std::string& filePath) {
        if (filePath.empty()) {
            std::cout << "No configuration file path specified." << std::endl;
            return false;
        }

        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cout << "Failed to open configuration file for writing: " << filePath << std::endl;
            return false;
        }

        try {
            file << std::setw(4) << configJson;
            return true;
        } catch (const std::exception& e) {
            std::cout << "Error writing configuration file: " << e.what() << std::endl;
            return false;
        }
    }

    template <typename T>
    void setConfigValue(const std::string& key, const T& value) {
        configJson[key] = value;
    }

    template <typename T>
    bool getConfigValue(const std::string& key, T& value) {
        if (configJson.find(key) != configJson.end()) {
            try {
                using ValueType = typename std::decay<T>::type;
                if constexpr (std::is_same_v<ValueType, json>) {
                    value = configJson[key];
                } else if constexpr (std::is_same_v<ValueType, std::string>) {
                    value = configJson[key].get<std::string>();
                } else if constexpr (std::is_same_v<ValueType, int>) {
                    value = configJson[key].get<int>();
                } else if constexpr (std::is_same_v<ValueType, bool>) {
                    value = configJson[key].get<bool>();
                } else if constexpr (std::is_same_v<ValueType, float>) {
                    value = configJson[key].get<float>();
                } else if constexpr (std::is_same_v<ValueType, double>) {
                    value = configJson[key].get<double>();
                } else {
                    // Handle unsupported type here
                    return false;
                }
                return true;
            } catch (const std::exception& e) {
                std::cout << "Error retrieving configuration value: " << e.what() << std::endl;
            }
        }
        return false;
    }

    bool valueExists(const std::string& key) {
        return (configJson.find(key) != configJson.end());
    }
};
