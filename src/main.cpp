#include "io.h"
#include "dataStore.h"
#include <iostream>

int main() {
    IO io;
    DataStore dataStore;
    
    std::string userInput = io.promptInput();
    dataStore.addData(userInput);

    std::cout << "You typed: " << userInput << std::endl;

    // Retrieving and printing all stored data
    std::vector<std::string> allData = dataStore.getAllData();
    std::cout << "All data in store:\n";
    for (const std::string &data : allData) {
        std::cout << data << std::endl;
    }

    return 0;
}