#pragma once

#include <string>

class Path
{
public:
    Path();
    ~Path();
    
    void Push(std::string directory);
    void Pop();
    void ToRoot();
    std::string GetPath() const;

private:
    std::string path;
};
