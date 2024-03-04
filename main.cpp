#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>

using namespace std;

class TreeNode {
public:
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char d) : data(d), left(nullptr), right(nullptr) {}
};

class Node {
public:
    char data;
    Node* next;

    Node(char d) : data(d), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(char data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "The stack is empty" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    char peek() {
        if (isEmpty()) {
            cout << "The stack is empty" << endl;
            return '\0';
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class ExpressionConverter {
public:
    static string infixToPostfix(string infix) {
        Stack operatorStack;
        string postfix;
        for (auto it = infix.begin(); it != infix.end(); ++it) {
            char& c = *it;
            if (isalnum(c)) { // If operand, append to postfix
                postfix += c;
                postfix += ' '; // Add space after operand
            } else if (c == '(') { // If left parenthesis, push onto stack
                operatorStack.push(c);
            } else if (c == ')') { // If right parenthesis, pop stack until left parenthesis
                while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                    postfix += operatorStack.peek();
                    postfix += ' '; // Add space after operator
                    operatorStack.pop();
                }
                operatorStack.pop(); // Discard the '('
            } else { // If operator
                while (!operatorStack.isEmpty() && precedence(c) <= precedence(operatorStack.peek())) {
                    postfix += operatorStack.peek();
                    postfix += ' '; // Add space after operator
                    operatorStack.pop();
                }
                operatorStack.push(c);
            }
        }
        // Pop remaining operators from stack
        while (!operatorStack.isEmpty()) {
            postfix += operatorStack.peek();
            postfix += ' '; // Add space after operator
            operatorStack.pop();
        }
        return postfix;
    }

    static TreeNode* buildExpressionTree(string postfix) {
        stack<TreeNode*> st;
        for (auto it = postfix.begin(); it != postfix.end(); ++it) {
            char& c = *it;
            if (isalnum(c)) {
                TreeNode* newNode = new TreeNode(c);
                st.push(newNode);
            } else {
                TreeNode* newNode = new TreeNode(c);
                newNode->right = st.top();
                st.pop();
                newNode->left = st.top();
                st.pop();
                st.push(newNode);
            }
        }
        return st.top();
    }

    static bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

private:
    static int precedence(char c) {
        if (c == '^')
            return 3;
        else if (c == '*' || c == '/')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return -1;
    }
};

class ExpressionTree {
private:
    static void printInfixRecursive(TreeNode* root) {
        if (root) {
            bool needParentheses = false;
            if (root->left && ExpressionConverter::isOperator(root->left->data)) {
                needParentheses = true;
            }
            if (needParentheses) cout << "(";
            printInfixRecursive(root->left);
            if (needParentheses) cout << ")";
            cout << root->data;
            needParentheses = false;
            if (root->right && ExpressionConverter::isOperator(root->right->data)) {
                needParentheses = true;
            }
            if (needParentheses) cout << "(";
            printInfixRecursive(root->right);
            if (needParentheses) cout << ")";
        }
    }

    static void printPrefixRecursive(TreeNode* root) {
        if (root) {
            cout << root->data;
            cout << " ";
            printPrefixRecursive(root->left);
            printPrefixRecursive(root->right);
        }
    }

    static void printPostfixRecursive(TreeNode* root) {
        if (root) {
            printPostfixRecursive(root->left);
            printPostfixRecursive(root->right);
            cout << root->data;
            cout << " ";
        }
    }

public:
    static void printInfix(TreeNode* root) {
        printInfixRecursive(root);
    }

    static void printPrefix(TreeNode* root) {
        printPrefixRecursive(root);
    }

    static void printPostfix(TreeNode* root) {
        printPostfixRecursive(root);
    }
};

int main() {
    string infix;
    cout << "Enter the infix expression: ";
    getline(cin, infix);

    string postfix = ExpressionConverter::infixToPostfix(infix);
    cout << "Infix expression: " << infix << endl;
    cout << "Postfix expression: " << postfix << endl;

    TreeNode* root = ExpressionConverter::buildExpressionTree(postfix);

    cout << "Expression tree: " << endl;
    cout << "Infix notation: ";
    ExpressionTree::printInfix(root);
    cout << endl;

    cout << "Prefix notation: ";
    ExpressionTree::printPrefix(root);
    cout << endl;

    cout << "Postfix notation: ";
    ExpressionTree::printPostfix(root);
    cout << endl;

    return 0;
}
