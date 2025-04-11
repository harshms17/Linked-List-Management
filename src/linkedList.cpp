#include <iostream>
#include <exception>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <thread>
#include <conio.h>
#include <windows.h>
#include "LinkedList.h" // Custom class for linked list operations: supports insertion, deletion, traversal, and reversal of elements.

void clearScreen() {
    system("cls");
}
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void typeEffect(std::string text, int delay = 50) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}
void loadingAnimation(std::string action) {
    setConsoleColor(14); // Yellow
    std::cout << action;
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "." << std::flush;
    }
    std::cout<<" Request Accepted!" << std::endl;
    setConsoleColor(7); // Reset to default
}
template<typename T>
void displayMenu(linkedList<T>& list) {
    clearScreen();
    setConsoleColor(14); // Yellow
    std::cout << "\n===== Linked List Menu =====\n";
    setConsoleColor(11); // Light Blue
    std::cout << "1. Insert at Head\n";
    std::cout << "2. Insert at End\n";
    std::cout << "3. Insert at Position\n";
    std::cout << "4. Delete at Position\n";
    std::cout << "5. Delete by Element\n";
    std::cout << "6. Reverse List\n";
    std::cout << "7. Print List\n";
    std::cout << "8. Exit\n";
    setConsoleColor(14); // Yellow
    std::cout << "============================\n";
    list.print(); // Print the current state of the list
    std::cout << "============================\n";
    setConsoleColor(10); // Green
    std::cout << "Enter your choice: ";
    setConsoleColor(7); // Reset to default
}
int getValidInt(){
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        setConsoleColor(12); // Red
        std::cout << "Invalid input. ";
        setConsoleColor(11); // Light Blue
        std::cout << "Please enter a valid number: ";
        setConsoleColor(7); // Reset to default
    }
    return value;
}
std::string getValidString(){
    std::string value;
    std::cin >> value;
    return value;
}
template<typename T>
void linkedListProgram(linkedList<T>& list,T (*getValue)()){
    int choice, position;
    T value;
    do {
        displayMenu(list);
        choice = getValidInt();
        switch (choice) {
            // Insert at Head
            case 1:
                setConsoleColor(10); // Green
                std::cout << "Enter value to insert at head: ";
                setConsoleColor(7); // Reset to default
                value = getValue();
                loadingAnimation("Inserting at head");
                list.insertAtHead(value);
                break;
            // Insert at End
            case 2:
                setConsoleColor(10); // Green
                std::cout << "Enter value to insert at end: ";
                value = getValue();
                setConsoleColor(7); // Reset to default
                loadingAnimation("Inserting at end");
                list.insertAtEnd(value);
                break;
            // Insert at Position
            case 3:
                setConsoleColor(10); // Green
                std::cout << "Enter value: ";
                setConsoleColor(7); // Reset to default
                value = getValue();
                setConsoleColor(10); // Green
                std::cout << "Enter position to insert: ";
                setConsoleColor(7); // Reset to default
                position = getValidInt();
                loadingAnimation("Inserting at position");
                list.insertAtPosition(value, position);
                break;
            // Delete at Position
            case 4:
                setConsoleColor(10); // Green
                std::cout << "Enter position to delete: ";
                setConsoleColor(7); // Reset to default
                position = getValidInt();
                loadingAnimation("Deleting at position");
                list.deleteAtPosition(position);
                break;
            // Delete by Element
            case 5:
                setConsoleColor(10); // Green
                std::cout << "Enter element to delete: ";
                setConsoleColor(7); // Reset to default
                value = getValue();
                loadingAnimation("Deleting element");
                list.deleteByElement(value);
                break;
            // Reverse List
            case 6:
                loadingAnimation("Reversing list");
                list.reverse();
                break;
            // Print List
            case 7:
                loadingAnimation("Printing list");
                list.print();
                break;
            // Exit
            case 8:
                setConsoleColor(14); // Yellow
                typeEffect("Exiting program... Goodbye!");
                setConsoleColor(7); // Reset to default
                break;
            // Invalid choice
            default:
                setConsoleColor(12); // Red
                std::cout << "Invalid choice, please select between 1 and 8.";
                setConsoleColor(7); // Reset to default
        }
        std::cout << "\nPress any key to continue...";
        _getch(); // Wait for user input before clearing the screen
    } while (choice != 8);
}
int main() {
    setConsoleColor(10); // Green
    std::cout << "Choose data type for linked list: \n1. Integer\n2. String\nEnter choice: ";
    setConsoleColor(7); // Reset to default
    int typeChoice;

    do{
        typeChoice = getValidInt();
        if (typeChoice != 1 && typeChoice != 2) {
            setConsoleColor(12); // Red
            std::cout << "Invalid choice. ";
            setConsoleColor(11); // Light Blue
            std::cout << "Please enter 1 or 2.\n";
            setConsoleColor(7); // Reset to default
        }
    } while (typeChoice != 1 && typeChoice != 2);
    
    if (typeChoice == 1) {
        linkedList<int> intList;
        linkedListProgram(intList, getValidInt);
    } else if (typeChoice == 2) {
        linkedList<std::string> strList;
        linkedListProgram(strList, getValidString);
    }
    
    return 0;
}