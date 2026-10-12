#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from preorder traversal with -1 as null
TreeNode* buildTree(vector<int>& preorder, int& index) {
    if (index >= preorder.size() || preorder[index] == -1) {
        index++;
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(preorder[index++]);
    node->left = buildTree(preorder, index);
    node->right = buildTree(preorder, index);
    
    return node;
}

// Find depth and parent of a node
pair<int, int> findDepthAndParent(TreeNode* root, int target, int depth, int parent) {
    if (!root) return {-1, -1};
    
    if (root->val == target) {
        return {depth, parent};
    }
    
    // Search in left subtree
    auto left = findDepthAndParent(root->left, target, depth + 1, root->val);
    if (left.first != -1) return left;
    
    // Search in right subtree
    return findDepthAndParent(root->right, target, depth + 1, root->val);
}

int main() {
    int q;
    cin >> q;
    
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    // Read the rest of the line (the tree data)
    string treeLine;
    cin.ignore(); // Ignore the newline after the last query
    getline(cin, treeLine);
    
    // Parse the tree data
    vector<int> preorder;
    stringstream ss(treeLine);
    int val;
    while (ss >> val) {
        preorder.push_back(val);
    }
    
    // Build the tree
    int index = 0;
    TreeNode* root = buildTree(preorder, index);
    
    // Process queries
    for (auto& query : queries) {
        int x = query.first;
        int y = query.second;
        
        auto depthParentX = findDepthAndParent(root, x, 0, -1);
        auto depthParentY = findDepthAndParent(root, y, 0, -1);
        
        // Check if they are cousins: same depth but different parents
        if (depthParentX.first == depthParentY.first && 
            depthParentX.first != -1 && 
            depthParentX.second != depthParentY.second) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}