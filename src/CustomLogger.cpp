#include "CustomLogger.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <semaphore.h>
#include <fcntl.h>
#include <ctime>
#include <unordered_set>
#include <thread>

CustomLogger::Logger::Logger()
{
    std::cout << "Logger Initiated.." << std::endl;
    std::cout << "No Custom Path provided..Writing Logs to /home/sidharth/Desktop" << std::endl;
    LogFile.open("/home/sidharth/Desktop/newLogger.txt", std::ios::app);
    if (!LogFile.is_open())
    {
        std::cerr << "Could not open Log File..." << std::endl;
    }
    std::cout << "Log File Ready to write" << std::endl;
}

CustomLogger::Logger::Logger(std::string LogPath)
{
    if (!fs::exists(LogPath))
    {
        std::cerr << "Cannot Open Log File Path, Log File does not exist" << std::endl;
    }
    LogFile.open(LogPath, std::ios::app);
    if (!LogFile.is_open())
    {
        std::cerr << "Could not open Log File.." << std::endl;
    }
    std::cout << "Log File Ready to write" << std::endl;
}

sem_t *CustomLogger::Logger::getNamedMutex()
{
    const char *MUTEX_NAME = "/loggerSemaphore";
    sem_t *mutex = sem_open(MUTEX_NAME, O_CREAT | O_EXCL, 0666, 1);
    if (mutex == SEM_FAILED)
    {
        if (errno == EEXIST)
        {
            mutex = sem_open(MUTEX_NAME, 0);
        }
        else
        {
            std::cout << errno << std::endl;
            std::cerr << "sem allocation Failed" << std::endl;
        }
    }
    else
    {
        std::cerr << "sem initialization Failed" << std::endl;
    }
    return mutex;
}

int CustomLogger::Logger::writeLog(std::string message, std::string messageType, std::string APP_ID)
{

    if (message == "" || APP_ID == "")
    {
        std::cout << "No information provided in the logs.." << std::endl;
        return -1;
    }
    if (messageTypes.find(messageType) == messageTypes.end())
    {
        std::cout << "Message Type not found in Logs" << std::endl;
        return -1;
    }
    sem_t *mutex = getNamedMutex();
    std::string currentTime = getCurrentTime();
    std::string LogToWrite = "[ " + currentTime + " ]:[" + messageType + "]: " + message + APP_ID + "\n";
    try
    {
        sem_wait(mutex);       // waiting for the mutex
        LogFile << LogToWrite; // writing to the file
        sem_post(mutex);
        sem_close(mutex); // releasing the mutex
        return 1;
    }
    catch (...)
    {
        std::cerr << "Writing to File Failed" << std::endl;
        return -1;
    }
}

std::string CustomLogger::Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

CustomLogger::Logger::~Logger()
{
    if (LogFile.is_open())
    {
        std::cout << "Closing Log File" << std::endl;
        LogFile.close();
    }
}
