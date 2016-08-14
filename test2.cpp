#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <chrono>
#include <functional>
#include <assert.h>

struct LargerData
{
    int val;
    LargerData() : values(new double[512])
    {
    }

    ~LargerData()
    {
        delete[] values;
    }

    LargerData(LargerData &other) : LargerData()
    {
        this->val = other.val;
        for(size_t i=0;i<512;++i)values[i]=other.values[i];
        other.values = 0;
    }

    LargerData(LargerData &&other)
    {
        this->val = std::move(other.val);
        this->values = other.values;
        other.values = 0;
    }

    LargerData(const LargerData &) = default;
/*
    void operator=(const int &value)
    {
        val = value;
    }
    */

    bool operator==(const LargerData &other)
    {
        return val == other.val;
    }

    double *values;
};

bool operator<(const LargerData &o1, const LargerData &o2)
{
    return o1.val < o2.val;
}

template <typename A, typename B>
void unique_manual(A &arr, B begin, B end)
{
    // The array container behaves kind of strange on deletion of elements, therefore the given end could become invalid, make double check here
    for (auto it = begin; it != end && it != arr.end(); it++) {
        auto it2 = it;
        it2++;  // Skip first one to not compare the same element
        while (it2 != end && it2 != arr.end()) {
            if (*it2 == *it) {
                // We deleted the given element, since it cannot be the current
                // it, we can safley delete it and breaking the inner loop.
                it2 = arr.erase(it2);
            } else {
                it2++;
            }
        }
    }
}

void unique_auto_signarue(auto &arr, auto begin, auto end)
{
    std::sort(begin, end);
    arr.erase(std::unique(begin, end), end);
}

template <typename A, typename B>
void unique_template_signature(A &arr, B begin, B end)
{
    std::sort(begin, end);
    arr.erase(std::unique(begin, end), end);
}

void unique_with_move(auto &arr, auto begin, auto end)
{
    decltype(std::remove_reference(*arr.data())) v;
    std::set<decltype(v)> m;
    for (auto e : arr) {
        m.insert(std::move(e));
    }
    arr.clear();
    for (auto e : m) {
        arr.push_back(std::move(e));
    }
}

void unique_with_iterators(auto &arr, auto begin, auto end)
{
    decltype(std::remove_reference(*arr.data())) v;
    std::set<decltype(v)> m(begin, end);
    arr.clear();
    arr.insert(arr.begin(), m.begin(), m.end());
}

template <typename T>
auto generate_vector(size_t size)
{
    std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    std::vector<T> arr(size);
    std::default_random_engine gen;
    std::generate(arr.begin(), arr.end(), [&]() { return dist(gen); });

    // Make sure we have a few doble-elements within the list...
    if (size < 10) throw std::invalid_argument("generate vectors must be called with at least 10");  // Be lazy for the next lines
    arr[0] = 4;
    arr[3] = 4;
    arr[4] = 4;
    arr[size - 1] = 4;
    return arr;
}

template <>
auto generate_vector<LargerData>(size_t size)
{
    std::vector<LargerData> arr(size);

    // Make sure we have a few doble-elements within the list...
    if (size < 10) throw std::invalid_argument("generate vectors must be called with at least 10");  // Be lazy for the next lines
    /*
    arr[0] = 4;
    arr[3] = 4;
    arr[4] = 4;
    arr[size - 1] = 4;
    */
    return arr;
}

template <typename T>
void check_runtime(size_t size)
{
    auto v = generate_vector<T>(size);

    // We have to define a lambda here because the auto type could ne resolved otherwise
    std::vector<std::function<void(decltype((v)), decltype(v.begin()), decltype(v.end()))>> arr(
        {[](decltype(v) & a, decltype(v.begin()) b, decltype(v.end()) c) { unique_manual(a, b, c); },
         [](decltype(v) & a, decltype(v.begin()) b, decltype(v.end()) c) { unique_auto_signarue(a, b, c); },
         [](decltype(v) & a, decltype(v.begin()) b, decltype(v.end()) c) { unique_template_signature(a, b, c); },
         [](decltype(v) & a, decltype(v.begin()) b, decltype(v.end()) c) { unique_with_move(a, b, c); },
         [](decltype(v) & a, decltype(v.begin()) b, decltype(v.end()) c) { unique_with_iterators(a, b, c); }});

    std::vector<std::string> names = {"unique_manual              ", "unique_auto_signarue       ", "unique_template_signature  ", "unique_with_move           ", "unique_with_iterators      "};

    assert(names.size() == arr.size());

    size_t prev_elems = 0;
    std::cout << "Elements: " << size << std::endl;
    for (size_t i = 0; i < arr.size(); i++) {
        // Copy the data to have the same data each run
        auto data = v;
        auto before = std::chrono::high_resolution_clock::now();
        arr[i](data, data.begin(), data.end());
        auto after = std::chrono::high_resolution_clock::now();
        std::cout << std::fixed << "\t " << names[i] << ": " << std::chrono::duration_cast<std::chrono::duration<double>>(after - before).count() << std::endl;

        // Make sure everything works as expected
        if (prev_elems != 0 && prev_elems != data.size()) {
            throw std::runtime_error("Elements are not equal previous run " + std::to_string(prev_elems) + " vs. " + std::to_string(data.size()));
        }
        prev_elems = data.size();
        if (data.size() == size) {
            throw std::runtime_error("Elements should have been removed, but they are not");
        }
    }
    std::cout << "\t Size after (can be random):" << prev_elems << std::endl;
}

int main(int argc, char **argv)
{
    for (size_t i = 1; i < 7; ++i) {
        check_runtime<int>(pow(10, i));
    }

    for (size_t i = 1; i < 7; ++i) {
        check_runtime<LargerData>(pow(10, i));
    }
}
