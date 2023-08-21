#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <string>
#include <vector>

class DataStore {
public:
    DataStore();
    ~DataStore();
    void addData(const std::string &data);
    std::vector<std::string> getAllData() const;
};

#endif // DATA_STORE_H
