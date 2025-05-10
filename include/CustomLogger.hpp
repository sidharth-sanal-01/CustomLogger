#ifndef __CUSTOM_LOGGER__HPP__
#define __CUSTOM_LOGGER__HPP__
#include <iostream>
#include <fstream>
#include <filesystem>
#include <semaphore.h>
#include <unordered_set>

namespace fs = std::filesystem;

namespace CustomLogger
{

    class Logger
    {
    private:
        std::ofstream LogFile;
        std::unordered_set<std::string> messageTypes = {"INFO", "WARNING", "ERROR"};

    public:
        Logger();
        Logger(std::string LogPath);
        ~Logger();
        sem_t *getNamedMutex();                                                         /**
                                                                                         * @brief provides shared mutex to synchronise writing between processes.
                                                                                         * It uses semaphore to create mutex
                                                                                         * @return semaphore pointer.
                                                                                         */
        int writeLog(std::string message, std::string messageType, std::string app_id); /**
                                                                                         * @brief functionality to write logs to logger.
                                                                                         * It creates logs with time of writing calculated.
                                                                                         * @param message The message to be put in log.
                                                                                         * @param messageType The message type to be put in log.eg: ERROR, INFO
                                                                                         * @param app_id the app_id of the log being passed
                                                                                         * @return -1 if unsuccessfull,0 if successfull.
                                                                                         */
        std::string getCurrentTime();                                                   /**
                                                                                         * @brief functionality to get time in string format
                                                                                         * It creates time object in string format.
                                                                                         * @return time in string format
                                                                                         */
    };
};

#endif