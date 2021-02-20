#include <iostream>
#include <vector>
using namespace std;

#define TEST_CASE 0, 0, 1, 1, 1, 0,1, 0, 0, 1, 1, 1, 1
#define Knumber 2

class Solution
{
public:
    int longestOnes(vector<int> &A, int K)
    {
        size_t left = 0, right = 0;
        int longest = 0, counter = 0;
        if (K == 0)
        {
            while (right < A.size())
            {
                if (A[right] == 1)
                    counter++;
                else
                    counter = 0;
                longest = longest > counter ? longest : counter;
                right++;
            }
            return longest;
        }
        while (right < A.size())
        {
            if (A[right] == 0)
            {
                if (counter == K)
                {
                    while (A[left] == 1)
                        left++;
                    left++;
                    counter -= 1;
                }
                counter++;
            }
            longest = right - left > longest ? right - left : longest;
            right++;
        }
        return longest + 1;
    }
};

template <int... Ints>
using int_sequence = std::integer_sequence<int, Ints...>;

template <int index, int Itop, int... i, int... I>
constexpr auto getvalue(int_sequence<i...>, int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(i) == index)
        return Itop;
    else
        return getvalue<index>(int_sequence<i..., Itop>(), int_sequence<I...>());
}

template <int index, int... I>
constexpr auto getvalue(int_sequence<I...> _)
{
    return getvalue(int_sequence<>(), _);
}

template <int I, int... N>
void print(int_sequence<I, N...>)
{
    cout << I << " ";
    if constexpr (sizeof...(N) == 0)
        cout << endl;
    else
        print(int_sequence<N...>());
}

template <int K>
constexpr size_t longestOnes(int_sequence<>) { return 0; }

template <int K, size_t lO, int Itop, int... I>
constexpr size_t longestOnes(int_sequence<Itop, I...>, int_sequence<>) { return max(sizeof...(I) + 1, lO); }

template <int K, size_t lO, int Itop, int... I>
constexpr size_t longestOnes(int_sequence<>, int_sequence<Itop, I...>);

template <int K, size_t lO, int Jtop, int... J, int Itop, int... I>
constexpr size_t longestOnes(int_sequence<Jtop, J...>, int_sequence<Itop, I...>)
{
    //print(int_sequence<Jtop, J...>());
    //print(int_sequence<Itop, I...>());
    if constexpr (K == 0)
    {
        if constexpr (Itop == 1)
            return longestOnes<0, max(sizeof...(J) + 1, lO)>(int_sequence<Jtop, J..., Itop>(), int_sequence<I...>());
        else
        {
            if constexpr (Jtop == 1)
                return longestOnes<0, max(sizeof...(J) + 1, lO)>(int_sequence<J...>(), int_sequence<Itop, I...>());
            else
                return longestOnes<0, max(sizeof...(J) + 1, lO)>(int_sequence<J..., Itop>(), int_sequence<I...>());
        }
    }
    else
    {
        if constexpr (Itop == 1)
            return longestOnes<K, max(sizeof...(J) + 1, lO)>(int_sequence<Jtop, J..., Itop>(), int_sequence<I...>());
        else
            return longestOnes<K - 1, max(sizeof...(J) + 1, lO)>(int_sequence<Jtop, J..., Itop>(), int_sequence<I...>());
    }
}

template <int K, size_t lO, int Itop, int... I>
constexpr size_t longestOnes(int_sequence<>, int_sequence<Itop, I...>)
{
    if constexpr (K == 0)
    {
        if constexpr (Itop == 1)
            return longestOnes<0, max((size_t)1, lO)>(int_sequence<Itop>(), int_sequence<I...>());
        else
        {
            return longestOnes<0, lO>(int_sequence<>(), int_sequence<I...>());
        }
    }
    else
    {
        if constexpr (Itop == 1)
            return longestOnes<K, max((size_t)1, lO)>(int_sequence<Itop>(), int_sequence<I...>());
        else
            return longestOnes<K - 1, max((size_t)1, lO)>(int_sequence<Itop>(), int_sequence<I...>());
    }
}

template <int K, int... I>
constexpr size_t longestOnes(int_sequence<I...> _) { return longestOnes<K, 0>(int_sequence<>(), _); }

int main()
{
    Solution s;
    vector<int> test = {TEST_CASE};
    int result = s.longestOnes(test, Knumber);
    cout << result << endl;
    auto template_test = int_sequence<TEST_CASE>();
    auto template_result = longestOnes<Knumber>(template_test);
    cout << template_result << endl;
    return 0;
}