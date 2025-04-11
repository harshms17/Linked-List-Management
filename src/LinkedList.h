#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Errors.h" // Custom error class for file operations
#include "Node.h"   // Custom class for Node Structure
#include "LinkedListUtils.h"  // Custom class for custom operations

template<typename T>
class linkedList{ // Linked list Class
    Node<T>* head; // List always have one head node
    std::ofstream logFile; // Log file

    void log(std::string message){
        // std::chrono::time_point<std::chrono::system_clock> rawTime = std::chrono::system_clock::now();
        time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // converting raw Time to time structure
        tm* time = localtime(&now); // local readable time pointer
        logFile << time->tm_mday << "-" << time->tm_mon + 1 << "-" << time->tm_year+1900 << "\t" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << "\t|\t"
            << message // adding to logfile
            << std::endl;
    }

    public:
    linkedList(): head(NULL), logFile("../log/log.txt",std::ios::app){ // Empty List Constructor
        try
        {
            // if(!logFile.is_open()) throw Errors::file_error("File not opened.\033[0m\n"); //color
            if(!logFile.is_open()) throw Errors::file_error("File not opened.\n");
            log("Linked List Created");
        }
        catch(const Errors::file_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void insertAtHead(T data){ // Insert at head of list
        Node<T>* newNode = new Node<T>(data); // Empty Node creation
        newNode->next = head;
        head = newNode; // new head
        log(convertToString(data) +" Inserted at Head");
    }

    void insertAtEnd(T data){ // Insert at end of list
        Node<T>* newNode = new Node<T>(data); // new Node<T> creation
        if(head == NULL){ // If list is empty
            head = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != NULL){ // getting tail node of list
            temp = temp->next;
        }
        temp->next = newNode;
        log(convertToString(data) +" Inserted at the End");
    }

    void insertAtPosition(T data, int position){ // Insert at position
        try
        {
            if (position < 1) {
                // throw Errors::invalid_input("Position must be greater than 0\033[0m\n"); //color
                throw Errors::invalid_input("Position must be greater than 0\n");
            }
            if(position == 1){ // If position is 1, insert at head
                insertAtHead(data);
                return;
            }
            Node<T>* temp = head;
            int cnt = 2;
            while(cnt < position){
                if(temp->next == NULL) { // position out of range
                    // throw Errors::invalid_input("Position out of range\033[0m\n"); //color
                    throw Errors::invalid_input("Position out of range\n");
                }
                temp = temp->next;
                cnt++;
            }
            Node<T>* newNode = new Node<T>(data); // new Node<T> creation
            newNode->next = temp->next;
            temp->next = newNode;
            log(convertToString(data) +" Inserted at position " + convertToString(position));
        }
        catch(const Errors::invalid_input& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void deleteAtPosition(int position){ // Delete at head of list
        try
        {
            if(head == NULL){ // empty List Case
                // throw Errors::invalid_request("List is already empty. Cannot delete\033[0m\n"); //color
                throw Errors::invalid_request("List is already empty. Cannot delete\n");
            }
            if(position == 1){ // head node case
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                temp = NULL;
            }else{
                Node<T>* prev = head;
                int cnt = 2;
                while(cnt < position && prev->next != NULL){ // traversal to target node
                    prev = prev->next;
                    cnt++;
                }
                if(prev->next == NULL) { // position out of range
                    // throw Errors::invalid_input("Position out of range\033[0m\n"); //color
                    throw Errors::invalid_input("Position out of range\n");
                }
                Node<T>* targetNode = prev->next;
                prev->next = targetNode->next;
                delete targetNode;
                targetNode = NULL;
            }
            log("Deleted from position " + convertToString(position));
        }
        catch(const Errors::invalid_request& e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch(const Errors::invalid_input& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void deleteByElement(T data){
        try{
            if(head == NULL){
                // throw Errors::invalid_request("List is already empty. Cannot delete\033[0m\n"); //color
                throw Errors::invalid_request("List is already empty. Cannot delete\n");
            }
            if(head->data==data){
                deleteAtPosition(1);
            }else{
                Node<T>* prev = head;
                Node<T>* curr = head->next;
                while(curr && curr->data!=data){ // traversal to target node
                    prev = curr;
                    curr = curr->next;
                }
                if(curr == NULL){ // element not found
                    // throw Errors::invalid_request("Element not found in list. Cannot delete\033[0m\n"); //color
                    throw Errors::invalid_request("Element not found in list. Cannot delete\n");
                }
                prev->next = curr->next;
                delete curr;
                curr = NULL;
            }
            log(convertToString(data) +" Deleted from the list");
        }
        catch(const Errors::invalid_request& e){
            std::cerr << e.what() << std::endl;
        }
    }

    void reverse(){
        try
        {
            if(head == NULL){
                // throw Errors::invalid_request("list is empty. can not reverse\033[0m\n"); // list is empty //color
                throw Errors::invalid_request("list is empty. can not reverse\n"); // list is empty
            }else if(head->next == NULL){
                // throw Errors::invalid_request("list contains only one element. list unchanged\033[0m\n"); // only one node. No need to reverse. //color
                throw Errors::invalid_request("list contains only one element. list unchanged\n"); // only one node. No need to reverse.
            }else{
                Node<T>* prev = NULL;
                Node<T>* curr = head;
                while(curr!=NULL){ // traversal of list
                    Node<T>* forward = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = forward;
                }
                head = prev;
                log("List Reversed.");
            }
        }
        catch(const Errors::invalid_request& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void print(){
        try
        {
            // if(head == NULL){ // Empty List case handle
                // throw Errors::invalid_request("List is empty. Nothing to print\033[0m\n"); //color
                // throw Errors::invalid_request("List is empty. Nothing to print\n");
            // }
            Node<T>* temp = head;
            while(temp!= NULL){ // printing each node
                std::cout << temp->data << " -> ";
                temp = temp->next;
            }std::cout << "X" << std::endl;
        }
        catch(const Errors::invalid_request& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    ~linkedList() {
        try
        {
            Node<T>* temp;
            while (head != NULL) {
                temp = head;
                head = head->next;
                delete temp;
            }
            log("Linked List Destroyed\n");
            logFile.close(); // Close the log file when the object is destroyed.
            // if(logFile.is_open()) throw Errors::file_error("File is still open\033[0m\n"); //color
            if(logFile.is_open()) throw Errors::file_error("File is still open\n");
        }
        catch(const Errors::file_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};
#endif