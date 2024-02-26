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

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(char data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    char peek() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return '\0';
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

class ExpressionConverter {
public:
    static bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

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

    static string infixToPostfix(string infix) {
        Stack operatorStack;
        string postfix;
        for (char& c : infix) {
            if (isalnum(c)) { // If operand, append to postfix
                postfix += c;
            } else if (c == '(') { // If left parenthesis, push onto stack
                operatorStack.push(c);
            } else if (c == ')') { // If right parenthesis, pop stack until left parenthesis
                while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                    postfix += operatorStack.peek();
                    operatorStack.pop();
                }
                operatorStack.pop(); // Discard the '('
            } else { // If operator
                while (!operatorStack.isEmpty() && precedence(c) <= precedence(operatorStack.peek())) {
                    postfix += operatorStack.peek();
                    operatorStack.pop();
                }
                operatorStack.push(c);
            }
        }
        // Pop remaining operators from stack
        while (!operatorStack.isEmpty()) {
            postfix += operatorStack.peek();
            operatorStack.pop();
        }
        return postfix;
    }

    static TreeNode* buildExpressionTree(string postfix) {
        stack<TreeNode*> st;
        for (char& c : postfix) {
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
};

class ExpressionTree {
public:
    static void printInfix(TreeNode* root) {
        if (root) {
            if (ExpressionConverter::isOperator(root->data)) {
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

    static void printPrefix(TreeNode* root) {
        if (root) {
            cout << root->data;
            printPrefix(root->left);
            printPrefix(root->right);
        }
    }

    static void printPostfix(TreeNode* root) {
        if (root) {
            printPostfix(root->left);
            printPostfix(root->right);
            cout << root->data;
        }
    }
};

int main() {
    string infix;
    cout << "Enter the infix expression: ";
    getline(cin, infix);

    string postfix = ExpressionConverter::infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    TreeNode* root = ExpressionConverter::buildExpressionTree(postfix);

    cout << "Infix expression: ";
    ExpressionTree::printInfix(root);
    cout << endl;

    cout << "Prefix expression: ";
    ExpressionTree::printPrefix(root);
    cout << endl;

    cout << "Postfix expression: ";
    ExpressionTree::printPostfix(root);
    cout << endl;

    return 0;
}
