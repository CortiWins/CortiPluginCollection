#include "lodepngHeader.cpp"
#include "ConsoleLoggerHeader.cpp"

//! Used to log text into a file or a console.
namespace CortiLog
{
bool isLogEnabled = false;
bool isLogToFile= false;
bool isLogToConsole= false;

//! Gets the timestamp of the current time with the given format.
const std::string GetDateTime(const char* timeFormat )
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime for more information about date/time format
    strftime(buf, sizeof(buf), timeFormat, &tstruct);
    return buf;
}

#include "DebugFile.cpp"
CConsoleLogger *consoleProcess = null;

//! Makro für Schreibweise als LOGLINE("value=" << 1223); für beliebig viele Parameter.
#define LOGINFO(stream){ if(CortiLog::isLogEnabled){ std::ostringstream parameterStream; parameterStream << stream; CortiLog::Log(parameterStream.str());} }

//! Makro für Schreibweise als LOGLINE("value=" << 1223); für beliebig viele Parameter.
#define LOGERROR(stream){ std::ostringstream parameterStream; parameterStream << stream; CortiLog::LogError(parameterStream.str()); }

//! Gets a value from the configuration. if the values does not exist, returns '0'
int GetValueFromConfig(std::map<std::string, std::string> configMap, std::string variableKey)
{
    if(configMap.count(variableKey))
    {
        return atoi(configMap[variableKey].c_str());
    }

    return 0;
}

//! Writes this line into a file or the console.
void Log(std::string logline)
{
    if(isLogEnabled )
    {
        std::ostringstream logStream;
        logStream << GetDateTime("%Y.%m.%d-%H:%M:%S") << " " << logline << std::endl;
        std::string logString = logStream.str();

        if(isLogToFile)
        {
            DebugFile::LogLineRaw(logString);
        }

        if(isLogToConsole)
        {
            consoleProcess->print(logString.c_str());
        }
    }
}

//! Writes this line into a file or the console or in MessageBox if no console is present.
void LogError(std::string logline)
{
    if(isLogEnabled)
    {
        std::ostringstream logStream;
        logStream << "ERROR: " << GetDateTime("%Y.%m.%d-%H:%M:%S") << " " << logline << std::endl;
        std::string logString = logStream.str();

        if(isLogToFile)
        {
            DebugFile::LogLineRaw(logString);
        }

        if(isLogToConsole)
        {
            consoleProcess->print(logString.c_str());
        }
    }

    if(!isLogToConsole)
    {
        MessageBox ( NULL, logline.c_str(), (char *)"CortiLog Error",  MB_OK | MB_ICONWARNING );
    }
}

//! Called by the OnStartup-Callback.
void OnStartup()
{
    std::map<std::string, std::string> configuration = RPG::loadConfiguration((char *)"CortiLog");

    int logToConsole = GetValueFromConfig(configuration, "LogToConsole") > 0;
    int logToFile = GetValueFromConfig(configuration, "LogToFile") > 0;

    isLogToFile = logToFile > 0;
    isLogToConsole = logToConsole > 0;
    isLogEnabled = isLogToFile || isLogToConsole;

    if(isLogToConsole)
    {
        consoleProcess = null;
        consoleProcess = new CConsoleLogger();
        consoleProcess->Create("CortiLog Console");
    }

    if(isLogToFile)
    {
        CortiLog::DebugFile::OnStartup();
    }

    LOGINFO("CortiLog Startup");
}

//! Call by the OnExit Callback.
void OnExit()
{
    if(isLogToConsole)
    {
        consoleProcess->Close();
        consoleProcess = null;
    }

    if(isLogToFile)
    {
        DebugFile::OnExit();
    }
}
}
