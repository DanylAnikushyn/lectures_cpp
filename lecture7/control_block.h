#pragma once
#include <atomic>

struct ControlBlock
{
    std::atomic<unsigned> ref_counter{0};
    std::atomic<unsigned> weak_counter{0};
};