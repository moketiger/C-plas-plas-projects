# include <iostream>
#include <list>
#include <random> 
#include <algorithm>

char random_pick(const std::list<char>& list){

    std::mt19937 gen(std::random_device{}());
    auto it = list.begin();
    std::advance(it, std::uniform_int_distribution<>(0, list.size() - 1)(gen));
    return *it;

}   

int main(){
    const std::list<char> numbers_list = {'1' , '2', '3', '4', '5', '6', '7', '8', '9'};
    const std::list<char> letters_list = {'Q','W','E','R', 'T' , 'Y' , 'U' , 'I' , 'O' , 'P','A','S', 'D' , 'F' , 'G' , 'H' , 'J','K', 'L' , 'Z','X','V','C', 'B'  , 'N','M'};
    const std::list<char> special_characters_list = {'!','@' ,'#' , '$' , '%' , '&' , '?'};

    int numbers_amount;
    int letters_amount;
    int special_characters_amount;

    std::string password;

    std::cout << "write how many numbers do you want in the password: ";
    std::cin >> numbers_amount;

    std::cout << "write how many letters do you want in the password: ";
    std::cin >> letters_amount;

    std::cout << "write how many special characters do you want in the password: ";
    std::cin >> special_characters_amount;

    password.clear();

    if (numbers_amount > 0){
        for (int i = 0; i < numbers_amount; i++){
            password.push_back(random_pick(numbers_list));
        }
    }

    if (letters_amount > 0){
        for (int z = 0; z < letters_amount; z++){
            password.push_back(random_pick(letters_list));
        }
    }

    if (special_characters_amount > 0){
        for (int e = 0; e < special_characters_amount; e++){
            password.push_back(random_pick(special_characters_list));
        }
    }


    std::shuffle(password.begin(), password.end(), std::mt19937{std::random_device{}()});
    std::cout << password << "\n"; 

    return 0;

}