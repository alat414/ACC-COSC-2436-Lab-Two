#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <vector>

// The DocTest tutorial is located here:
// https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template<typename T>
class StackADT 
{
    public:
        virtual bool isEmpty() const = 0;

        virtual bool push(const T & value) = 0;
        virtual T peek() const = 0;
        virtual bool pop() = 0;
};

constexpr int MIN_ARRAY_SIZE=2;

template<typename T, int N>
class ArrayStack final : public StackADT<T> 
{
    private:
        int topIndex;
        T array[N] {};
    public:
        ArrayStack() : topIndex(-1) 
        {
            static_assert(N >= MIN_ARRAY_SIZE);
        }

        bool isEmpty() const override 
        {
            // TODO begin
            return topIndex < 0;
            // TODO end
        }

        bool push(const T & value) override 
        {
            // TODO begin
            bool result = false;
            if(topIndex < MIN_ARRAY_SIZE - 1)
            {
                topIndex++;
                array[topIndex] = value;
                result = true;
            }
            return result;
            // TODO: Replace
            // TODO end
        }

        T peek() const override 
        {
            if(isEmpty()) 
            {
                throw std::logic_error("Peek on empty.");
            }
            // TODO begin
            return array[topIndex]; // TODO: replace stub.
            // TODO end
        }

        bool pop() override 
        {
            bool result = false;
            if(!isEmpty()) 
            {
                topIndex--;
                result = true;
            }
            return result;
            // TODO begin
            // Replace stub.
            // TODO end
        }
};

template<typename T>
class Node 
{
    private:
        T value;
        Node* next;

    public:
        Node() : value(T()), next(nullptr) 
        {

        }
        Node(T value, Node* next) : value(value), next(next) 
        {

        }

        T getValue() const 
        {
            return value;
        }

        Node* getNext() const  
        {
            return next;
        }

        void setNext(Node* n) 
        {
            next = n;
        }

        void setValue(const T & v) 
        {
            value = v;
        }
};

// Rule of Three / Rule of Five
//
// In classes that manage dynamic resources (like our ListStack, which allocates
// Nodes on the heap), you must implement the "special member functions":
//
//  - Copy constructor
//  - Copy assignment operator
//  - Destructor
//
// This is called the "Rule of Three". If you also implement move semantics
// (move constructor, move assignment operator), it becomes the "Rule of Five".
//
// If you omit them, the compiler generates shallow copies by default, which
// would break our linked structure (two stacks pointing to the same Nodes).
//
// We demonstrate all five here in ListStack.
template<typename T>
class ListStack : public StackADT<T> 
{
    private:
        Node<T>* topPtr;

    public:
        ListStack() : topPtr(nullptr) 
        {
        }
        ~ListStack() 
        {
            while(!isEmpty()) 
            {
                pop();
            }
        }

        T top() const
        {
            if(isEmpty())
            {
                throw std::underflow_error("Stack is empty");
            }
            return topPtr->getValue();
        }
    

        // Copy constructor
        ListStack(const ListStack & other) 
        {
            // TODO begin
            Node<T>* originalChainPtr = other.topPtr;
    
            if (originalChainPtr == nullptr)
            {
                topPtr = nullptr;
            }
            else
            {
                topPtr = new Node<T>();
                
                topPtr->setValue(originalChainPtr->getValue());

                Node<T>* newChainPtr = topPtr;
               
                originalChainPtr = originalChainPtr->getNext();

                while(originalChainPtr != nullptr)
                {
                    T nextItem = originalChainPtr->getValue();
                    
                    Node<T>* newNodePtr = new Node<T>(nextItem, nullptr);
                    
                    newChainPtr->setNext(newNodePtr);
                    
                    newChainPtr = newChainPtr->getNext();
                    
                    originalChainPtr = originalChainPtr->getNext();
                }
                newChainPtr->setNext(nullptr);
            }
            // TODO end
        }

        // Copy assignment operator
        ListStack& operator=(const ListStack& other) 
        {
            // TODO begin
            if (this != &other)
            {
                ListStack temp(other);
                std::swap(topPtr,temp.topPtr);
            }
            return *this;
            // TODO end
        }

        // Move constructor
        ListStack(ListStack && other) noexcept
            : topPtr(nullptr)
        {
            // TODO begin
            std::swap(topPtr,other.topPtr);
            // TODO end
        }

