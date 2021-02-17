#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define TEST_CASE_561 2, 4, 3, 2, 6, 7
//#define SortMethod Quicksort
#define SortMethod bubblesort

class Solution
{
public:
    int arrayPairSum(vector<int> &nums)
    {
        sort(begin(nums), end(nums));
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i)
            sum += nums[i++];
        return sum;
    }
};

template <int... Ints>
using int_sequence = integer_sequence<int, Ints...>;

template <int I, int... N>
constexpr auto catint(int_sequence<N...>)
{
    return int_sequence<I, N...>();
}

template <int Head, int... I, int... N>
constexpr auto catsequence(int_sequence<I...>, int_sequence<N...>)
{
    return int_sequence<I..., Head, N...>();
}

template <int Head, int Itop, int... I>
constexpr auto Smallerthan(int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(I) == 0)
    {
        if constexpr (Itop < Head)
            return int_sequence<Itop>();
        else
            return int_sequence<>();
    }
    else
    {
        if constexpr (Itop < Head)
            return catint<Itop>(Smallerthan<Head>(int_sequence<I...>()));
        else
            return Smallerthan<Head>(int_sequence<I...>());
    }
}

template <int Head, int Itop, int... I>
constexpr auto Biggerthan(int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(I) == 0)
    {
        if constexpr (Itop >= Head)
            return int_sequence<Itop>();
        else
            return int_sequence<>();
    }
    else
    {
        if constexpr (Itop >= Head)
            return catint<Itop>(Biggerthan<Head>(int_sequence<I...>()));
        else
            return Biggerthan<Head>(int_sequence<I...>());
    }
}

constexpr auto Quicksort(int_sequence<>) { return int_sequence<>(); }

template <int Itop, int... I>
constexpr auto Quicksort(int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(I) == 0)
        return int_sequence<Itop>();
    else
        return catsequence<Itop>(Quicksort(Smallerthan<Itop>(int_sequence<I...>())), Quicksort(Biggerthan<Itop>(int_sequence<I...>())));
}

template <int Insert>
constexpr auto bubbleInsert(int_sequence<>)
{
    return int_sequence<Insert>();
}

template <int Insert, int Itop, int... I>
constexpr auto bubbleInsert(int_sequence<Itop, I...>)
{
    if constexpr (Itop > Insert)
        return int_sequence<Insert, Itop, I...>();
    else
        return catint<Itop>(bubbleInsert<Insert>(int_sequence<I...>()));
}

constexpr auto bubblesort(int_sequence<>){return int_sequence<>();}

template <int Itop, int... I>
constexpr auto bubblesort(int_sequence<Itop, I...>)
{
    return bubbleInsert<Itop>(bubblesort(int_sequence<I...>()));
}

template <int Ifirst, int Isecond, int... I>
constexpr int PairSum(int_sequence<Ifirst, Isecond, I...>)
{
    if constexpr (sizeof...(I) == 0)
        return Ifirst;
    else
        return Ifirst + PairSum(int_sequence<I...>());
}

template <int... I>
constexpr int arrayPairSum(int_sequence<I...> _)
{
    return PairSum(SortMethod(_));
}

template <>
constexpr int arrayPairSum<>(int_sequence<>) { return 0; }

int main()
{
    Solution s;
    vector<int> test = {TEST_CASE_561};
    cout << s.arrayPairSum(test) << endl;
    auto template_test = int_sequence<TEST_CASE_561>();
    auto template_result = arrayPairSum(template_test);
    cout << template_result << endl;
}