# include <iostream>
# include <vector>


class Equation_Items{

    private:
        double Factor;
        char Operation;
        std::string variable;
        
    public:
        void set_everything(double Factor , char Operation , std::string variable){
            this->Factor = Factor;
            this->Operation = Operation;
            this->variable = variable;
        }

        //Seters.
        void set_Factor(double number){
            Factor = number;}
        
        void set_Operation(char Operation){
            this->Operation = Operation;}
           
        void set_Value(std::string variable){
            this->variable = variable;}
        
        //Geters.
        double get_Factor(){
            return Factor;}
        
        char get_Operation(){
            return Operation;}
        
        std::string get_Value(){
            return variable;}

};

std::vector<std::vector<int>> Bracket_index_to_do( std::vector<Equation_Items> Part_of_Equation);

Equation_Items Create_Item(double Factor , char Operation , std::string Value);

bool Is_Math_Opreition(std::string Opreition);

void Replace(int first_index , int last_index , Equation_Items new_value , std::vector<Equation_Items>& list);;

double Calculate(double first_number , double second_number , char Opreition);

void Bracket_Simplifier(int Start_Bracket_index , int Close_Bracket_index , std::vector<Equation_Items>& Part_of_Equation);

void Bracket_Expansion(int Start_Bracket_index , int Close_Bracket_index , std::vector<Equation_Items>& Part_of_Equation , Equation_Items Result_with_x , Equation_Items Result_without_x);

int main(){
    std::string Full_Equation_letters;
    std::vector<Equation_Items> First_Part_Equation;
    std::vector<Equation_Items> secont_Part_Equation;
    std::vector<Equation_Items> Current_part_Equation;


    std::cout << "Write a equation you want to be solved: ";
    std::getline(std::cin  , Full_Equation_letters);

    (Full_Equation_letters.find("=") > Full_Equation_letters.size()) ? std::cout << "You did NOT enter a valid equation!" : std::cout << "";
    // change that if there is 4 - 4x it will be 4 + -4x
    std::string number;
    Full_Equation_letters += " ";

    for (int i = 0; i < Full_Equation_letters.size(); i++){
        // Create new class item.
        Equation_Items new_item;
        char currnt = Full_Equation_letters[i];
        if (std::isdigit(currnt) || currnt == '.' || currnt == '-'){
            number += currnt;}

        else if (!(number.empty())) {
            // it is a variable (x or y).
            if (std::isalpha(currnt)){
                new_item.set_everything(std::stod(number) , '0' , std::string(1 , currnt));
                Current_part_Equation.push_back(new_item);
                number.clear();
                continue;
            }
            // it is a number.
            else if (number != "-") {
                new_item.set_everything(std::stod(number) , '0' , "0");
                Current_part_Equation.push_back(new_item);
            }
            // it is a subtraction sign (-).
            else {
                new_item.set_everything(0 , '-' , "0");
                Current_part_Equation.push_back(new_item);
            }
            number.clear();
            
        }

        if (currnt == '*' || currnt == '+' || currnt == '/' || currnt == '(' || currnt == ')'){
            new_item.set_everything(0 , currnt , "0");
            Current_part_Equation.push_back(new_item);
        }

        else if (std::isalpha(currnt)){
            new_item.set_everything(1 , '0' , std::string(1 , currnt));
            Current_part_Equation.push_back(new_item);
        }
        
        else if (currnt == '='){
            // swich Between the first part equation and the second equation.
            First_Part_Equation = Current_part_Equation;
            Current_part_Equation.clear();}
    }

    secont_Part_Equation = Current_part_Equation;
    Current_part_Equation.clear();

    std::vector<int> First_Part_Equation_open_Bracket_list = Bracket_index_to_do(First_Part_Equation)[0];
    std::vector<int> Second_Part_Equation_open_Bracket_list = Bracket_index_to_do(secont_Part_Equation)[0];
    

    for (int i = 0; i < First_Part_Equation_open_Bracket_list.size(); i++){
        int open_paren_index_to_do = Bracket_index_to_do(First_Part_Equation)[0][0];
        int close_paren_index_to_do = Bracket_index_to_do(First_Part_Equation)[1][0]; 
        Bracket_Simplifier(open_paren_index_to_do , close_paren_index_to_do , First_Part_Equation);  
    }

    for (int i = 0; i < Second_Part_Equation_open_Bracket_list.size(); i++){
        int open_paren_index_to_do = Bracket_index_to_do(secont_Part_Equation)[0][0];
        int close_paren_index_to_do = Bracket_index_to_do(secont_Part_Equation)[1][0]; 
        Bracket_Simplifier(open_paren_index_to_do , close_paren_index_to_do , secont_Part_Equation);  
    }
    
    double New_var_factor;
    double New_number;

    if (First_Part_Equation[1].get_Operation() == '-'){
        New_number = First_Part_Equation[2].get_Factor() + secont_Part_Equation[2].get_Factor();
    }

    else if (First_Part_Equation[1].get_Operation() == '+'){
        New_number = First_Part_Equation[2].get_Factor() - secont_Part_Equation[2].get_Factor();
    }

    New_var_factor = secont_Part_Equation[0].get_Factor() - First_Part_Equation[0].get_Factor();

    double result_for_var = New_number / New_var_factor;

    std::cout << secont_Part_Equation[0].get_Value() << " = " << result_for_var;

    // for (int i = 0; i < First_Part_Equation.size(); i++){
    //     std::cout << First_Part_Equation[i].get_Factor() << '\t' <<  First_Part_Equation[i].get_Operation() << '\t' <<   First_Part_Equation[i].get_Value() << '\n';
    // }
    // 
    // std::cout << "---------------------------------\n";
    // std::cout << "---------------------------------\n";
    // 
    // for (int i = 0; i < secont_Part_Equation.size(); i++){
    //     std::cout << secont_Part_Equation[i].get_Factor() << '\t' <<  secont_Part_Equation[i].get_Operation() << '\t' <<   secont_Part_Equation[i].get_Value() << '\n';
    // }

    return 0;
}

