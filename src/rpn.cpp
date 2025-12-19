#include <iostream>   // чтобы выводить и читать данные
#include <vector>     // чтобы хранить числа
#include <sstream>    // чтобы разбивать строку на слова
using namespace std;

int main() {
    string line; // сюда будем читать одну строку из файла

    // Читаем каждую строку по очереди
    while (getline(cin, line)) {
        if (line.empty()) continue; // если строка пустая, пропускаем её

        vector<long long> stack; // это наша "коробка" для чисел
        bool error = false;      // если что-то пошло не так, поставим true

        istringstream iss(line); // разбиваем строку на части (по пробелам)
        string token;            // сюда будем класть каждое слово (число или знак)

        // Проходим по всем словам в строке
        while (iss >> token) {

            // Если это оператор + - * /
            if (token == "+" || token == "-" || token == "*" || token == "/") {

                // Нужно хотя бы два числа в коробке, чтобы посчитать
                if (stack.size() < 2) {
                    error = true; // мало чисел → ошибка
                    break;        // выходим из цикла
                }

                long long b = stack.back(); stack.pop_back(); // достаем последнее число
                long long a = stack.back(); stack.pop_back(); // достаем предпоследнее число

                // Делаем нужную операцию и кладём результат обратно в коробку
                if (token == "+") stack.push_back(a + b);
                else if (token == "-") stack.push_back(a - b);
                else if (token == "*") stack.push_back(a * b);
                else { 
                    if (b == 0) { error = true; break; } // деление на 0 → ошибка
                    stack.push_back(a / b);
                }

            } else {
                // Если это число, пробуем положить в коробку
                try { stack.push_back(stoll(token)); } // преобразуем строку в число
                catch(...) { error = true; break; }    // если не число → ошибка
            }
        }

        // В конце в коробке должен остаться ровно один результат
        if (stack.size() != 1) error = true;

        // Выводим строку и результат
        cout << line << " = ";
        if (!error) cout << stack.back();
        else cout << "ERROR"; // если произошла ошибка
        cout << "\n";
    }
}