        // Move assignment operator
        ListStack& operator=(ListStack&& other) noexcept 
        {
            // TODO begin
            if (this != &other)
            {
                ListStack temp(std::move(other));
                std::swap(topPtr,temp.topPtr);
            }
            return *this;
            // TODO end
        }

        bool isEmpty() const override 
        {
            // TODO begin
            return topPtr == nullptr; // TODO: replace stub
            // TODO end
        }

        bool push(const T & value) override 
        {
            // TODO begin
            Node<T>* newNodePtr = new Node<T>(value, topPtr);
            topPtr = newNodePtr;
            return true; // TODO: replace stub
            // TODO end
        }

        T peek() const override 
        {
            if(isEmpty())  
            {
                throw std::logic_error("Peek on empty.");
            }
            // TODO begin
            return topPtr->getValue(); // TODO: Replace stub.
            // TODO end
        }

        bool pop() override 
        {
            // TODO begin
            bool result = false;
            if(!isEmpty()) 
            {
                Node<T>* nodeToDeletePtr = topPtr;
                
                topPtr = topPtr->getNext();

                nodeToDeletePtr->setNext(nullptr);
                
                delete nodeToDeletePtr;
                
                nodeToDeletePtr = nullptr;

                return true;
            }
            
            return false; // TODO: Replace stub.
            // TODO end
        }
};

// Must use a stack.
bool areCurlyBracesMatched(const std::string & inputString) 
{
    // TODO begin
    ListStack<char>currentStack; //a new empty stack
    bool validBalance = true;
    
    for (size_t i = 0; i < inputString.length(); i++)
    {
        char ch = inputString[i];

        if(ch == '{')
        {
            currentStack.push(ch);
        }
        else if (ch == '}')
        {
            if(currentStack.isEmpty())
            {
                return false;
            }
            currentStack.pop();
        }
    }
    return currentStack.isEmpty();
}
// TODO end

bool isPalindrome(const std::string & inputString) 
{
    // TODO begin
    ListStack<char>newStack;

    for (char ch : inputString)
    {
        newStack.push(ch);
    }

    for(char ch : inputString)
    {
        if(newStack.isEmpty() || ch != newStack.top())
        {
            return false;
        }
        newStack.pop();
    }
    return true;

}

std::string reversedString(const std::string & inputString) 
{
    // TODO begin
    ListStack<char> charStack;
    std::string result;

    for(char ch : inputString)
    {
        charStack.push(ch);
    }
    
    while(!charStack.isEmpty())
    {
        result += charStack.top();
        charStack.pop();
    }

    return result;
    // TODO end
}

// Helper for infixToPostFix.
int precedence(char op) 
{
    if(op == '^')
    {
        return 3;
    }
    if(op == '*' || op == '/') 
    {
        return 2;
    } 
    else 
    {
        assert(op == '+' || op == '-');
        return 1;
    }
}

// Helper for infixToPostFix.
bool isOperator(char ch) 
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isRightAssociative(char ch)
{
    return ch == '^';
}

// Helper for infixToPostFix.
bool isOperand(char ch) 
{
    // Cast is necessary because isalpha expects unsigned char. Passing in char is undefined.
    return std::isalpha(static_cast<unsigned char>(ch));
}

std::string infixToPostFix(const std::string & infix) 
{
    // TODO begin
    ListStack<char>signStack;
    std::string currentInput;

    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];

        if(c == ' ')
        {
            continue;
        }
        else if ((c >= 'a' && c <= 'z') ||
                 (c >= 'A' && c <= 'Z') ||
                 (c >= '0' && c <= '9'))
        {
            currentInput += c;
        }
        else if (c == '(')
        {
            signStack.push('(');
        }
        else if (c == ')')
        {
            while(!signStack.isEmpty() && signStack.top() != '(')
            {
                currentInput += signStack.top();
                signStack.pop();
            }
            if (signStack.isEmpty())
            {
                throw std::invalid_argument("Mismatching parentheses");
            }
            signStack.pop();
        }
        else if (isOperator(c))
        {
            while(!signStack.isEmpty() && signStack.top() != '(' &&
                  (precedence(signStack.top()) > precedence(c) || 
                  (precedence(signStack.top()) == precedence(c) && !isRightAssociative(c))))
            {
                currentInput += signStack.top();
                signStack.pop();
            }
            signStack.push(c);
        }
        else 
        {
            throw std::invalid_argument("Invalid character in expression");
        }
    }
    while (!signStack.isEmpty())
    {
        if (signStack.top() == '(')
        {
            throw std::invalid_argument("Mismatching parentheses");
        }
        currentInput += signStack.top();
        signStack.pop();
    }
    return currentInput; // TODO: replace stub.
    // TODO end
}

