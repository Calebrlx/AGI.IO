#include "dataStore.h"

DataStore::DataStore() {
    // Constructor implementation (if needed)
}

DataStore::~DataStore() {
    // Destructor implementation (if needed)
}

void DataStore::addData(const std::string &data) {
    store.push_back(data); // Adding data to the vector
}

std::vector<std::string> DataStore::getAllData() const {
    return store; // Returning all stored data
}

// Private member variable to store the data
std::vector<std::string> DataStore::store;
