- Goals:

The primary goal of this project is to create a custom voice assistant with the ability to process natural language input, execute basic commands, and integrate advanced AI models for handling complex requests. The system is designed to be modular, allowing for easy expansion and integration with other tools and services.

  
- Architecture

The architecture consists of several key components, each serving a specific role:

1. IO (Input/Output)**:
    - Handles user input and output interactions.
    - Communicates user input to the Cache Manager for processing.

2. NLP (Natural Language Processing)**:
    - Processes natural language input for basic AI functionality.
    - May delegate more complex tasks to advanced AI models, such as ChatGPT-4.

3. Cache Manager**:
    - Acts as a central orchestrator, managing communication between IO, DataStore, and NLP.
    - Caches recent memory and handles requests to DataStore for long-term storage.

4. DataStore**:
    - Manages long-term data storage, including LSTM (Long Short-Term Memory) functionality.
    - Communicates exclusively with the Cache Manager.

5. Optional Python Scripts**:
    - Used for model training and complex AI logic.
    - Can integrate with deep learning frameworks like TensorFlow or PyTorch.


- Implementation

The project is primarily implemented in C++ with potential Python components for deep learning. The codebase is organized into separate `.cpp` and `.h` files for each component, creating a clean separation of concerns.


- Logic

1. Initialization**: `main.cpp` initializes all components.
2. User Interaction**: `io.cpp` receives user input and passes it to `cacheManager.cpp`.
3. Processing**: `cacheManager.cpp` sends input to `nlp.cpp` for processing. If required, complex logic is delegated to Python scripts.
4. Storage**: Processed data may be stored in `dataStore.cpp` through `cacheManager.cpp`.
5. Response**: Final processed output is sent back to the user through `io.cpp`.


- Directory Structure

project_root/
|-- src/
|   |-- io.cpp
|   |-- dataStore.cpp
|   |-- cacheManager.cpp
|   |-- nlp.cpp
|   |-- main.cpp
|-- headers/
|   |-- io.h
|   |-- dataStore.h
|   |-- cacheManager.h
|   |-- nlp.h
|-- README.txt



`src/io.cpp` & `headers/io.h`
Class: `IO`
- Methods:
  - `std::string promptInput()`: Prompts the user to type something and returns the user's input as a string.

`src/dataStore.cpp` & `headers/dataStore.h`
Class: `DataStore`
- Methods:
  - `void storeData(const std::string &data)`: Handles long-term data storage.
  - `std::string retrieveData(const std::string &key)`: Retrieves data based on a specific key or identifier.

`src/cacheManager.cpp` & `headers/cacheManager.h`
Class: `CacheManager`
- Methods:
  - `CacheManager(DataStore* dataStore, NLP* nlp)`: Constructor that takes pointers to DataStore and NLP.
  - `std::string processInput(const std::string &input)`: Processes input and communicates between IO, DataStore, and NLP.
  - `void updateCache(const std::string &key, const std::string &value)`: Updates recent memory or cache.
  - `std::string retrieveFromCache(const std::string &key)`: Retrieves data from the cache.

`src/nlp.cpp` & `headers/nlp.h`
Class: `NLP`
- Methods:
  - `std::string processInput(const std::string &input)`: Performs basic NLP on the input. If the input is complex, it may delegate to advanced AI models like ChatGPT-4.

`src/main.cpp`
Main Program File**:
- Includes: Integration and initialization of all classes and handling the main loop of the program.
- Main Function:
  - Instantiates objects for IO, DataStore, CacheManager, and NLP.
  - Coordinates interactions between these objects.
  - Manages the overall flow of the program, including user interactions and responses.