// ==============================
// Guided Test Plan (Do in order)
// ==============================

// Small helper: drain a stack into a vector from top→bottom (destructive).
template <typename Stack, typename T>
static std::vector<T> drain_to_vec(Stack & s) 
{
    std::vector<T> out;
    while (!s.isEmpty()) 
    {
        out.push_back(s.peek());
        s.pop();
    }
    return out;
}

// 01) Do these tests FIRST: ArrayStack basics (push/peek/pop/isEmpty)
TEST_CASE("[01] ArrayStack — basic operations") 
{
    ArrayStack<int, MIN_ARRAY_SIZE> s;
    CHECK(s.isEmpty());

    CHECK(s.push(10));
    CHECK_FALSE(s.isEmpty());
    CHECK(s.peek() == 10);

    CHECK(s.push(20));
    CHECK(s.peek() == 20);

    CHECK(s.pop());
    CHECK(s.peek() == 10);

    CHECK(s.pop());
    CHECK(s.isEmpty());
}

// 02) NEXT: ListStack basics (push/peek/pop/isEmpty)
// Make sure basic linked structure operations work exactly like the array version.
TEST_CASE("[02] ListStack — basic operations") 
{
    ListStack<int> s;
    CHECK(s.isEmpty());

    CHECK(s.push(10));
    CHECK_FALSE(s.isEmpty());
    CHECK(s.peek() == 10);

    CHECK(s.push(20));
    CHECK(s.peek() == 20);

    CHECK(s.pop());
    CHECK(s.peek() == 10);

    CHECK(s.pop());
    CHECK(s.isEmpty());
}

// 03) THEN: Copy constructor (deep copy)
// - Both stacks should contain the same sequence (top→bottom).
// - Mutating the original after copying should NOT affect the copy.
// - Popping from both should yield identical sequences.
// - Self-consistency: copying an empty stack yields empty.
TEST_CASE("[03] ListStack — copy constructor deep copy") 
{
    // Build original: top is 3
    ListStack<int> a;
    a.push(1);
    a.push(2);
    a.push(3);

    // Copy construct
    ListStack<int> b(a);
    CHECK_FALSE(a.isEmpty());
    CHECK_FALSE(b.isEmpty());
    CHECK(a.peek() == 3);
    CHECK(b.peek() == 3);

    // Mutate original; copy must be unaffected
    a.pop();          // remove 3
    a.push(42);       // new top is 42
    CHECK(a.peek() == 42);
    CHECK(b.peek() == 3);  // copy's top remains 3

    // Drain both to verify full order
    auto va = drain_to_vec<ListStack<int>, int>(a); // returns {42,2,1}
    auto vb = drain_to_vec<ListStack<int>, int>(b); // returns {3,2,1}
    CHECK(va == std::vector<int>({42, 2, 1}));
    CHECK(vb == std::vector<int>({3, 2, 1}));

    // Copying an empty stack
    ListStack<int> empty;
    ListStack<int> emptyCopy(empty);
    CHECK(empty.isEmpty());
    CHECK(emptyCopy.isEmpty());
}

// 04) NEXT: Copy assignment operator (=)
// - Deep copy behavior.
// - Previous contents of LHS are discarded safely.
// - Self-assignment should not corrupt.
TEST_CASE("[04] ListStack — copy assignment operator") 
{
    ListStack<int> src;
    src.push(1);
    src.push(2);
    src.push(3);

    ListStack<int> dst;
    dst.push(9); // will be overwritten
    dst = src;   // copy-assign

    // Check deep copy top
    CHECK(dst.peek() == 3);
    CHECK(src.peek() == 3);

    // Mutate src; dst must be unaffected
    src.pop();        // remove 3
    src.push(77);     // now top 77
    CHECK(src.peek() == 77);
    CHECK(dst.peek() == 3);

    // Drain both to confirm full order
    auto vsrc = drain_to_vec<ListStack<int>, int>(src); // {77,2,1}
    auto vdst = drain_to_vec<ListStack<int>, int>(dst); // {3,2,1}
    CHECK(vsrc == std::vector<int>({77, 2, 1}));
    CHECK(vdst == std::vector<int>({3, 2, 1}));

    // Self-assignment should be a no-op
    ListStack<int> sself;
    sself.push(5);
    sself.push(6);
    sself = sself; // self-assign
    CHECK(sself.peek() == 6);
    auto vself = drain_to_vec<ListStack<int>, int>(sself); // {6,5}
    CHECK(vself == std::vector<int>({6, 5}));
}

