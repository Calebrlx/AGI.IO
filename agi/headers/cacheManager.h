#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

#include "dataStore.h"
#include "nlp.h"
#include <string>
#include <unordered_map>

class CacheManager {
public:
    CacheManager(DataStore* dataStore, NLP* nlp);
    std::string processInput(const std::string &input);
    void updateCache(const std::string &key, const std::string &value);
    std::string retrieveFromCache(const std::string &key);

private:
    DataStore* dataStore;
    NLP* nlp;
    std::unordered_map<std::string, std::string> cache;
};

#endif // CACHE_MANAGER_H
