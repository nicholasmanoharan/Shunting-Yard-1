#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cmath>

using namespace std;


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


class Stack {
private:
    struct Node {
        char data;
        Node* next;
        Node(char val) : data(val), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
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
            cout << "Stack is empty!" << endl;
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
    struct Node {
        char data;
        Node* next;
        Node(char val) : data(val), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

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
            cout << "Queue is empty!" << endl;
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
        return front == nullptr;
    }
};


bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

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


string shuntingYard(string infix) {
    Stack operatorStack;
    string postfix = "";

    for (char& token : infix) {
        if (isdigit(token)) {
            postfix += token;
            postfix += ' '; 
        } else if (token == '(') {
            operatorStack.push(token);
        } else if (token == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfix += operatorStack.pop();
                postfix += ' '; 
            }
            operatorStack.pop(); 
        } else if (isOperator(token)) {
            while (!operatorStack.isEmpty() && precedence(token) <= precedence(operatorStack.peek())) {
                postfix += operatorStack.pop();
                postfix += ' '; 
            }
            operatorStack.push(token);
        }
    }

   
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
        postfix += ' '; 
    }

    return postfix;
}


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


void printPrefix(TreeNode* root) {
    if (root) {
        cout << root->data;
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


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
