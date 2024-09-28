#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
std::string loggedInFirstName, loggedInLastName;
class Ingredient {
public:
    std::string name;
    int calories;
    Ingredient(std::string n, int c) : name(n), calories(c) {}
    void display() const {
        std::cout << name << " has " << calories << " calories.\n";
    }
};
class IngredientManager {
private:
    std::vector<Ingredient> ingredients;
public:
    void addIngredient(const std::string& name, int calories) {
        for (const auto& ing : ingredients) {
            if (ing.name == name) {
                std::cout << "Pre-made meal/Ingredient already exists!\n";
                return;
            }
        }
        ingredients.emplace_back(name, calories);
        std::cout << "Pre-made meal/Ingredient added successfully!\n";
    }
    int searchIngredient(const std::string& name) {
        auto it = std::find_if(ingredients.begin(), ingredients.end(),
                               [&name](const Ingredient& ingredient) {
                                   return ingredient.name == name;
                               });
        if (it != ingredients.end()) {
            it->display();
            return it->calories;
        } else {
            std::cout << "Pre-made meal/Ingredient not found!\n";
            return -1;
        }
    }
    void listIngredients() {
        if (ingredients.empty()) {
            std::cout << "No pre-made meals/ingredients added yet.\n";
            return;
        }
        std::cout << "Listing all the pre-made meals/ingredients:\n";
        for (const auto& ingredient : ingredients) {
            ingredient.display();
        }
    }
};
IngredientManager ingredientManager;
void initializeIngredients() {
    ingredientManager.addIngredient("Apple", 95);
    ingredientManager.addIngredient("Banana", 105);
    ingredientManager.addIngredient("Slice of Pizza", 285);
    ingredientManager.addIngredient("Grilled Chicken Breast", 165);
    ingredientManager.addIngredient("Avocado", 240);
    ingredientManager.addIngredient("Brown Rice (1 cup cooked)", 216);
    ingredientManager.addIngredient("Spinach Salad (1 cup)", 7);
    ingredientManager.addIngredient("Almonds (1 oz)", 164);
    ingredientManager.addIngredient("Chocolate Chip Cookie", 200);
    ingredientManager.addIngredient("Egg (large)", 78);
    ingredientManager.addIngredient("Greek Yogurt (1 cup)", 59);
    ingredientManager.addIngredient("Glass of Red Wine", 125);
    ingredientManager.addIngredient("Cheeseburger", 303);
    ingredientManager.addIngredient("French Fries (medium)", 365);
    ingredientManager.addIngredient("Protein Shake", 220);
    ingredientManager.addIngredient("Tofu (1 cup)", 188);
    ingredientManager.addIngredient("Salmon Fillet", 367);
    ingredientManager.addIngredient("Beef Steak (200 grams)", 542);
    ingredientManager.addIngredient("Oatmeal (1 cup cooked)", 158);
    ingredientManager.addIngredient("Whole Wheat Bread (1 slice)", 69);
}
int login_acc()
{
    std::string firstname, lastname;
    std::cout << "Enter your first name: ";
    std::cin >> firstname;
    std::cout << "Enter your last name: ";
    std::cin >> lastname;
    std::ifstream fileIn("accounts.csv");
    std::string line;
    while (getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string existingFirstName, existingLastName;
        int existingCalories;
        getline(ss, existingFirstName, ',');
        getline(ss, existingLastName, ',');
        ss >> existingCalories;
        if (existingFirstName == firstname && existingLastName == lastname) {
            loggedInFirstName = firstname;
            loggedInLastName = lastname;
            std::cout << "Login successful!\n";
            fileIn.close();
            return 1;
        }
    }
    fileIn.close();
    std::cout << "No account found with that first and last name!\n";
    return 0;
}
void create_acc()
{
    std::string firstname, lastname;
    int calorieObjective;
    std::cout << "Enter your first name: ";
    std::cin >> firstname;
    std::cout << "Enter your last name: ";
    std::cin >> lastname;
    std::cout << "Enter your daily calorie objective (it must be between 500 and 5000: ";
    std::cin >> calorieObjective;
    while (calorieObjective < 500 || calorieObjective > 5000) {
        std::cout << "Invalid objective. It must be between 500 and 5000. Please re-enter the calorie objective: ";
        std::cin >> calorieObjective;
    }
    std::ifstream fileIn("accounts.csv");
    std::string line;
    bool exists = false;
    while (getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string existingFirstName, existingLastName;
        int existingCalories;
        getline(ss, existingFirstName, ',');
        getline(ss, existingLastName, ',');
        ss >> existingCalories;
        if (existingFirstName == firstname && existingLastName == lastname) {
            exists = true;
            break;
        }
    }
    fileIn.close();
    if (exists) {
        std::cout << "An account with this name and surname already exists!\n";
        create_acc();
    } else {
        std::ofstream fileOut("accounts.csv", std::ios::app);
        fileOut << firstname << "," << lastname << "," << calorieObjective << std::endl;
        fileOut.close();
        std::cout << "Account created successfully!\n";
    }
}
void delete_acc() {
    std::string firstname, lastname;
    std::cout << "Enter your first name: ";
    std::cin >> firstname;
    std::cout << "Enter your last name: ";
    std::cin >> lastname;
    std::ifstream accountsIn("accounts.csv");
    std::ofstream accountsOut("temp_accounts.csv", std::ios::out);
    std::string line;
    bool accountFound = false;
    while (getline(accountsIn, line)) {
        std::stringstream ss(line);
        std::string existingFirstName, existingLastName;
        int existingCalories;
        getline(ss, existingFirstName, ',');
        getline(ss, existingLastName, ',');
        ss >> existingCalories;
        if (existingFirstName != firstname || existingLastName != lastname) {
            accountsOut << line << std::endl;
        } else {
            accountFound = true;
        }
    }
    accountsIn.close();
    accountsOut.close();
    if (accountFound) {
        std::remove("accounts.csv");
        std::rename("temp_accounts.csv", "accounts.csv");
        std::cout << "Account deleted successfully!\n";
    } else {
        std::remove("temp_accounts.csv");
        std::cout << "No account found with that first and last name!\n";
        return;
    }
    std::ifstream logsIn("logs.csv");
    std::ofstream logsOut("temp_logs.csv", std::ios::out);
    bool logFound = false;
    while (getline(logsIn, line)) {
        std::stringstream ss(line);
        std::string date, logFirstName, logLastName;
        int calories;
        getline(ss, date, ',');
        getline(ss, logFirstName, ',');
        getline(ss, logLastName, ',');
        ss >> calories;
        if (logFirstName != firstname || logLastName != lastname) {
            logsOut << line << std::endl;
        } else {
            logFound = true;
        }
    }
    logsIn.close();
    logsOut.close();
    if (logFound) {
        std::remove("logs.csv");
        std::rename("temp_logs.csv", "logs.csv");
        std::cout << "All the user data also deleted successfully!\n";
    } else {
        std::remove("temp_logs.csv");
        std::cout << "No data found for that user, nothing was changed!\n";
    }
}
void edit_obj() {
    if (loggedInFirstName.empty() || loggedInLastName.empty()) {
        std::cout << "No user is currently logged in.\n";
        return;
    }
    std::ifstream fileIn("accounts.csv");
    std::ofstream fileOut("temp.csv", std::ios::out);
    std::string line;
    bool found = false;
    int currentObjective;
    while (getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string firstname, lastname;
        int calorieObjective;
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        ss >> calorieObjective;
        if (firstname == loggedInFirstName && lastname == loggedInLastName) {
            found = true;
            currentObjective = calorieObjective;
            std::cout << "Current calorie daily objective: " << currentObjective << std::endl;
            int newObjective;
            std::cout << "Enter new calorie objective (between 500 and 5000): ";
            std::cin >> newObjective;
            while (newObjective < 500 || newObjective > 5000) {
                std::cout << "Invalid objective! It must be between 500 and 5000! Please re-enter the new calorie objective: ";
                std::cin >> newObjective;
            }
            fileOut << firstname << "," << lastname << "," << newObjective << std::endl;
        } else {
            fileOut << line << std::endl;
        }
    }
    fileIn.close();
    fileOut.close();
    if (found) {
        std::remove("accounts.csv");
        std::rename("temp.csv", "accounts.csv");
        std::cout << "Objective updated successfully!\n";
    } else {
        std::cout << "No account found for the logged in user.\n";
        std::remove("temp.csv");
    }
}
void add_cal() {
    if (loggedInFirstName.empty() || loggedInLastName.empty()) {
        std::cout << "No user is currently logged in.\n";
        return;
    }
    std::string date;
    std::cout << "Enter the date (using the format DD.MM.YYYY) for calorie logging: ";
    std::cin >> date;
    int choice;
    std::cout << "1. Add calories manually\n2. Choose from a list of ingredients\nEnter your choice: ";
    std::cin >> choice;
    int calories = 0;
    if (choice == 1) {
        std::cout << "Enter the number of calories: ";
        std::cin >> calories;
        while (calories <= 0) {
            std::cout << "Calories must be greater than 0. Please re-enter: ";
            std::cin >> calories;
        }
    } else if (choice == 2) {
        ingredientManager.listIngredients();
        std::cout << "Enter the name of the pre-made meal/ingredient you wish to choose: ";
        std::string ingredientName;
        std::cin.ignore();
        getline(std::cin, ingredientName);
        calories = ingredientManager.searchIngredient(ingredientName);
        if (calories == -1) {
            return;
        }
    } else {
        std::cout << "Invalid choice!\n";
        return;
    }
    std::ifstream fileIn("logs.csv");
    std::ofstream fileOut("temp.csv", std::ios::out);
    std::string line;
    bool found = false;
    while (getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string fileDate, firstname, lastname;
        int existingCalories;
        getline(ss, fileDate, ',');
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        ss >> existingCalories;
        if (fileDate == date && firstname == loggedInFirstName && lastname == loggedInLastName) {
            existingCalories += calories;
            found = true;
        }
        fileOut << fileDate << "," << firstname << "," << lastname << "," << existingCalories << std::endl;
    }
    if (!found) {
        fileOut << date << "," << loggedInFirstName << "," << loggedInLastName << "," << calories << std::endl;
    }
    fileIn.close();
    fileOut.close();
    std::remove("logs.csv");
    std::rename("temp.csv", "logs.csv");
    std::cout << "Calories added successfully!\n";
}
void delete_cal() {
    if (loggedInFirstName.empty() || loggedInLastName.empty()) {
        std::cout << "No user is currently logged in.\n";
        return;
    }
    std::string date;
    std::cout << "Enter the date (using the format DD.MM.YYYY) from which to delete calories: ";
    std::cin >> date;
    int caloriesToDelete;
    std::cout << "Enter the number of calories to delete: ";
    std::cin >> caloriesToDelete;
    if (caloriesToDelete <= 0) {
        std::cout << "Calories must be greater than 0!\n";
        return;
    }
    std::ifstream fileIn("logs.csv");
    std::ofstream fileOut("temp.csv", std::ios::out);
    std::string line;
    bool found = false;
    bool validDeletion = false;
    while (getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string fileDate, firstname, lastname;
        int existingCalories;
        getline(ss, fileDate, ',');
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        ss >> existingCalories;
        if (fileDate == date && firstname == loggedInFirstName && lastname == loggedInLastName) {
            found = true;
            if (caloriesToDelete > existingCalories) {
                std::cout << "Cannot delete more calories than were logged!\n";
                existingCalories = 0;
            } else {
                existingCalories -= caloriesToDelete;
                validDeletion = true;
            }
        }
        if (existingCalories > 0 || (fileDate != date || firstname != loggedInFirstName || lastname != loggedInLastName)) {
            fileOut << fileDate << "," << firstname << "," << lastname << "," << existingCalories << std::endl;
        }
    }
    fileIn.close();
    fileOut.close();
    if (!found) {
        std::cout << "No calories tracked for that date!\n";
        std::remove("temp.csv");
    } else if (validDeletion) {
        std::remove("logs.csv");
        std::rename("temp.csv", "logs.csv");
        std::cout << "Calories deleted successfully!\n";
    } else {
        std::remove("temp.csv");
    }
}
void view_cal() {
    if (loggedInFirstName.empty() || loggedInLastName.empty()) {
        std::cout << "No user is currently logged in.\n";
        return;
    }
    std::string date;
    std::cout << "Enter the date (using the format DD.MM.YYYY) to view calories: ";
    std::cin >> date;
    std::ifstream logsFile("logs.csv");
    std::string line;
    bool found = false;
    int totalCalories = 0;
    while (getline(logsFile, line)) {
        std::stringstream ss(line);
        std::string fileDate, firstname, lastname;
        int calories;
        getline(ss, fileDate, ',');
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        ss >> calories;
        if (fileDate == date && firstname == loggedInFirstName && lastname == loggedInLastName) {
            totalCalories += calories;
            found = true;
        }
    }
    logsFile.close();
    if (!found) {
        std::cout << "No calories tracked for that date!\n";
        return;
    }
    std::ifstream accountsFile("accounts.csv");
    int calorieTarget = 0;
    found = false;
    while (getline(accountsFile, line)) {
        std::stringstream ss(line);
        std::string firstname, lastname;
        int target;
        getline(ss, firstname, ',');
        getline(ss, lastname, ',');
        ss >> target;
        if (firstname == loggedInFirstName && lastname == loggedInLastName) {
            calorieTarget = target;
            found = true;
            break;
        }
    }
    accountsFile.close();
    if (!found) {
        std::cout << "Account details not found. Unable to retrieve calorie target.\n";
        return;
    }
    std::cout << "Calories logged for " << date << ": " << totalCalories << std::endl;
    if (totalCalories > calorieTarget) {
        std::cout << "You are over your calorie target by " << (totalCalories - calorieTarget) << " calories!\n";
    } else if (totalCalories < calorieTarget) {
        std::cout << "You are under your calorie target by " << (calorieTarget - totalCalories) << " calories!\n";
    } else {
        std::cout << "You met your exact calorie target!\n";
    }
}
void logged_in()
{
    int choice;
    std::cout<<"\nOperations Menu\nPlease select the operation you want to proceed with:";
    std::cout << "\n1. Edit objective\n2. Add calories\n3. Delete calories\n4. View calories\n5. Exit\nEnter your choice: ";
    std::cin >> choice;
    switch (choice)
    {
        default:
            std::cout << "Please select a valid option!";
            logged_in();
            return;
        case 1:
            edit_obj();
            logged_in();
            break;
        case 2:
            add_cal();
            logged_in();
            break;
        case 3:
            delete_cal();
            logged_in();
            break;
        case 4:
            view_cal();
            logged_in();
            break;
        case 5:
            std::cout << "Thank you for using our services!";
            return;
    }
}
bool check=true;
int main()
{
    if (check) {
        initializeIngredients();
        check = false;
    }
    int choice;
    std::cout << "\nCountX\n";
    std::cout << "Main Menu:\n";
    std::cout << "1. Create account\n2. Login with an existing account\n3. Delete account\n4. Exit\nEnter your choice: ";
    std::cin >> choice;
    switch (choice)
    {
        case 1:
            create_acc();
            main();
            break;
        case 2:
            if (login_acc())
            {
                logged_in();
            }
            else
                main();
            break;
        case 3:
            delete_acc();
            main();
            break;
        case 4:
            std::cout << "Thank you for using our services!";
            return 0;
        default:
            std::cout << "Please select a valid option!\n";
            main();
            break;
    }
    return 0;
}