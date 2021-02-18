#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

class Solution
{
public:
    vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c)
    {
        if (nums.size())
        {
            if (nums[0].size() * nums.size() == r * c)
            {
                vector<vector<int>> Answer(r, vector<int>(c));
                int bound = r * c;
                int vc = nums[0].size();
                for (int index = 0; index < bound; index++)
                {
                    Answer[index / c][index % c] = nums[index / vc][index % vc];
                }
                return Answer;
            }
        }
        return nums;
    }
};
template <int... Ints>
using int_sequence = integer_sequence<int, Ints...>;

template <int Itop, int... I>
constexpr int gethead(int_sequence<Itop, I...>) { return Itop; }

template <int index, int Itop, int... I>
constexpr int getvalue(int_sequence<Itop, I...>)
{
    if constexpr (index == 0)
        return Itop;
    else
        return getvalue<index - 1>(int_sequence<I...>());
}

template <int row, int columns, int... I>
struct Matrix
{
public:
    static const int r = row;
    static const int c = columns;
    template <int i, int j>
    static const int value = getvalue<i * columns + j>(int_sequence<I...>());
};

template <int nrow, int ncolumns, int row, int columns, int... I>
constexpr auto matrixReshape(Matrix<row, columns, I...> _)
{
    if constexpr (nrow * ncolumns == row * columns)
        return Matrix<nrow, ncolumns, I...>();
    else
        return _;
}

template <int index = 0, int... I>
void printN(Matrix<I...> _)
{
    if constexpr (index >= _.r * _.c)
        return;
    else
    {
        cout << getvalue<index + 2>(int_sequence<I...>()) << " ";
        if constexpr ((index + 1) % _.c == 0)
            cout << endl;
        printN<index + 1>(_);
    }
}

int main()
{
    auto template_test = Matrix<2, 2, 1, 2, 3, 4>();
    printN(template_test);
    auto template_result = matrixReshape<1, 4>(template_test);
    printN(template_result);
    vector<vector<int>> test = {{1, 2}, {3, 4}};
    Solution s;
    auto result = s.matrixReshape(test, 1, 4);
    for (auto i : result[0])
    {
        cout << i << " ";
    }
    cout << endl;
}