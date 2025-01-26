#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Define Person class
class Person
{
private:
    // private data members of the Person class
    string name;
    string jobId; 
    double annualIncome;
    double chargeableIncome;
    double estimatedTax;

public:
    // Default constructor
    Person()
    {
        name = "";
        jobId = "";
        annualIncome = 0.0;
        chargeableIncome = 0.0;
        estimatedTax = 0.0;
    }

    // Constructor with parameters
    Person(const string &Name, const string &JobId, double AnnualIncome)
    {
        name = Name;
        jobId = JobId;
        annualIncome = AnnualIncome;
        chargeableIncome = annualIncome * (1 - 0.13); // deduct 13% from the individual's total income.
        estimatedTax = 0.0;
    }

    // Copy constructor
    Person(const Person &other)
    {
        name = other.name;
        jobId = other.jobId;
        annualIncome = other.annualIncome;
        chargeableIncome = other.chargeableIncome;
        estimatedTax = other.estimatedTax;
    }

    // Assignment operator
    Person &operator=(const Person &other)
    {
        if (this != &other)
        {
            name = other.name;
            jobId = other.jobId;
            annualIncome = other.annualIncome;
            chargeableIncome = other.chargeableIncome;
            estimatedTax = other.estimatedTax;
        }
        return *this; // return the current object
    }

    // compute tax
    void computeTax()
    {
        double taxSum = 0.0;

        if (chargeableIncome <= 0)
        {
            taxSum = 0.0;
        }
        else if (chargeableIncome <= 5000)
        {
            taxSum = 0.0;
        }
        else if (chargeableIncome <= 20000)
        {
            // First 5,000 is tax-free, remaining part taxed at 1%
            taxSum = (chargeableIncome - 5000) * 0.01;
        }
        else if (chargeableIncome <= 35000)
        {
            // First 20,000 accumulated tax is 150, remaining part taxed at 3%
            taxSum = 150 + (chargeableIncome - 20000) * 0.03;
        }
        else if (chargeableIncome <= 50000)
        {
            // First 35,000 accumulated tax is 600, remaining part taxed at 6%
            taxSum = 600 + (chargeableIncome - 35000) * 0.06;
        }
        else if (chargeableIncome <= 70000)
        {
            // First 50,000 accumulated tax is 1,500, remaining part taxed at 11%
            taxSum = 1500 + (chargeableIncome - 50000) * 0.11;
        }
        else if (chargeableIncome <= 100000)
        {
            // First 70,000 accumulated tax is 3,700, remaining part taxed at 19%
            taxSum = 3700 + (chargeableIncome - 70000) * 0.19;
        }
        else if (chargeableIncome <= 400000)
        {
            // First 100,000 accumulated tax is 9,400, remaining part taxed at 25%
            taxSum = 9400 + (chargeableIncome - 100000) * 0.25;
        }
        else if (chargeableIncome <= 600000)
        {
            // First 400,000 accumulated tax is 84,400, remaining part taxed at 26%
            taxSum = 84400 + (chargeableIncome - 400000) * 0.26;
        }
        else if (chargeableIncome <= 2000000)
        {
            // First 600,000 accumulated tax is 136,400, remaining part taxed at 28%
            taxSum = 136400 + (chargeableIncome - 600000) * 0.28;
        }
        else
        {
            // First 2,000,000 accumulated tax is 528,400, remaining part taxed at 30%
            taxSum = 528400 + (chargeableIncome - 2000000) * 0.30;
        }

        estimatedTax = taxSum;
    }

    // Getter functions
    string getName() const { return name; }
    string getJobId() const { return jobId; }
    double getAnnualIncome() const { return annualIncome; }
    double getChargeableIncome() const { return chargeableIncome; }
    double getEstimatedTax() const { return estimatedTax; }

    // function to print the information for UI
    void printInfo() const
    {
        cout << left << setw(18) << name << " "
             << setw(7) << jobId << " "
             << setw(12) << fixed << setprecision(2) << annualIncome << " "
             << setw(12) << chargeableIncome << " "
             << setw(10) << estimatedTax << endl;
    }
};

// Define nodeType struct
struct nodeType
{
    Person info;
    nodeType *link;
};

// Define linkedList class
class linkedList
{
private:
    nodeType *first; // link to the first node
    nodeType *last;  // link to the last node
    int count;       // count of nodes

public:
    // constructor and destructor for linkedList
    linkedList()
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    ~linkedList()
    {
        destroyList();
    }

    // destroy the linkedList
    void destroyList()
    {
        nodeType *temp;
        while (first != nullptr)
        {
            temp = first;
            first = first->link;
            delete temp;
        }
        last = nullptr;
        count = 0;
    }

    // check if the linkedList is empty
    bool isEmpty() const
    {
        return (first == nullptr);
    }

