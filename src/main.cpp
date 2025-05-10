#include <iostream>
#include "CustomLogger.hpp"
#include <memory>

int main()
{
    std::unique_ptr<CustomLogger::Logger> logger = std::make_unique<CustomLogger::Logger>();
    for (int i = 0; i < 1000000; i++)
    {

        logger->writeLog("My First Log..", "INFO", "LNX");
        logger->writeLog("My second Log..", "INFO", "LNX");
    }
}