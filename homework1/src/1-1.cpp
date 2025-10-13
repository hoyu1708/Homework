#include <iostream>
#include <vector>
using namespace std;

// ------------------------
// ���j����
// ------------------------
int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann_recursive(m - 1, 1);
    return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

// ------------------------
// �D���j�����]�ϥ� stack �������j�^
// ------------------------
int ackermann_iterative(int m, int n) {
    struct Frame { int m; int n; bool inner_done; };
    vector<Frame> stack;
    stack.push_back({ m, n, false });
    int result = 0;

    while (!stack.empty()) {
        auto& top = stack.back();
        if (top.m == 0) {
            result = top.n + 1;
            stack.pop_back();
            if (!stack.empty()) {
                stack.back().n = result; // �⵲�G�Ǧ^�~�h
            }
        }
        else if (top.n == 0) {
            top.m -= 1;
            top.n = 1;
        }
        else if (!top.inner_done) {
            top.inner_done = true;
            stack.push_back({ top.m, top.n - 1, false }); // �p�⤺�h
        }
        else {
            top.m -= 1;
            top.n = result;  // �Τ��h���G��s�~�h
            top.inner_done = false;
        }
    }

    return result;
}

// ------------------------
// �D�{��
// ------------------------
int main() {
    int m = 3, n = 2;

    cout << "Recursive: Ackermann(" << m << "," << n << ") = "
        << ackermann_recursive(m, n) << endl;

    cout << "Iterative: Ackermann(" << m << "," << n << ") = "
        << ackermann_iterative(m, n) << endl;
}
