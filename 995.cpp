#include <iostream>
#include <vector>
#include <array>
using namespace std;
class Solution
{
public:
    int minKBitFlips(vector<int> &A, int K)
    {
        int n = A.size();
        vector<int> diff(n + 1);
        int counter = 0, revCnt = 0;
        int i = 0;
        while (i < n - K + 1)
        {
            revCnt ^= diff[i];
            if (A[i] == revCnt)
            {
                ++counter;
                revCnt ^= 1;
                diff[i + K] ^= 1;
            }
            i++;
        }
        while (i < n)
        {
            revCnt ^= diff[i];
            if (A[i] == revCnt)
                return -1;
            i++;
        }
        return counter;
    }
};

template <int... Ints>
using int_sequence = std::integer_sequence<int, Ints...>;

template <int i, int... I>
constexpr auto push(int_sequence<I...>) { return int_sequence<I..., i>(); }

template <int Itop, int... I>
constexpr int head(int_sequence<Itop, I...>) { return Itop; }

template <int Itop, int... I>
constexpr int tail(int_sequence<Itop, I...>) { return int_sequence<I...>(); }

template <int I, int... N>
constexpr auto cat(int_sequence<N...>) { return int_sequence<I, N...>(); }

template <int I, int... N>
void print(int_sequence<I, N...>)
{
    cout << I << " ";
    if constexpr (sizeof...(N) == 0)
        cout << endl;
    else
        print(int_sequence<N...>());
}


template <int K, int index, int rev, int Itop, int... I, int... J>
constexpr int minKBitFlips(int_sequence<Itop, I...> d, int_sequence<J...> _)
{
    if constexpr (sizeof...(J) > 0)
    {
        if constexpr (index == head(_) + K)
        {
            if constexpr (Itop == rev ^ 1)
            {
                return minKBitFlips<K, index + 1, rev ^ 1>(d, push<index>(_)) + 1;
            }
            else
            {
                return minKBitFlips<K, index + 1, rev>(d, tail(_));
            }
        }
    }
    else
    {
        if constexpr (Itop == rev)
        {
            return minKBitFlips<K, index + 1, rev ^ 1>(d, push<index>(_)) + 1;
        }
        else
        {
            return minKBitFlips<K, index + 1, rev>(d, _);
        }
    }
}


template <int K>
constexpr auto reverseK(int_sequence<> _) { return _; }

template <int K, int Itop, int... I>
constexpr auto reverseK(int_sequence<Itop, I...> _)
{
    if constexpr (K == 0)
        return _;
    else
        return cat<Itop ^ 1>(reverseK<K - 1>(int_sequence<I...>()));
}

template <int K>
constexpr int minKBitFlips(int_sequence<> _) { return 0; }

template <int K, int Itop, int... I>
constexpr int minKBitFlips(int_sequence<Itop, I...> _)
{
    if constexpr (Itop == 0)
    {
        if constexpr (sizeof...(I) < K - 1)
            return -1;
        else
            return 1 + minKBitFlips<K>(reverseK<K>(_));
    }
    else
    {
        return minKBitFlips<K>(int_sequence<I...>());
    }
}

int main()
{
    Solution s;
    vector<int> test = {0, 0, 0, 1, 0, 1, 1, 0};
    int K = 3;
    int result = s.minKBitFlips(test, K);
    cout << result << endl;
    auto template_test = int_sequence<0, 0, 0, 1, 0, 1, 1, 0>();
    int template_result = minKBitFlips<3>(template_test);
    cout << template_result << endl;
}