// 05) NEXT: Move constructor
// - Source becomes empty; destination takes ownership.
// - Order must be preserved.
TEST_CASE("[05] ListStack — move constructor") 
{
    ListStack<int> src;
    src.push(1);
    src.push(2);
    src.push(3);

    ListStack<int> moved(std::move(src));
    CHECK(src.isEmpty());
    CHECK_FALSE(moved.isEmpty());
    CHECK(moved.peek() == 3);

    auto v = drain_to_vec<ListStack<int>, int>(moved); // {3,2,1}
    CHECK(v == std::vector<int>({3, 2, 1}));
}

// 06) NEXT: Move assignment operator
// - LHS old contents discarded, takes RHS nodes.
// - RHS becomes empty.
// - Self move-assign should be a guarded no-op (by address check).
TEST_CASE("[06] ListStack — move assignment operator") 
{
    ListStack<int> a;
    a.push(10);
    a.push(20);

    ListStack<int> b;
    b.push(1);
    b.push(2);
    b.push(3);

    // Move-assign: a takes b's nodes; b becomes empty
    a = std::move(b);
    CHECK(b.isEmpty());
    CHECK_FALSE(a.isEmpty());
    CHECK(a.peek() == 3);

    // Self move-assign on NON-empty 'a' should be a no-op
    a = std::move(a);
    CHECK_FALSE(a.isEmpty());
    CHECK(a.peek() == 3);

    // Now drain to confirm full order remains intact
    auto va = drain_to_vec<ListStack<int>, int>(a); // {3,2,1}
    CHECK(va == std::vector<int>({3, 2, 1}));

    ListStack<int> c;
    c = std::move(c);        // should not crash
    CHECK(c.isEmpty());      // remains empty
}


// 07) NEXT: Algorithms (reverse, palindrome, curly braces)
// Do these after both stacks are solid. They are independent of stack code.
TEST_CASE("[07] Algorithms — reversedString & isPalindrome & braces") 
{
    // reversedString
    CHECK(reversedString("").empty());
    CHECK(reversedString("a") == "a");
    CHECK(reversedString("ab") == "ba");
    CHECK(reversedString("abc") == "cba");

    // isPalindrome (case-sensitive by design)
    CHECK(isPalindrome(""));
    CHECK(isPalindrome("a"));
    CHECK(isPalindrome("aa"));
    CHECK(isPalindrome("aba"));
    CHECK(isPalindrome("abba"));
    CHECK_FALSE(isPalindrome("ab"));
    CHECK_FALSE(isPalindrome("abaa"));

    // areCurlyBracesMatched
    CHECK(areCurlyBracesMatched(""));
    CHECK(areCurlyBracesMatched("{}"));
    CHECK(areCurlyBracesMatched("a{bc}d"));
    CHECK_FALSE(areCurlyBracesMatched("{"));
    CHECK_FALSE(areCurlyBracesMatched("}"));
    CHECK_FALSE(areCurlyBracesMatched("a{b{c}"));
}

// 08) LAST: infix → postfix (operators, precedence, parentheses)
// Tackle this once everything else is green.
TEST_CASE("[08] Infix→Postfix — core conversions") 
{
    CHECK(infixToPostFix("").empty());

    CHECK(infixToPostFix("a") == "a");
    CHECK(infixToPostFix("a+b") == "ab+");
    CHECK(infixToPostFix("a*b") == "ab*");

    CHECK(infixToPostFix("a+b*c") == "abc*+");
    CHECK(infixToPostFix("a+(b*c)") == "abc*+");
    CHECK(infixToPostFix("(a+(b*c))") == "abc*+");

    CHECK(infixToPostFix("(a+b)*c") == "ab+c*");
    CHECK(infixToPostFix("((a+b)*c)") == "ab+c*");

    CHECK(infixToPostFix("a*b+c") == "ab*c+");
    CHECK(infixToPostFix("(a*b)+c") == "ab*c+");
    CHECK(infixToPostFix("((a*b)+c)") == "ab*c+");
}



