# include <iostream>
# include <cmath>
#include <list>

int main(){

    double number_1;
    double number_2;
    double result = 1;
    double new_number;
    double PI = 3.14159265358979323846;

    std::string operation;
    std::list<int> numbers;
    std::string another_number;

    std::cout << "Welcome to the science calculator\n";
    std::cout << "-----------------------------------\n";
    std::cout << "What operation do you want to do?: \n" << 
    "Write either: + , - , * , / , ^ , sqrt , sin , cos , tan: ";
    std::cin >> operation;

    if (operation == "sqrt" || operation ==  "sin" ||
         operation ==  "cos" || operation ==  "tan"){

        std::cout << "input the first number: ";
        std::cin >> number_1;

        
        if (operation == "sqrt"){
            if (number_1 >=0){
                result = sqrt(number_1);}}
        else if (operation == "sin"){
            result = sin(number_1 * PI / 180);}
        else if (operation == "cos"){
        result = cos(number_1 * PI / 180);
        if (fabs(result) < 1e-10) result = 0; }
        else if (operation == "tan"){
            result = tan(number_1 * PI / 180);}
        
        std::cout << "result: " << result;
    }

    else if (operation == "+" || operation ==  "-" 
        || operation ==  "*" || operation ==  "/"){

        std::cout << "input the first number: ";
        std::cin >> number_1;

        std::cout << "input the secend number: ";
        std::cin >> number_2;

        numbers.push_back(number_1);
        numbers.push_back(number_2);
        
        std::cin.ignore();

        do{
            std::cout << "do you want to enter another number (yes , no)?: ";
            std::getline(std::cin , another_number);

            if(another_number == "yes"){

                std::cout << "write the new number here: ";
                std::cin >>  new_number;

                numbers.push_back(new_number);
                std::cin.ignore();
            }

        }while(another_number == "yes");

        
        if (operation == "+"){
            result = 0;
            for (int i : numbers){
                result += i;}}
        else if (operation == "-"){
            result = 0;
            for (int i : numbers){
                result -= i;}}
        else if (operation == "*"){
            result = 1;
            for (int i : numbers){
                result = result * i;}}
        else if (operation == "/"){
            for (int i : numbers){
                if (i != 0) {
                    if (i == numbers.front()){
                        result = i;}
                    else{result /= i;}}
                else {
                    std::cout << "you can't divide by zero";
                    break;}}}
        
        std::cout << "result: " << result;
    }
        

    else if(operation == "^"){

        std::cout << "Enter the base: ";
        std::cin >> number_1;

        std::cout << "Enter the exponent: ";
        std::cin >> number_2;

        result = pow(number_1, number_2);

        std::cout << "result: " << result;
    }

    else{
        std::cout << "You entered a invalid operator";
    }

    return 0;

}