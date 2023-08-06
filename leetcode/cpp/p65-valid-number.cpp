// LeetCode 65. Valid Number.

#include <array>
#include <iostream>
#include <optional>

class Solution {
    enum State {
        Start,
        LeadingSign,
        LeadingDot,
        IntOrDecimal,
        Decimal,
        ExponentStart,
        ExponentSign,
        ExponentNum,
        Bad,
        N,
    };

    enum class Type {
        Sign,
        Digit,
        Dot,
        E,
    };

    std::array<std::array<State, 4>, State::N> transitionMatrix = {
        //                          Sign          Digit         Dot             E
        //                        --------      ---------    --------        --------
        /* Start */           LeadingSign,  IntOrDecimal, LeadingDot,            Bad,
        /* LeadingSign */             Bad,  IntOrDecimal, LeadingDot,            Bad,
        /* LeadingDot */              Bad,       Decimal,        Bad,            Bad,
        /* IntOrDecimal */            Bad,  IntOrDecimal,    Decimal,  ExponentStart,
        /* Decimal */                 Bad,       Decimal,        Bad,  ExponentStart,
        /* ExponentStart */  ExponentSign,   ExponentNum,        Bad,            Bad,
        /* ExponentSign */            Bad,   ExponentNum,        Bad,            Bad,
        /* ExponentNum */             Bad,   ExponentNum,        Bad,            Bad,
        /* Bad */                     Bad,           Bad,        Bad,            Bad,
    };

    std::optional<Type> cToType(char c) {
        if (c >= '0' and c <= '9') {
            return Type::Digit;
        }
        if (c == '.') {
            return Type::Dot;
        }
        if (c == '+' || c == '-') {
            return Type::Sign;
        }
        if (c == 'e' || c == 'E') {
            return Type::E;
        }
        return {};
    }

public:
    bool isNumber(std::string s) {
        State state = State::Start;
        for (const auto c : s) {
            const auto type = cToType(c);
            if (!type) {
                return false;
            }
            state = transitionMatrix[state][static_cast<size_t>(*type)];
            if (state == State::Bad) {
                return false;
            }
        }

        switch (state) {
        case State::Start:
        case State::LeadingSign:
        case State::LeadingDot:
        case State::ExponentStart:
        case State::ExponentSign:
        case State::Bad:
        case State::N:
            return false;

        case State::Decimal:
        case State::IntOrDecimal:
        case State::ExponentNum:
            break;
        }
        return true;
    }
};

int main()
{
    struct TestCase {
        std::string s;
        bool exp;
    };

    const TestCase test_cases[] = {
        {"2", true},
        {"0089", true},
        {"-0.1", true},
        {"+3.14", true},
        {"4.", true},
        {"-.9", true},
        {"2e10", true},
        {"-90E3", true},
        {"3e+7", true},
        {"+6e-1", true},
        {"-123.456e789", true},

        {"", false},
        {"abc", false},
        {"1a", false},
        {"1e", false},
        {"e3", false},
        {"99e2.5", false},
        {"--6", false},
        {"-+3", false},
        {"95a54e53", false},
    };

    Solution solution;
    for (const auto& tc : test_cases) {
        const auto act = solution.isNumber(tc.s);
        if (tc.exp != act) {
            std::cerr << "fail, s: " << tc.s
            << ", exp: " << tc.exp
            << ", act: " << act
            << "\n";
        }
    }
}