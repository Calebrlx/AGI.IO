#include "cacheManager.h"

CacheManager::CacheManager(DataStore* ds, NLP* nlpModule) : dataStore(ds), nlp(nlpModule) {}

std::string CacheManager::processInput(const std::string &input) {
    // Process the input through NLP
    std::string result = nlp->processInput(input);

    // If additional logic or caching is needed, it can be implemented here
    // Example: updateCache("lastInput", input);

    return result;
}

void CacheManager::updateCache(const std::string &key, const std::string &value) {
    cache[key] = value;
}

std::string CacheManager::retrieveFromCache(const std::string &key) {
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }
    // If the key is not in the cache, attempt to retrieve it from long-term storage
    return dataStore->retrieveData(key);
}
