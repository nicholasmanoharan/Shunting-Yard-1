#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

// Binary Tree Node
class TreeNode {
public:
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Stack and Queue using Linked List
class Container {
private:
    struct Node {
        char data;
        Node* next;
        Node(char val) : data(val), next(nullptr) {}
    };

    Node* top;
    Node* front;
    Node* rear;

public:
    Container() : top(nullptr), front(nullptr), rear(nullptr) {}

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Container is empty!" << endl;
            return '\0';
        }
        char val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    char peek() {
        if (isEmpty()) {
            cout << "Container is empty!" << endl;
            return '\0';
        }
        return top->data;
    }

    void enqueue(char val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    char dequeue() {
        if (isEmpty()) {
            cout << "Container is empty!" << endl;
            return '\0';
        }
        char val = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == nullptr && front == nullptr;
    }
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to check precedence of operators
int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

// Shunting Yard Algorithm
string shuntingYard(string infix) {
    Container operatorStack;
    string postfix = "";

    for (char& token : infix) {
        if (isdigit(token)) {
            postfix += token;
            postfix += ' '; // Adding space as delimiter
        } else if (token == '(') {
            operatorStack.push(token);
        } else if (token == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfix += operatorStack.pop();
                postfix += ' '; // Adding space as delimiter
            }
            operatorStack.pop(); // Discard '('
        } else if (isOperator(token)) {
            while (!operatorStack.isEmpty() && precedence(token) <= precedence(operatorStack.peek())) {
                postfix += operatorStack.pop();
                postfix += ' '; // Adding space as delimiter
            }
            operatorStack.push(token);
        }
    }

    // Empty the remaining operators in stack
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
        postfix += ' '; // Adding space as delimiter
    }

    return postfix;
}

// Build Expression Tree from Postfix Notation
TreeNode* buildExpressionTree(string postfix) {
    stack<TreeNode*> expressionStack;

    for (char& token : postfix) {
        if (isdigit(token)) {
            TreeNode* newNode = new TreeNode(token);
            expressionStack.push(newNode);
        } else if (isOperator(token)) {
            TreeNode* rightNode = expressionStack.top();
            expressionStack.pop();
            TreeNode* leftNode = expressionStack.top();
            expressionStack.pop();

            TreeNode* newNode = new TreeNode(token);
            newNode->left = leftNode;
            newNode->right = rightNode;

            expressionStack.push(newNode);
        }
    }

    return expressionStack.top();
}

// Recursive function to print infix expression from Expression Tree
void printInfix(TreeNode* root) {
    if (root) {
        if (isOperator(root->data)) {
            cout << "(";
            printInfix(root->left);
            cout << root->data;
            printInfix(root->right);
            cout << ")";
        } else {
            cout << root->data;
        }
    }
}

// Recursive function to print prefix expression from Expression Tree
void printPrefix(TreeNode* root) {
    if (root) {
        cout << root->data;
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

// Recursive function to print postfix expression from Expression Tree
void printPostfix(TreeNode* root) {
    if (root) {
        printPostfix(root->left);
        printPostfix(root->right);
        cout << root->data;
    }
}

int main() {
    string infixExpression;
    cout << "Enter the infix expression: ";
    getline(cin, infixExpression);

    string postfixExpression = shuntingYard(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    TreeNode* expressionTree = buildExpressionTree(postfixExpression);

    cout << "Infix expression: ";
    printInfix(expressionTree);
    cout << endl;

    cout << "Prefix expression: ";
    printPrefix(expressionTree);
    cout << endl;

    cout << "Postfix expression: ";
    printPostfix(expressionTree);
    cout << endl;

    return 0;
}
