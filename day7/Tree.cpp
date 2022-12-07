#include "Tree.hpp"

Tree::Tree(std::string _path)
{
    path = _path;
}

Tree::~Tree() {}

void Tree::AddChild(std::string child)
{
    childrenDirectories.push_back(child);
}

void Tree::AddSize(int size)
{
    m_size += size;
}

int Tree::GetSize() const
{
    return m_size;
}
