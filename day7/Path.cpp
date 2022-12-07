#include "Path.hpp"

Path::Path()
{
    path = "/";
}

Path::~Path() {}
    
void Path::Push(std::string directory)
{
    path += directory + "/";
}

void Path::Pop()
{
    path.pop_back();
    for (int i = path.size() - 1; i != 0; --i)
    {
        if (path[i] == '/')
            break;
        path.pop_back();
    }
}

void Path::ToRoot()
{
    path = "/";
}

std::string Path::GetPath() const
{
    return path;
}
