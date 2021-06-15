#pragma once
#include <atomic>

struct ControlBlock
{
    std::atomic<std::size_t> ref_counter{0};
    std::atomic<std::size_t> weak_counter{0};
};