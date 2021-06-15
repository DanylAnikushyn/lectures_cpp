#pragma once
#include <atomic>

struct ControlBlock
{
    std::atomic<unsigned> ref_counter;
    std::atomic<unsigned> weak_counter;
};