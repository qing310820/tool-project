#include "function.h"

void split(string str, string pattern, vector<string>& vecList)
{
    while (true)
    {
        int index = str.find(pattern);

        std::string subStr = str.substr(0, index);
        if (!subStr.empty())
        {
            vecList.push_back(subStr);
        }

        str.erase(0, index + pattern.size());

        if (index == -1)
            break;
    }
}