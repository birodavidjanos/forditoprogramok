#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

int evaluateExpression(const string& input);

int main() {
    string input;
    cout << "Adj meg egy aritmetikai kifejezést: ";
    cin >> input;
    int result = evaluateExpression(input);
    cout << "Az eredmény: " << result << endl;
    return 0;
}

int evaluateExpression(const string& input) {
    stack<int> values; // Számok tárolására
    stack<char> ops;   // Operátorok tárolására

    for (size_t i = 0; i < input.length(); i++) {
        if (isdigit(input[i])) {
            // Számot találunk, addig olvassuk, amíg a szám véget nem ér
            int value = 0;
            while (i < input.length() && isdigit(input[i])) {
                value = value * 10 + (input[i] - '0');
                i++;
            }
            values.push(value);
            i--; // Lépjünk vissza, mert a ciklus tovább lép
        } else if (input[i] == '(') {
            ops.push(input[i]); // Zárójelet helyezzük az operátor verembe
        } else if (input[i] == ')') {
            // Zárójelek között számítást végez
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                if (op == '+') values.push(val1 + val2);
                else if (op == '-') values.push(val1 - val2);
                else if (op == '*') values.push(val1 * val2);
                else if (op == '/') values.push(val1 / val2);
            }
            ops.pop(); // Nyitó zárójelet eltávolítjuk
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            // Operátorok rendezése precedencia szerint
            while (!ops.empty() && ops.top() != '(' && 
                   ((input[i] == '+' || input[i] == '-') || 
                    (input[i] == '*' || input[i] == '/'))) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                if (op == '+') values.push(val1 + val2);
                else if (op == '-') values.push(val1 - val2);
                else if (op == '*') values.push(val1 * val2);
                else if (op == '/') values.push(val1 / val2);
            }
            ops.push(input[i]); // Az aktuális operátort a verembe tesszük
        }
    }

    // Maradék műveletek végrehajtása
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();

        if (op == '+') values.push(val1 + val2);
        else if (op == '-') values.push(val1 - val2);
        else if (op == '*') values.push(val1 * val2);
        else if (op == '/') values.push(val1 / val2);
    }

    return values.top(); // Az utolsó eredmény
}