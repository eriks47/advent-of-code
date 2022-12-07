#include <fstream>
#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <limits.h>

#include "Tree.hpp"
#include "Path.hpp"

#define PART 2

#define TOTAL_MEM 70000000
#define REQ_MEM   30000000

std::unordered_map<std::string, Tree*> trees;

int resolveDirectorySizes(Tree *tree)
{
    if (tree->childrenDirectories.empty())
        return tree->GetSize();

    int childSizeSum = 0;
    for (auto &path: tree->childrenDirectories)
    {
        Tree *found = trees[path];
        childSizeSum += resolveDirectorySizes(found);
    }
    tree->childrenDirectories.clear();
    return (tree->m_size = childSizeSum + tree->GetSize());
}

int sumOfDirectories(std::ifstream &inputStream)
{
    // The idea:
    //    - Construct a tree that represents the "file system";
    //    - Recursively compute the size of each directory and push the sizes to a vector
    //    - Iterate through the vector and sum each of the sizes under 100000

    Path path;
    Tree *current = new Tree(path.GetPath());
    std::string line;
    bool areContents = false;
    while (!std::getline(inputStream, line).eof())
    {
        if (line[0] == '$')
            areContents = false;

        if (areContents)
        {
            int size;
            if (line[0] == 'd')
            {
                char n[128], _n[128];
                sscanf(line.c_str(), "%s %s", _n, n);
                current->AddChild(path.GetPath() + n + "/");
            }
            else
            {
                char n[128];
                sscanf(line.c_str(), "%d %s", &size, n);
                current->AddSize(size);
            }
        }

        // $ cd
        if (line[0] == '$' && line[2] == 'c' && line[3] == 'd') 
        {
            trees[current->path] = current;
            std::cout << "Added path: " << current->path << "\n";
            if (line[5] == '/')
                path.ToRoot();
            else if (line[5] == '.' && line[6] == '.')
                path.Pop();
            else
                path.Push(line.c_str() + 5);

            if (trees.find(path.GetPath()) == trees.end())
                current = new Tree(path.GetPath());
            else
                current = trees[path.GetPath()];
        }
        else if (line[0] == '$' && line[2] == 'l' && line[3] == 's') 
        {
            areContents = true;
        }
    }
    trees[current->path] = current;

    // Resolve unresolved children directories
    Tree *root = trees["/"];
    resolveDirectorySizes(root);

#if PART == 1
    // Find the sum
    int sum = 0;
    for (auto &[_path, node]: trees)
    {
        if (!node)
            std::cout << "XDDD" << std::endl;
        if (node->GetSize() <= 100000)
            sum += node->GetSize();
    }
    return sum;
#elif PART == 2
    int memUsed = root->GetSize();
    int memFree = TOTAL_MEM - memUsed;
    int memMissing = REQ_MEM - memFree;

    int sizeOfDeleted = INT_MAX;
    for (auto &[_path, node]: trees)
    {
        if (node->GetSize() >= memMissing && node->GetSize() < sizeOfDeleted)
            sizeOfDeleted = node->GetSize();
    }
    return sizeOfDeleted;
#endif
}

int main()
{
    std::ifstream inputStream("input.txt");
    int sum = sumOfDirectories(inputStream);
    std::cout << "The sum is: " << sum << "\n";
}