    // function to insert a node at the end of the linkedList
    void insertLast(const Person &p)
    {
        nodeType *newNode = new nodeType;
        newNode->info = p;
        newNode->link = nullptr;

        if (isEmpty())
        {
            first = newNode;
            last = newNode;
        }
        else
        {
            last->link = newNode;
            last = newNode;
        }
        count++;
    }

    // function to print the linkedList
    void printList() const
    {
        if (isEmpty())
        {
            cout << "The linkedList is empty.\n";
            return;
        }

        cout << endl;
        cout << "Name               Job ID  Annual      Chargeable  Estimated\n"
             << "------------------------------------------------------------\n";

        nodeType *current = first;
        while (current != nullptr)
        {
            current->info.printInfo();
            current = current->link;
        }

        cout << endl;
    }

    // Search by jobId
    nodeType *searchByJobId(const string &id) const
    {
        nodeType *current = first;

        while (current != nullptr)
        {
            if (current->info.getJobId() == id)
            {
                return current;
            }
            current = current->link;
        }

        return nullptr;
    }

    // Delete node by jobId
    bool deleteByJobId(const string &id)
    {
        if (isEmpty())
            return false;

        nodeType *current = first;
        nodeType *trail = nullptr;
        bool found = false;

        while (current != nullptr && !found)
        {
            if (current->info.getJobId() == id)
                found = true;
            else
            {
                trail = current;
                current = current->link;
            }
        }
        if (!found)
            return false; // if not found then return false

        // if the node to be deleted is the first node then:
        if (current == first)
        {
            first = first->link;
            if (first == nullptr)
                last = nullptr;
        }
        else
        {
            trail->link = current->link;
            if (current == last)
                last = trail;
        }

        delete current;
        count--; // decrease the count of nodes
        return true;
    }

    // Save list to file
    bool saveToFile(const string& filename) const
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cout << "Error: Cannot open file for writing: " << filename << endl;
            return false;
        }

        nodeType* current = first;
        while (current != nullptr)
        {
            // Write in the same format as input: name,jobId,annualIncome
            outFile << current->info.getName() << ","
                   << current->info.getJobId() << ","
                   << fixed << setprecision(2) 
                   << current->info.getAnnualIncome() << endl;
            current = current->link;
        }

        outFile.close();
        return true;
    }

    // Display tax category counts
    void displayTaxCategoryCounts() const
    {
        // Counters for each category
        int categoryA = 0, categoryB = 0, categoryC = 0, categoryD = 0, categoryE = 0;
        int categoryF = 0, categoryG = 0, categoryH = 0, categoryI = 0, categoryJ = 0;

        // Traverse the list
        nodeType* current = first;
        while (current != nullptr)
        {
            double income = current->info.getChargeableIncome();

            // Determine the category
            if (income <= 5000)
                categoryA++;
            else if (income <= 20000)
                categoryB++;
            else if (income <= 35000)
                categoryC++;
            else if (income <= 50000)
                categoryD++;
            else if (income <= 70000)
                categoryE++;
            else if (income <= 100000)
                categoryF++;
            else if (income <= 400000)
                categoryG++;
            else if (income <= 600000)
                categoryH++;
            else if (income <= 2000000)
                categoryI++;
            else
                categoryJ++;

            current = current->link;
        }

        // Display the counts
        cout << "\nTax Category Counts:\n";
        cout << "Category A (0 - 5,000): " << categoryA << endl;
        cout << "Category B (5,001 - 20,000): " << categoryB << endl;
        cout << "Category C (20,001 - 35,000): " << categoryC << endl;
        cout << "Category D (35,001 - 50,000): " << categoryD << endl;
        cout << "Category E (50,001 - 70,000): " << categoryE << endl;
        cout << "Category F (70,001 - 100,000): " << categoryF << endl;
        cout << "Category G (100,001 - 400,000): " << categoryG << endl;
        cout << "Category H (400,001 - 600,000): " << categoryH << endl;
        cout << "Category I (600,001 - 2,000,000): " << categoryI << endl;
        cout << "Category J (Above 2,000,000): " << categoryJ << endl;
    }
};

