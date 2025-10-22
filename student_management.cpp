# include <iostream>
# include "json.hpp"
# include <fstream>
# include <vector>

class students{
    private:
        int score = -1;
        int age;

    public:
        std::string first_name;
        std::string last_name;

        void set_average_score(double new_score)
        {
            if (new_score <= 100 && new_score >= 0){
                score = new_score;}

            else if (new_score > 100){
                score = 100;}
            
        }

        double get_score() const {
            return score;}

        void set_age(int new_age)
        {
            if (new_age <= 100 && new_age >= 18){
                age = new_age;}

            else{
                std::cout << "this person is not in the right age for school\n";}
        }

        int get_age() const {
            return age;}
};

std::vector<students> load_students(const std::string& file_path);
void save_students(const std::vector<students>& students_list, const std::string& file_path);

int main(){

    std::string file_path = "Students.json";
    std::string operation;
    std::vector<students> students_list;
    std::string run_progrem_again = "yes";

    while (run_progrem_again == "yes"){

        students_list = load_students(file_path);

        std::cout <<  "Do you want to add a new student, \nchange a student information \nor look at students information? \nwrite your answer here (add,change,look): ";
        std::cin >> operation;
        std::cin.ignore();

        if (operation == "add")
        {
            students new_student;
            int age;
            
            std::cout << "write the student first name: ";
            std::getline(std::cin , new_student.first_name);

            std::cout << "write the last name: ";
            std::getline(std::cin , new_student.last_name);

            std::cout << "write the age of the student: ";
            std::cin >> age;
            new_student.set_age(age);

            students_list.push_back(new_student);
        }

        else if (operation == "change")
        {
            std::string student_name_change_information;
            std::string type_of_information_change;

            std::cout << "who's information do you want to change? (write first name): ";
            std::getline(std::cin ,student_name_change_information);

            for (int i = 0; i < students_list.size(); i++)
            {
                if (students_list[i].first_name == student_name_change_information)
                {
                    std::cout << "what information do you want to change(first name or last name or score or age)?: "; 
                    std::getline(std::cin , type_of_information_change);

                    if (type_of_information_change == "score")
                    {
                        int new_score;
                        std::cout << "write the new score: ";
                        std::cin >> new_score;
                        students_list[i].set_average_score(new_score);
                    }

                    else if (type_of_information_change == "age")
                    {
                        int new_age;
                        std::cout << "write the new age: ";
                        std::cin >> new_age;
                        students_list[i].set_age(new_age);
                    }

                    else if (type_of_information_change == "first name")
                    {
                        std::string new_first_name;
                        std::cout << "write the new first name: "; 
                        std::getline(std::cin , new_first_name);
                        students_list[i].first_name = new_first_name;
                    }

                    else if (type_of_information_change == "last name")
                    {
                        std::string new_last_name;
                        std::cout << "write the new last name: "; 
                        std::getline(std::cin , new_last_name);
                        students_list[i].last_name = new_last_name;
                    }
                }
            }
        }

        else if (operation == "look")
        {
            for (int i = 0; i < students_list.size(); i++)
            {
                std::cout << "first name is: " << students_list[i].first_name << '\n';

                std::cout << "last name is: " << students_list[i].last_name << '\n';

                std::cout << students_list[i].first_name << " age is " << students_list[i].get_age() << '\n';

                if (students_list[i].get_score() >= 0){
                std::cout << students_list[i].first_name << " average score is " << students_list[i].get_score() << '\n';
                std::cout << "\n";
                }
                else{
                    std::cout << students_list[i].first_name<< " did not take any tests\n";
                }
                
            }
            return 0;
        }   

        else
        {
            std::cout << " Invalid Input";
        }

        save_students(students_list , file_path);

        std::cin.ignore();
        std::cout << "do you want to use the progroem anther time\nwrite yes or no: ";
        std::getline(std::cin , run_progrem_again);
    }
    return 0;
}

void save_students(const std::vector<students>& students_list, const std::string& file_path) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& s : students_list) {
        j.push_back({
            {"first_name", s.first_name},
            {"last_name", s.last_name},
            {"score", s.get_score()},
            {"age", s.get_age()}
        });
    }
    std::ofstream file(file_path);
    file << j.dump(4);
}

std::vector<students> load_students(const std::string& file_path) {
    std::vector<students> students_list;
    std::ifstream file(file_path);
    nlohmann::json j;
    // Only read if not empty
    if (file && file.peek() != std::ifstream::traits_type::eof()) { 
        file >> j;
        for (const auto& item : j) {
            students s;
            s.first_name = item.value("first_name", "");
            s.last_name = item.value("last_name", "");
            s.set_average_score(item.value("score", -1));
            s.set_age(item.value("age", 18));
            students_list.push_back(s);
        }
    }
    return students_list;
}