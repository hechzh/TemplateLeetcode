#include <iostream>
#include <vector>
#include <type_traits>

#define TEST_CASE_485 1, 1, 0, 1, 1 ,1

using namespace std;

template <int... Ints>
using int_sequence = std::integer_sequence<int, Ints...>;

class Solution
{
public:
    int findMaxConsecutiveOnes(vector<int> &nums)
    {
        int answer = 0;
        int temp_answer = 0;
        for (auto i : nums)
        {
            if (i == 0)
            {
                if (temp_answer)
                {
                    answer = answer > temp_answer ? answer : temp_answer;
                    temp_answer = 0;
                }
            }
            else
            {
                temp_answer++;
            }
        }
        answer = answer > temp_answer ? answer : temp_answer;
        return answer;
    }
};

template <int max, int counter>
constexpr int findMaxConsecutiveOnes(int_sequence<>) { return 0; }

template <int max, int counter, int Itop, int... I>
constexpr int findMaxConsecutiveOnes(int_sequence<Itop, I...>)
{
    if constexpr (sizeof...(I) == 0)
    {
        if constexpr (Itop == 1)
            return max > counter + 1 ? max : counter + 1;
        else
            return max > counter ? max : counter;
    }
    if constexpr (Itop == 0)
        return findMaxConsecutiveOnes< (max > counter ? max : counter), 0 > (int_sequence<I...>());
    else
        return findMaxConsecutiveOnes<max, counter + 1>(int_sequence<I...>());
}

template <int Itop, int... I>
constexpr int findMaxConsecutiveOnes(int_sequence<Itop, I...> _)
{
    return findMaxConsecutiveOnes<0, 0>(_);
}

int main()
{
    Solution s;
    vector<int> test = {TEST_CASE_485};
    int result = s.findMaxConsecutiveOnes(test);
    cout << result << endl;
    auto template_test = int_sequence<TEST_CASE_485>();
    int template_result = findMaxConsecutiveOnes(template_test);
    cout<<template_result<<endl;
}