namespace Helper
{
bool FileExist(std::string filename)
{
    // benötigt #include <fstream>
    std::ifstream ifile(filename.c_str()); // Try to open file for reading
    return (bool)ifile; // Casted to bool here, so true if ifile != null, i.e. it exists
}

//! Gets a value with the given key from the configuration. if the values does not exist, returns '0'
int GetValueFromConfig(std::string variableKey)
{
    if(configMap.count(variableKey))
    {
        return atoi(configMap[variableKey].c_str());
    }

    return 0;
}

//! Gets a value with a key combined from 'variableKey' + 'value' from the configuration. if the values does not exist, returns '0'
int GetValueFromConfig(std::string variableKey, int value)
{
    std::stringstream keyName;
    keyName << variableKey << (value);
    if(configMap.count(keyName.str()))
    {
        return atoi(configMap[keyName.str()].c_str());
    }

    return 0;
}

//! Gets a value with a key combined as 'PreFix1PostFix' from the configuration. If the values does not exist, returns '0'
int GetValueFromConfig(std::string preFix, int value, std::string postFix)
{
    std::stringstream keyName;
    keyName << preFix << (value) << postFix;
    std::string name = keyName.str();

    if(configMap.count(name))
    {
        return atoi(configMap[name].c_str());
    }

    return 0;
}

}
