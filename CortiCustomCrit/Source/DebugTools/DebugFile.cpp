namespace DebugFile
{
//! Access to the file
std::ofstream fileWriter;

//! Loggt Zeile mit Zeitstempel und extra Linebreak.
void LogLine(std::string logline)
{
    if(fileWriter.is_open())
    {
        fileWriter << GetDateTime("%Y.%m.%d-%H:%M:%S") << " " << logline << std::endl;
    }
}

//! Loggt Zeile ohne extra Linebreak. Verwendet wenn LineBreak schon in logline ist.
void LogLineRaw(std::string logline)
{
    if(fileWriter.is_open())
    {
        fileWriter << logline;
    }
}

//! Called by the OnStartup-Callback.
void OnStartup()
{
    std::ostringstream nameStream;
    nameStream << "CortiLogs.txt";
    fileWriter.open(nameStream.str().c_str(), std::ios::out | std::ios::app);
    LogLine("---------------------------------------------------------------");
    LogLine("CortiLogs: New game started");
}

//! Call by the OnExit Callback.
void OnExit()
{
    fileWriter.close();
}
}