std::vector<std::vector<int>> Bracket_index_to_do( std::vector<Equation_Items> Part_of_Equation){
    std::vector<int> list_of_open_paren;
    std::vector<int> list_of_close_paren;
    int insert_index = 0;

    
    for (int i = 0; i < Part_of_Equation.size(); i++){
        //std::cout << Part_of_Equation[i].get_Operation() << '\t';
        if (Part_of_Equation[i].get_Operation() == '('){
            list_of_open_paren.insert(list_of_open_paren.begin() + insert_index, i);
        }

        else if (Part_of_Equation[i].get_Operation() == ')'){
            list_of_close_paren.insert(list_of_close_paren.begin() + insert_index, i);
            insert_index++;
        }
    }
    list_of_open_paren.push_back(0);
    list_of_close_paren.push_back(Part_of_Equation.size() - 1);
    return {list_of_open_paren , list_of_close_paren};
}

void Bracket_Expansion(int Start_Bracket_index , int Close_Bracket_index , std::vector<Equation_Items>& Part_of_Equation , Equation_Items Result_with_x , Equation_Items Result_without_x){

    // chack if we Multipliy or divide quantity of the braket.
    Equation_Items Operation = Part_of_Equation[Start_Bracket_index + 2];

    Result_with_x.set_Factor(Calculate(Part_of_Equation[Start_Bracket_index - 2].get_Factor() , Result_with_x.get_Factor() , Part_of_Equation[Start_Bracket_index - 1].get_Operation()));
    Result_without_x.set_Factor(Calculate(Part_of_Equation[Start_Bracket_index - 2].get_Factor() , Result_without_x.get_Factor() , Part_of_Equation[Start_Bracket_index - 1].get_Operation()));
    

    Part_of_Equation.erase(
        Part_of_Equation.begin() + Start_Bracket_index - 2,
        Part_of_Equation.begin() + Close_Bracket_index + 1
    );

    int insert_pos = Start_Bracket_index - 2;
    bool has_with_x = Result_with_x.get_Factor() != 0;
    bool has_without_x = Result_without_x.get_Factor() != 0;
    
    if (has_without_x){
        Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Result_without_x);
    }
    if (has_with_x && has_without_x){
        Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Create_Item(0 , '+' , "0"));
    }
    if (has_with_x){
        Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Result_with_x);
    }
    

    
    
}

