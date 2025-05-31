# include <iostream>
# include <ctime>

char random_pick(char list[] , int size){
    int random_num = rand() % size;
    return list[random_num];
}   

int main(){
    char numbers_list[] = {'1' , '2', '3', '4', '5', '6', '7', '8', '9'};
    char letters_list[] = {'Q','W','E','R', 'T' , 'Y' , 'U' , 'I' , 'O' , 'P','A','S', 'D' , 'F' , 'G' , 'H' , 'J','K', 'L' , 'Z','X','V','C', 'B'  , 'N','M'};
    char special_characters_list[] = {'!','@' ,'#' , '$' , '%' , '&' , '?'};

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
            password.push_back(random_pick(numbers_list , sizeof(numbers_list)));
        }
    }

    if (letters_amount > 0){
        for (int i = 0; i < letters_amount; i++){
            password.push_back(random_pick(letters_list , sizeof(letters_list)));
        }
    }

    if (special_characters_amount > 0){
        for (int i = 0; i < special_characters_amount; i++){
            password.push_back(random_pick(special_characters_list , sizeof(special_characters_list)));
        }
    }

    for (int j = 0; j < password.size(); j++){
        int random_num = rand() % password.size();
        std::swap(password[j], password[random_num]);
    }

    std::cout << password << "\n"; 

    return 0;

}
