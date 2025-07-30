#include <stdio.h>
#include <stdlib.h>

// Binary Search Tree Node Structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ==================== NODE CREATION ====================
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ==================== INSERTION ====================
TreeNode* insert(TreeNode* root, int value) {
    // Base case: create new node
    if (root == NULL) {
        return createNode(value);
    }
    
    // Recursive insertion
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // If value == root->data, do nothing (no duplicates)
    
    return root;
}

// ==================== SEARCH ====================
TreeNode* search(TreeNode* root, int value) {
    // Base cases
    if (root == NULL || root->data == value) {
        return root;
    }
    
    // Search left or right subtree
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Iterative search (more efficient)
TreeNode* searchIterative(TreeNode* root, int value) {
    while (root != NULL && root->data != value) {
        if (value < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// ==================== FIND MINIMUM ====================
TreeNode* findMin(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    
    // Keep going left to find minimum
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

// ==================== FIND MAXIMUM ====================
TreeNode* findMax(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    
    // Keep going right to find maximum
    while (root->right != NULL) {
        root = root->right;
    }
    
    return root;
}

// ==================== DELETION ====================
TreeNode* delete(TreeNode* root, int value) {
    // Base case
    if (root == NULL) {
        return root;
    }
    
    // Find the node to delete
    if (value < root->data) {
        root->left = delete(root->left, value);
    } else if (value > root->data) {
        root->right = delete(root->right, value);
    } else {
        // Node to be deleted found
        
        // Case 1: Node has no children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Case 2: Node has one child
        else if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: Node has two children
        // Find inorder successor (minimum in right subtree)
        else {
            TreeNode* temp = findMin(root->right);
            
            // Replace root's data with successor's data
            root->data = temp->data;
            
            // Delete the successor
            root->right = delete(root->right, temp->data);
        }
    }
    
    return root;
}

// ==================== TRAVERSALS ====================

// Inorder Traversal (Left, Root, Right) - gives sorted order
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder Traversal (Root, Left, Right)
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Postorder Traversal (Left, Right, Root)
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// ==================== UTILITY FUNCTIONS ====================

// Calculate height of tree
int height(TreeNode* root) {
    if (root == NULL) {
        return -1;  // or 0, depending on convention
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Count total nodes
int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Check if tree is valid BST
int isValidBST(TreeNode* root, int min, int max) {
    if (root == NULL) {
        return 1; // true
    }
    
    if (root->data <= min || root->data >= max) {
        return 0; // false
    }
    
    return isValidBST(root->left, min, root->data) && 
           isValidBST(root->right, root->data, max);
}

// Wrapper function for BST validation
int isBST(TreeNode* root) {
    return isValidBST(root, INT_MIN, INT_MAX);
}

// Free entire tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Print tree structure (for debugging)
void printTree(TreeNode* root, int space) {
    const int COUNT = 10;
    if (root == NULL) return;
    
    space += COUNT;
    printTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    printTree(root->left, space);
}

// ==================== MAIN PROGRAM EXAMPLE ====================
int main() {
    TreeNode* root = NULL;
    
    // Insert values
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("BST created with values: 50, 30, 70, 20, 40, 60, 80\n\n");
    
    // Search for a value
    TreeNode* result = search(root, 40);
    if (result != NULL) {
        printf("Found: %d\n", result->data);
    } else {
        printf("Value 40 not found\n");
    }
    
    // Print traversals
    printf("\nInorder traversal (sorted): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");
    
    // Print tree structure
    printf("\nTree structure:\n");
    printTree(root, 0);
    
    // Display tree properties
    printf("\nTree height: %d\n", height(root));
    printf("Total nodes: %d\n", countNodes(root));
    printf("Is valid BST: %s\n", isBST(root) ? "Yes" : "No");
    
    // Delete a node
    printf("\nDeleting node 30...\n");
    root = delete(root, 30);
    
    printf("Inorder after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    // Clean up memory
    freeTree(root);
    
    return 0;
}