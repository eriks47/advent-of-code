#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define PART 2

using namespace std;

vector<vector<char>> getIntialState(ifstream &inputStream)
{
    vector<vector<char>> state;

    // Read in all the chars in order line by line
    string line;
    bool isInitializedState = false;
    for(;;)
    {
        getline(inputStream, line);
        if (line[1] >= '0' && line[1] <= '9')
            break;

        int stackIndex = 0;
        int blankCount = 0;
        for (char c : line)
        {
            if (c >= 'A' && c <= 'Z')
            {
                if (!isInitializedState)
                {
                    vector<char> newStack = {c};
                    state.push_back(newStack);
                }
                else
                {
                    state[stackIndex].push_back(c);
                    ++stackIndex;
                }
                blankCount = 0;
            }
            else if (blankCount == 3 && c == ' ')
            {
                if (!isInitializedState)
                {
                    vector<char> newStack = {};
                    state.push_back(newStack);
                }
                else
                {
                    ++stackIndex;
                }
                blankCount = 0;
            }
            else if (c == ' ')
            {
                ++blankCount;
            }
        }
        isInitializedState = true;
    }

    // Since we have read the crate stacks from top to bottom
    // we need to reverse them
    for (vector<char> &stack : state)
    {
        reverse(stack.begin(), stack.end());
    }
    return state;
}

void interpretCommands(ifstream &inputStream, vector<vector<char>> &state)
{
    // This code relies on the fact that `inputStream` is on the blank line
    // below initial state and above the commands

    string line;
    getline(inputStream, line);
    for(getline(inputStream, line); !inputStream.eof(); getline(inputStream, line))
    {
        string bin;
        stringstream lineStream;
        lineStream << line;
        int count, from, to;
        lineStream >> bin;
        lineStream >> count;
        lineStream >> bin;
        lineStream >> from;
        lineStream >> bin;
        lineStream >> to;

        --from; // Since ideces in C++ begin with 0, but in the input
        --to;   // the counting starts with 1, we convert them
#if PART == 1
        for (int i = 0; i < count; ++i)
        {
            char topCrate = state[from][state[from].size() - 1];
            state[from].pop_back();
            state[to].push_back(topCrate);
        }
#elif PART == 2
        // In the second part of the challange the only difference is that
        // the crates, when moved, retain order.

        vector<char> buffer = {};
        for (int i = 0; i < count; ++i)
        {
            char topCrate = state[from][state[from].size() - 1];
            state[from].pop_back();
            buffer.push_back(topCrate);
        }

        for (int i = buffer.size() - 1; i >= 0; --i)
        {
            state[to].push_back(buffer[i]);
        }
#endif
    }
}

string getTopCrates(ifstream &inputStream)
{
    vector<vector<char>> initialState = getIntialState(inputStream);
    interpretCommands(inputStream, initialState);
    string topCrates;
    for (const vector<char> stack: initialState)
    {
        topCrates += stack.at(stack.size() - 1);
    }
    return topCrates;
}

int main()
{
    ifstream inputStream("input.txt");
    string topCrates = getTopCrates(inputStream);
    cout << "The top crates are : `" << topCrates << "`\n";
}
