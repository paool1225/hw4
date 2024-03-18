#ifndef RECCHECK
#include <algorithm>
#include <utility>
#endif

#include "equal-paths.h"
using namespace std;


pair<int, bool> checkEqualPaths(Node* node, int depth);

// Implementation of the equalPaths function that initiates the recursive checking.
bool equalPaths(Node *root) {
    if (!root) return true;

    auto result = checkEqualPaths(root, 0);

    return result.second;
}

pair<int, bool> checkEqualPaths(Node* node, int depth) {
    if (!node) {
        return {depth, true};
    }

    auto leftResult = checkEqualPaths(node->left, depth + 1);
    auto rightResult = checkEqualPaths(node->right, depth + 1);

    bool isValid = leftResult.second && rightResult.second && (!node->left || !node->right || leftResult.first == rightResult.first);

    return {max(leftResult.first, rightResult.first), isValid};
}
