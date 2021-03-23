#pragma once

//
// Simple utility to show progress of come quantized process
// (omp-friendly)
//

#include <cstddef>
#include <functional>

class Progress
{
public:
    using callback_t = std::function<void(const std::size_t, const std::size_t)>;

private:
    const std::size_t total_it;
    std::size_t curr_it;

    callback_t callback;

public:

    Progress() = delete;

    Progress(const std::size_t total_iterations, const callback_t &_callback);

    void add(const std::size_t delta = 1);
};