int main()
{
    // create the linkedList
    linkedList myList;

    int choice;
    bool isFileLoaded = false; // check if the file is loaded
    do
    {
        cout << "\n=============== iTaxPro System ===============\n"
             << "1. Load data from file and calculate tax amount\n"
             << "2. Display all personnel information in the chain list\n"
             << "3. Add a new personnel\n"
             << "4. Display personnel estimated tax based on Job ID\n"
             << "5. Delete personnel data based on Job ID\n"
             << "6. Display total number of individuals in each tax category\n"
             << "0. Exit\n"
             << "==============================================\n"
             << "Please select your choice: ";

        // input validation for choice
        while (true)
        {
            cin >> choice;
            if (cin.fail())
            {
                cin.clear(); // clear the buffer
                cin.ignore(1000, '\n'); 
                cout << "Invalid input, please try again.\n";
            }
            else // if the input is a number, then break the loop
            {
                break;
            }
        }

        if (choice == 1)
        {
            if (isFileLoaded)
            {
                cout << "DataFile already loaded. Please select another option.\n";
                continue;
            }

            // define the filename
            string filename = "DataFile.txt";

            ifstream thefile(filename);
            if (!thefile)
            {
                cout << "Cannot open file: " << filename << endl;
                continue;
            }

            // read the file
            while (!thefile.eof())
            {
                string line;
                if (!getline(thefile, line))
                    break; // read a whole line
                if (line.empty())
                    continue; // skip empty lines

                // find the comma to determine the name, jobId, and income in the file
                string::size_type comma1 = line.find(',');
                string::size_type comma2 = line.rfind(',');

                if (comma1 == string::npos || comma2 == string::npos || comma1 == comma2)
                {
                    // if the format is wrong, then skip
                    continue;
                }

                // get the name, jobId, and income
                string name = line.substr(0, comma1);
                string jobId = line.substr(comma1 + 1, comma2 - (comma1 + 1));
                string incomeS = line.substr(comma2 + 1);

                double income = stod(incomeS);

                // create a Person object
                Person tempP(name, jobId, income);
                // compute the tax
                tempP.computeTax();
                // insert the node at the end of the linkedList
                myList.insertLast(tempP);
            }

            thefile.close();

            isFileLoaded = true; // set the flag to true
            
            cout << "Data has been loaded from file \"" << filename << "\" and inserted into the list.\n";
        }
        else if (choice == 2) // Display all personnel information in the chain list
        {
            // check if the file is loaded
            if (!isFileLoaded)
            {
                cout << "DataFile is not loaded. Please select option 1 to load data first.\n";
                continue;
            }

            // Display list
            myList.printList();
        }
        else if (choice == 3) // Add a new personnel
        {
            // check if the file is loaded
            if (!isFileLoaded)
            {
                cout << "DataFile is not loaded. Please select option 1 to load data first.\n";
                continue;
            }

            // Add a new personnel
            string name, jobId;
            double income;

            cout << "\nEnter new personnel information:\n";
            cout << "Name: ";
            cin.ignore(); // Clear buffer
            getline(cin, name); // Allow spaces in name

            cout << "Job ID: ";
            cin >> jobId;

            // Validate if jobId already exists
            if (myList.searchByJobId(jobId) != nullptr)
            {
                cout << "Error: Job ID already exists!\n";
                continue;
            }

            cout << "Annual Income: ";
            while (!(cin >> income) || income < 0)
            {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            // Create new person and compute tax
            Person newPerson(name, jobId, income);
            newPerson.computeTax();

            // Add to list
            myList.insertLast(newPerson);
            cout << "\nNew personnel added successfully!\n";
        }
        else if (choice == 4) // Search personnel (based on Job ID)
        {
            // check if the file is loaded
            if (!isFileLoaded)
            {
                cout << "DataFile is not loaded. Please select option 1 to load data first.\n";
                continue;
            }

            // Search
            cout << "Please enter Job ID to search: ";
            string id;
            cin >> id;
            nodeType *result = myList.searchByJobId(id);
            if (result != nullptr)
            {
                cout << "\nFound information:\n";
                cout << "Name               Job ID  Annual      Chargeable  Estimated\n"
                     << "------------------------------------------------------------\n";
                result->info.printInfo();
            }
            else
            {
                cout << "No information found for Job ID = " << id << "\n";
            }
        }
        else if (choice == 5) // Delete Personnel (based on Job ID)
        {
            // check if the file is loaded
            if (!isFileLoaded)
            {
                cout << "DataFile is not loaded. Please select option 1 to load data first.\n";
                continue;
            }

            // Delete
            cout << "Please enter Job ID to delete: ";

            string delId;
            cin >> delId;
            bool ok = myList.deleteByJobId(delId);

            if (ok)
            {
                cout << "Delete successful\n";
            }
            else
            {
                cout << "Not found or list is empty. Delete failed.\n";
            }
        }
        else if (choice == 6) // display total number of individuals in each tax category
        {
            // check if the file is loaded
            if (!isFileLoaded)
            {
                cout << "DataFile is not loaded. Please select option 1 to load data first.\n";
                continue;
            }
            
            myList.displayTaxCategoryCounts();
        }
        else if (choice == 0)
        {
            // Save data back to file before exit
            if (isFileLoaded)
            {
                if (myList.saveToFile("DataFile.txt"))
                {
                    cout << endl;
                    cout << "Data has been saved to file successfully.\n";
                }
                else
                {
                    cout << "Warning: Failed to save data to file.\n";
                }
            }
            cout << "Thank you for using iTaxPro system. Goodbye!\n";

            // pause the program and exit
            cout << "Press Enter to exit...";
            cin.get();
            cin.get();  
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}