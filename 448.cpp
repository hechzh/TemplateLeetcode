#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        int n = nums.size();
        for (auto &num : nums)
        {
            int x = (num - 1) % n;
            nums[x] += n;
        }
        vector<int> ret;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= n)
            {
                ret.push_back(i + 1);
            }
        }
        return ret;
    }
};

template <int... Ints>
using int_sequence = std::integer_sequence<int, Ints...>;

template <int I, int... N>
void print(int_sequence<I, N...>)
{
    cout << I << " ";
    if constexpr (sizeof...(N) == 0)
        cout << endl;
    else
        print(int_sequence<N...>());
}

template <int I, int... N>
constexpr auto cat(int_sequence<N...>)
{
    return int_sequence<I, N...>();
}

template <int n, int index, int Itop, int... i, int... I>
constexpr auto changeaddN(int_sequence<i...>, int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(i) == index)
        return int_sequence<i..., Itop + n, I...>();
    else
        return changeaddN<n,index>(int_sequence<i..., Itop>(), int_sequence<I...>());
}

template <int n>
constexpr int_sequence<> callwithreturn(int_sequence<>) { return int_sequence<>(); }

template <int n, int Itop, int... I>
constexpr auto callwithreturn(int_sequence<Itop, I...>)
{
    if constexpr (Itop > n)
        return callwithreturn<n>(int_sequence<I...>());
    else
        return cat<n - sizeof...(I)>(callwithreturn<n>(int_sequence<I...>()));
}

template <int index, int Itop, int... i, int... I>
constexpr auto getvalue(int_sequence<i...>, int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(i) == index)
        return Itop;
    else
        return getvalue<index>(int_sequence<i..., Itop>(), int_sequence<I...>());
}

template <int n, int Iindex, int... I>
constexpr auto CounterAdd(int_sequence<I...> _)
{
    if constexpr (Iindex < n)
        return CounterAdd<n, Iindex + 1>(changeaddN<n, (getvalue<Iindex>(int_sequence<>(), _) - 1) % n>(int_sequence<>(), _));
    else
        return _;
}

template <int... I>
constexpr auto findDisappearedNumbers(int_sequence<I...> _)
{
    return callwithreturn<sizeof...(I)>(CounterAdd<sizeof...(I), 0>(_));
}

int main()
{
    vector<int> a = {4, 3, 2, 7, 8, 2, 3, 1};
    Solution S;
    vector<int> b = S.findDisappearedNumbers(a);
    for (auto x : b)
    {
        cout << x << " ";
    }
    cout << endl;
    auto template_a = int_sequence<4, 3, 2, 7, 8, 2, 3, 1>();
    auto template_b = findDisappearedNumbers(template_a);
    print(template_b);
    return 0;
}
