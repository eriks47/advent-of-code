#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <any>

using Packet = std::vector<std::any>;
using PacketPair = std::pair<Packet, Packet>;

Packet parse_packet(std::string packet) 
{
    std::optional<std::any> current_value;
    std::vector<Packet> packet_stack;
    for(char c : packet)
    {
        if (c == '[')
        {
            packet_stack.push_back(Packet());
        }
        else if (c == ',')
        {
            packet_stack.back().push_back(*current_value);
            current_value = std::nullopt;
        }
        else if (c >= '0' && c <= '9')
        {
            if (!current_value.has_value())
                current_value = 0;

            auto &value = std::any_cast<int&>(*current_value);
            value *= 10;
            value += c - '0';
        }
        else if (c == ']')
        {
            if (current_value.has_value())
            {
                packet_stack.back().push_back(*current_value);
                current_value = std::nullopt;
            }

            current_value = packet_stack.back();
            packet_stack.pop_back();
        }
    }

    return std::any_cast<Packet>(*current_value);
}

std::vector<PacketPair> parse() 
{
    std::vector<PacketPair> result;
    std::ifstream input("input.txt");
    std::string first_packet, second_packet, dummy;
    while (std::getline(input, first_packet))
    {
        std::getline(input, second_packet);
        std::getline(input, dummy);

        auto packet1 = parse_packet(first_packet);
        auto packet2 = parse_packet(second_packet);
        result.push_back(std::make_pair(packet1, packet2));
    }
    return result;
}

int compare(int left, int right)
{
    return right - left;
}

int compare(const Packet &left, const Packet &right)
{
    std::size_t min_size = std::min(left.size(), right.size());

    for (std::size_t i = 0; i < min_size; ++i)
    {
        int comparison;
        
        if (left[i].type() == typeid(int) && right[i].type() == typeid(int))
        {
            comparison = compare(std::any_cast<int>(left[i]), std::any_cast<int>(right[i]));
        }
        else if (left[i].type() == typeid(Packet) && right[i].type() == typeid(Packet))
        {
            comparison = compare(std::any_cast<Packet>(left[i]), std::any_cast<Packet>(right[i]));
        }
        else
        {
            Packet left_packet;

            if (left[i].type() == typeid(int)) { left_packet = { left[i] }; }
            else { left_packet = std::any_cast<Packet>(left[i]); }

            Packet right_packet;

            if (right[i].type() == typeid(int)) { right_packet = { right[i] }; }
            else { right_packet = std::any_cast<Packet>(right[i]); }

            comparison = compare(left_packet, right_packet);
        }

        if (comparison != 0)
            return comparison;
    }
    return static_cast<int>(right.size() - left.size());
}

int main(int argc, char *argv[]) 
{
    auto pairs = parse();
    int valid_pairs = 0;

    for (std::size_t i = 0; i < pairs.size(); ++i)
    {
        auto comparison = compare(pairs[i].first, pairs[i].second);

        if (comparison >= 0) { valid_pairs += static_cast<int>(i) + 1; }
    }

    std::cout << "Silver: " << valid_pairs << std::endl;

    auto start_marker = parse_packet("[[2]]");
    auto end_marker = parse_packet("[[6]]");
    std::vector<Packet> packets = { start_marker, end_marker };

    for (auto pair : pairs)
    {
        packets.push_back(pair.first);
        packets.push_back(pair.second);
    }

    std::sort(packets.begin(), packets.end(), [](const Packet &left, const Packet &right)
    {
        auto comparison = compare(left, right);

        if (comparison == 0) { return false; }

        return comparison > 0;
    });

    std::size_t index_start, index_end;

    for (std::size_t i = 0; i < packets.size(); ++i)
    {
        auto packet = packets[i];

        if (compare(packet, start_marker) == 0)
        {
            index_start = i + 1;
        }
        else if (compare(packet, end_marker) == 0)
        {
            index_end = i + 1;
        }
    }

    std::cout << "Gold: " << index_start * index_end << std::endl;
}
