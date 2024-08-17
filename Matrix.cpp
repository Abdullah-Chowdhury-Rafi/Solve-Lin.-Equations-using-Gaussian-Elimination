#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
const double BIG = 1e7 + 1;
// This function takes two rows and their corresponding pivots and turns one of their pivots 0 using the other row. If, p_a is the pivot of the
// row R_a, and p_b is the pivot of row R_b, then this function is equivalent to R_a -> R_a - R_b(p_a/p_b)
vector<float> turn_pos_zero(vector<float> a, vector<float> b, float p_a, float p_b, int size)
{
    float m = abs(p_a / p_b), piv = BIG;
    vector<float> res;
    for (int i = 0; i < size; i++)
    {
        if (p_a > 0 != p_b > 0)
            res.pb((a[i] + b[i] * m));
        else
            res.pb((a[i] - b[i] * m));
        if ((abs(res[i]) < 1.00e-006))
            res[i] = 0;
        if (res[i] != 0 && piv == BIG)
            piv = i;
    }
    res.pb(piv);
    return res;
}
// This function takes a row and divides all its elements by the pivot of the row, effectively turning its pivot into 1
vector<float> turn_piv_one(vector<float> a, float p_a, int size)
{
    vector<float> res;
    for (int i = 0; i < size; i++)
    {
        res.pb(a[i] / p_a);
        if ((abs(res[i]) < 1.00e-006))
            res[i] = 0;
    }
    return res;
}
bool comp(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}
int main()
{
    int n, m, i, j;
    cin >> m;
    cin >> n;
    vector<float> arr[m];
    float use;
    // inputting the augmented matrix of the system of equations in an array of vectors
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            cin >> use;
            arr[i].pb(use);
        }
    }
    // storing the position of the pivot(first non-zero entry) of every row in a vector of pairs and determining the number of all-zero rows
    vector<pair<int, int>> piv;
    int zero = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (arr[i][j] != 0)
            {
                piv.pb({i, j});
                break;
            }
            else if (j == n - 1)
            {
                piv.pb({i, BIG});
                zero++;
            }
        }
    }
    // sorting this pivot vector by putting the row with the lefttmost pivot first
    sort(piv.begin(), piv.end(), comp);
    vector<float> s_arr[m];
    // storing the rows in this order in a new array of vectors
    for (i = 0; i < m; i++)
        s_arr[i] = arr[piv[i].first];
    // Transforming the matrix into its row echelon form:
    // if two rows have pivots in the same position then turning the pivot of the lower row 0 using the turn_pos_zero function. If the row turns
    // all-zero after this operation then interchanging it with the last row that is not all-zero. Else interchanging the consecuetive rows if
    // the pivot of the current row is to the right of the pivot of the row below it. Furthermore, coducting these same checks if the pivot of
    // the row above the current one is in the same position as the pivot of the one below it.
    for (i = 0; i < m - zero; i++)
    {
        if (piv[i].s == piv[i + 1].s)
        {
            s_arr[i + 1] = turn_pos_zero(s_arr[i + 1], s_arr[i], s_arr[i + 1][piv[i + 1].s], s_arr[i][piv[i].s], n);
            piv[i + 1].s = s_arr[i + 1][n];
            s_arr[i + 1].pop_back();
            if (piv[i + 1].s == BIG)
            {
                pair<int, int> b = piv[m - zero - 1];
                piv[m - zero - 1] = piv[i + 1];
                piv[i + 1] = b;
                vector<float> c = s_arr[m - zero - 1];
                s_arr[m - zero - 1] = s_arr[i + 1];
                s_arr[i + 1] = c;
                if (piv[i].s >= piv[i + 1].s)
                    i--;
                zero++;
                continue;
            }
        }
        else if (piv[i].s > piv[i + 1].s && i < m - zero - 1)
        {
            pair<int, int> b = piv[i];
            piv[i] = piv[i + 1];
            piv[i + 1] = b;
            vector<float> c = s_arr[i];
            s_arr[i] = s_arr[i + 1];
            s_arr[i + 1] = c;
            if (i != 0)
                if (piv[i - 1].s >= piv[i].s)
                    i -= 2;
        }
    }
    cout << "\nRow Echelon Form:\n";
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            cout << s_arr[i][j] << " ";
        cout << "\n";
    }
    // Transforming the matrix into its reduced row echelon form:
    // For every row, checking if any row above the current one has any elements in the same position of the pivot of this one and turning that
    // element into zero if found using the turn_pos_zero function. Next, checking if the pivot of the current row is anything but 1, and in that
    // case turning it into 1 by applying the turn_piv_one function of the row.
    for (i = 0; i < m - zero; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (s_arr[j][piv[i].s] != 0)
            {
                s_arr[j] = turn_pos_zero(s_arr[j], s_arr[i], s_arr[j][piv[i].s], s_arr[i][piv[i].s], n);
                piv[j].s = s_arr[j][n];
                s_arr[j].pop_back();
            }
        }
        if (s_arr[i][piv[i].s] != 1)
        {
            s_arr[i] = turn_piv_one(s_arr[i], s_arr[i][piv[i].s], n);
        }
    }
    cout << "\nReduced Row Echelon Form:\n";
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            cout << s_arr[i][j] << " ";
        cout << "\n";
    }
    cout << "\nSolution:\n";
    // Finding the solution of the system:
    // if the number of unknowns is equal to the number of equations and there is no all-zero row then there is only one unique solution where
    // the last elements of every row of the augmented matrix in reduced row echelon form are the solutions to every correspoding unknown in
    // order of the rows. If all the last elements are zero in this case, then this is the trivial solution and there is but no other solution.
    if (n - m == 1 && zero == 0)
    {
        zero = 0;
        for (i = 0; i < m; i++)
            if (s_arr[i][n - 1] == 0)
                zero++;
        if (zero == m)
            cout << "  The trivial solution is the only solution for the given system of equations: \n \n";
        else
            cout << "  There exists only one unique non-trivial solution for given system of equations:\n \n";
        for (i = 0; i < m; i++)
        {
            cout << "  X_" << i + 1 << " = " << s_arr[i][n - 1] << "\n";
        }
    }
    // If the number of unknowns is greater than the number of equations or there is atleast one all-zero row then infinite solutions exist. We
    // can allot any value we want to the extra unknowns and the corresponding unknowns of the all-zero rows One of the solutions is alloting
    // 1 to all the extra unknowns and solving for the other unknowns.
    else
    {
        cout << "  There exists infinite solutions for given system of equations. One of them is: \n \n";
        for (i = 0; i < m - zero; i++)
        {
            use = s_arr[i][n - 1];
            for (j = piv[i].s + 1; j < n - 1; j++)
                use -= s_arr[i][j];
            cout << "  X_" << i + 1 << " = " << use << "\n";
        }
        for (i = m - zero; i < n - 1; i++)
        {
            cout << "  X_" << i + 1 << " = " << 1 << "\n";
        }
    }
}
//ACR
//Happy Coding!!
