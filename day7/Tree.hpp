#pragma once

#include <vector>
#include <memory>
#include <string>

class Tree
{
public:
    Tree(std::string _path);
    ~Tree();

    void AddChild(std::string child);
    void AddSize(int size);
    int GetSize() const;

    bool isDirectory;
    std::string path;
    std::vector<std::string> childrenDirectories;

    int m_size = 0;
};