void Bracket_Simplifier(int Start_Bracket_index , int Close_Bracket_index , std::vector<Equation_Items>& Part_of_Equation){

    // Multiplication and division.
    for (int i = Start_Bracket_index; i < Close_Bracket_index; i++){
        
        Equation_Items Current = Part_of_Equation[i]; 
        if (Current.get_Operation() == '/' || Current.get_Operation() == '*'){
            
            double result = Calculate(Part_of_Equation[i - 1].get_Factor() , Part_of_Equation[i + 1].get_Factor() , Current.get_Operation());
            // chack if at lest one has a variable.
            if (std::isalpha(Part_of_Equation[i - 1].get_Value()[0]) || std::isalpha(Part_of_Equation[i + 1].get_Value()[0])){    
                Replace(i - 1 , i + 1 , Create_Item(result , '0' , "x") , Part_of_Equation);
            }
            else {
                Replace(i - 1 , i + 1 , Create_Item(result , '0' , "0") , Part_of_Equation);}
            
            i--;
            Close_Bracket_index -= 2;
        }
    }
    

    // Addition and subtraction.

    // Create new items
    Equation_Items Result_with_x = Create_Item(0 , '0' , "x");
    Equation_Items Result_without_x = Create_Item(0 , '0' , "0");

    //we take care of the first number in the braket because the agroritem does not take care of the first number.
    if (std::isalpha(Part_of_Equation[Start_Bracket_index + 1].get_Value()[0]) || std::isalpha(Part_of_Equation[Start_Bracket_index].get_Value()[0])){
        if (Part_of_Equation[Start_Bracket_index + 1].get_Operation() != '0'){
            Result_with_x.set_Factor(Part_of_Equation[Start_Bracket_index].get_Factor());
            Result_with_x.set_Value(Part_of_Equation[Start_Bracket_index].get_Value());
        }
        else {
            Result_with_x.set_Factor(Part_of_Equation[Start_Bracket_index + 1].get_Factor());
            Result_with_x.set_Value(Part_of_Equation[Start_Bracket_index + 1].get_Value());
        }
    }

    else {
        if (Part_of_Equation[Start_Bracket_index + 1].get_Operation() != '0'){
            Result_without_x.set_Factor(Part_of_Equation[Start_Bracket_index].get_Factor());}
        
        else {
            Result_without_x.set_Factor(Part_of_Equation[Start_Bracket_index + 1].get_Factor());}
    }
    
    // start to loop over the elements in the equation.
    for (int i = Start_Bracket_index; i < Close_Bracket_index; i++){

        Equation_Items Current = Part_of_Equation[i];

        if (Current.get_Operation() == '+' || Current.get_Operation() == '-'){
            if (std::isalpha(Part_of_Equation[i + 1].get_Value()[0])){
                    Result_with_x.set_Factor(Calculate(Result_with_x.get_Factor() , Part_of_Equation[i + 1].get_Factor() , Current.get_Operation()));
            }
            
            else {
                Result_without_x.set_Factor(Calculate(Result_without_x.get_Factor() , Part_of_Equation[i + 1].get_Factor() , Current.get_Operation()));
            }
                
        }
    }

    if (Part_of_Equation[Start_Bracket_index - 1].get_Operation() == '*' ||  Part_of_Equation[Start_Bracket_index - 1].get_Operation() == '/'){
        Bracket_Expansion(Start_Bracket_index , Close_Bracket_index , Part_of_Equation , Result_with_x , Result_without_x);
    }
    
    else {
        Part_of_Equation.erase(
            Part_of_Equation.begin() + Start_Bracket_index,
            Part_of_Equation.begin() + Close_Bracket_index + 1
        );

        Equation_Items Operation;
        // chack if we are inside a bracket or is not.
        
        Operation = (Part_of_Equation[Start_Bracket_index].get_Operation() == '(') ? Operation = 
        Part_of_Equation[Start_Bracket_index + 2] : Operation =  Part_of_Equation[Start_Bracket_index + 1];

        int insert_pos = Start_Bracket_index;
        bool has_with_x = Result_with_x.get_Factor() != 0;
        bool has_without_x = Result_without_x.get_Factor() != 0;

        if (has_without_x){
            Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Result_without_x);
        }
        if (has_with_x && has_without_x){
            Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Operation);
        }
        if (has_with_x){
            Part_of_Equation.insert(Part_of_Equation.begin() + insert_pos, Result_with_x);
        }
    }
    
}

void Replace(int first_index , int last_index , Equation_Items new_value , std::vector<Equation_Items>& list){
    list.erase(
    list.begin() + first_index,
    list.begin() + last_index + 1);
    list.insert(list.begin() + first_index , new_value);    
}

double Calculate(double first_number , double second_number , char Opreition){

    switch (Opreition){

        case '*':
            return first_number * second_number;
        
        case '/':
            return first_number / second_number;

        case '+':
            return first_number + second_number;
        
        case '-':
            return first_number - second_number;
        
        default:
            std::cout << "there is NOT math Opreition as: " << Opreition;
            throw std::invalid_argument("Invalid math operation");
            
    }
}

Equation_Items Create_Item(double Factor , char Operation , std::string Value){
    Equation_Items New_item;
    New_item.set_everything(Factor , Operation , Value);
    return New_item;
}