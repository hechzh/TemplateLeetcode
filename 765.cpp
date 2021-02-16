#include <iostream>
#include <vector>
#include <array>

using namespace std;

#define CouplerNumber(x) (x ^ 1)

class Solution
{
public:
    int minSwapsCouples(vector<int> &row)
    {
        int N = row.size() / 2;
        int counter = 0;
        int Answer = 0;
        vector<int> records(2 * N);
        vector<int> Skip(N);
        for (auto i : row)
        {
            records[i] = counter;
            counter++;
        }
        for (int i = 0; i < N; i++)
        {
            if (Skip[i] == 1)
                continue;
            else
            {
                int answer = -1;
                int j = 2 * i;
                int k;
                do
                {
                    k = CouplerNumber(records[CouplerNumber(row[j])]);
                    Skip[k / 2] = 1;
                    j = k;
                    answer++;
                } while (j / 2 != i);
                Answer += answer;
            }
        }
        return Answer;
    }
};

template <int... Ints>
using int_sequence = integer_sequence<int, Ints...>;

template <int value, int swap, int... i, int Itop, int... I>
constexpr auto findandswap(int_sequence<i...>, int_sequence<Itop, I...>)
{
    if constexpr (Itop == value ^ 1)
        return int_sequence<i..., swap, I...>();
    else
        return findandswap<value, swap>(int_sequence<i..., Itop>(), int_sequence<I...>());
}

template <int counter, int Ifirst, int Isecond, int... I>
constexpr auto reduceloop(int_sequence<Ifirst, Isecond, I...>)
{
    if constexpr (Ifirst ^ 1 == Isecond)
    {
        if constexpr (sizeof...(I) == 0)
            return counter;
        else
            return reduceloop<counter>(int_sequence<I...>());
    }
    else
        return reduceloop<counter + 1>(findandswap<Ifirst, Isecond>(int_sequence<>(), int_sequence<I...>()));
}

template <int... I>
constexpr auto minSwapsCouples(int_sequence<I...> _)
{
    return reduceloop<0>(int_sequence<I...>());
}

int main()
{
    Solution s;
    vector<int> test = {0, 3, 1, 2};
    auto answer = s.minSwapsCouples(test);
    cout << answer << endl;
    auto template_test = int_sequence<0, 3, 1, 2>();
    int x = minSwapsCouples(template_test);
    cout << x << endl;
    return 1;
}