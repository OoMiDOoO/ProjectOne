// #include <bits/stdc++.h> //<<<<<
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Change if needed please notice that this includes
//Subjects in all groups e.g.: If you have subject A in group 1 and 2
//then subject_num will equal 2, or 4 including sections.
const int subject_num = 101; // added one because 1-indexed.

//Added recently beaware of bugs.
// Arrays that hold the input.
// PLease notice that the input is like this:
// SubjectName (no spaces) - Subject Code - Subject units:
// Day Periods Group number
// Prototype:
// DS INF210 3
// 1 1-2 1 // First day from the first to the second period, Group One.
// 4 4-6 1 // Lecture then Section or vice versa.
// 2 1-2 2
// 4 1-3 2
// 0 // Exit the subject
// 0 // Exit the function
// IF INPUT WHERE WRONG YOU WILL HAVE TO RE-ENTER IT AGAIN.. Sorry, I have not studied this much flexability yet.
string subject_names[subject_num];
string subject_codes[subject_num];
int subject_group[subject_num];
int subject_days[subject_num];
int subject_units[subject_num];
string subject_periods[subject_num];
int regeistered_indexes[subject_num];

// Functions:
// Prinall() >>  Where you can edit the input. But I am too lazy to write it.
// Input function, takes oredered input.
void input(int *subject_count);
// void sort(string subject_names[subject_num], string subject_codes[subject_num], int subject_group[], int subject_days[], int subject_units[], string subject_periods[subject_num], int* subject_count);
// Register funcion, too long function that has many options, but main goal is to be able to register subjects.
void reg(int *subject_count);
// Prints starting index of each inividual subject, should be updated to print it ordered 1- 2- 3-.
void print_subjects(int *subject_count);
// Prints all subject periods of the chosen index in reg function.
void print_chosen(int in, int counter, int *subject_count);
// Makes sure that newly chosen subject doesn't collide with older chosen subjects.
// Please be aware that this doesn't support periods more than 2 digits.
bool collision(int in, int counter);
// Prints information of subjects in registered_indexes[], total units.
void review_register(int *counter);
// Provides delete ability in registered_indexes[].
void deletion(int in, int *counter);
// Function that converts the registered_indexes[] to a .csv, for script.py to handle it and convert it (finally) to .xlsx.
void output(int counter);
// In future hopefully there will be a special function that creates every possible table from input.
// magic()

int main()
{
    // Input arrays were declared in main, but lately realised that if declared globally it would be
    // much much much easier to delcare functions and less complex :)
    int subject_count = 1;
    input(&subject_count);
    print_subjects(&subject_count);
    reg(&subject_count);
    return 0;
}

void input(int *subject_count)
{
    for (int i = 1; i < subject_num; i++)
    {
        cout << "If done with input type 0 then Enter." << '\n';
        cin >> subject_names[i];
        if (subject_names[i] == "0")
            break;
        cin >> subject_codes[i] >> subject_units[i];
        cout << subject_names[i] << ' ' << subject_codes[i] << ' ' << subject_units[i] << ":\n";
        int temp = i;
        for (i; i < subject_num; i++)
        {
            cin >> subject_days[i];
            if (subject_days[i] == 0)
            {
                // If the input is 0 we will uselessly store an embty line
                // and will actually have a "bug" because subject_count will not get incremented
                // aka one of the subjects (lines) will not be printed.
                i--;
                break;
            }
            cin >> subject_periods[i] >> subject_group[i];
            subject_names[i] = subject_names[temp];
            subject_codes[i] = subject_codes[temp];
            subject_units[i] = subject_units[temp];
            *subject_count += 1;
        }
    }
}

void print_subjects(int *subject_count)
{
    for (int i = 1; i < *subject_count; i++)
    {
        if (subject_codes[i] != subject_codes[i - 1])
        {
            cout << i << "- " << subject_names[i] << ' ' << ' ' << subject_codes[i] << ' ' << subject_units[i] << '\n';
        }
    }
}

void reg(int *subject_count)
{
    int in, counter = 0;
    bool flag;
    while (true)
    {
        cout << "Print subjects: -1" << '\n'
             << "Print Registered/Edit subjects: -2" << '\n';
        cout << "Choose one subject (using its index) to show its lectures and sections." << '\n';
        cout << "If done with registering enter 0." << '\n';
        flag = false;
        cin >> in;
        if (in == 0) // <<<
        {
            output(counter);
            return;
        }
        if (in == -1)
        {
            print_subjects(subject_count);
            continue; // <<<<
        }
        if (in == -2)
        {
            review_register(&counter);
            continue;
            // -2 if you want to print all registered subjects or edit them
            // review, (delete, finish.) -> Back to this function.
            // counter will be passed by refrence in case of deletion.
        }
        print_chosen(in, counter, subject_count); // print all periods of chosen subject index.
        cin >> in;
        if (in == 0) // <<<<<<???
            continue;

        if (in < 0 || in > *subject_count)
        {
            cout << "Please enter a valid index." << '\n';
            continue;
        }

        for (int i = 0; i < counter; i++)
        {
            if (subject_codes[in] == subject_codes[regeistered_indexes[i]])
            {
                cout << "<<This subject was registered before, the function will be called again.>>" << '\n';
                flag = true;
                break;
            }
        }
        if (flag)
            continue;

        //Collision function
        if (collision(in, counter) == false)
            continue;

        regeistered_indexes[counter] = in;
        counter++;
        if (subject_group[in + 1] == subject_group[in] && subject_codes[in + 1] == subject_codes[in])
        {
            regeistered_indexes[counter] = in + 1;
            counter++;
        }
    }
}

void print_chosen(int in, int counter, int *subject_count)
{
    for (int i = 0; i < counter; i++)
    {
        if (subject_codes[regeistered_indexes[i]] == subject_codes[in])
        {
            cout << "<<Be aware that this subject was registered before.>>" << '\n';
            cout << "If you want to edit registered subjects, you can enter -2." << '\n';
            break;
        }
    }
    cout << "Remember formation is:" << '\n';
    cout << "Subject name - Subject code - Day - Periods - Group" << '\n';
    for (int i = in; i < *subject_count; i++)
    {
        cout << i << "- " << subject_names[i] << ' ' << subject_codes[i];
        cout << ' ' << subject_days[i] << ' ' << subject_periods[i] << ' ' << subject_group[i] << '\n';
        if (subject_codes[i + 1] != subject_codes[in]) // + 1 to check before going into next iteration.
        {
            cout << "Choose subject by entering its index: ";
            break;
        }
    }
    return;
}

//Needs more testing.
bool collision(int in, int counter)
{
    int start = subject_periods[in][0] - 48;
    int end = subject_periods[in][2] - 48;
    int start_i, end_i;
    for (int i = 0; i < counter; i++)
    {
        start_i = subject_periods[regeistered_indexes[i]][0] - 48;
        end_i = subject_periods[regeistered_indexes[i]][2] - 48;
        if (subject_days[regeistered_indexes[i]] == subject_days[in])
        {
            if (start >= start_i && start <= end_i)
            {
                //Consider adding more information.
                cout << '\n'
                     << "<<There's a collision with " << regeistered_indexes[i] << "- " << subject_names[regeistered_indexes[i]] << ">>\n";
                return false;
            }
            else if (end >= start_i && end <= end_i)
            {
                cout << '\n'
                     << "<<There's a collision with " << regeistered_indexes[i] << "- " << subject_names[regeistered_indexes[i]] << ">>\n";
                return false;
            }
        }
    }
    // This part could be moved to where the function is called, instead of recursion call it twice in reg().
    if (subject_group[in] == subject_group[in + 1] && subject_codes[in] == subject_codes[in + 1])
    {
        return collision(in + 1, counter);
    }
    cout << '\n'
         << "Registered successfully : )\n";
    return true;
}

//Should have used vector to make deletion easeir?
void review_register(int *counter)
{
    int total_units = 0;
    int in;
    cout << "These are the subjects you have registered: " << '\n';
    for (int i = 0; i < *counter; i++)
    {
        cout << '\n';
        cout << regeistered_indexes[i] << "- " << subject_names[regeistered_indexes[i]] << ' ' << subject_codes[regeistered_indexes[i]] << ' ';
        cout << subject_days[regeistered_indexes[i]] << ' ' << subject_periods[regeistered_indexes[i]] << ' ' << subject_group[regeistered_indexes[i]] << ' ' << subject_units[regeistered_indexes[i]];
        total_units += subject_units[regeistered_indexes[i]]; // Caculates it twice.
    }
    cout << '\n'
         << "Total units: " << total_units << '\n';
    cout << "If you are done with reviewing registeration enter 0, if you want to delete a subject press -1: ";
    cin >> in;
    //Another if condition for -1?
    if (in == 0)
        return;
    if (in == -1)
    {
        cout << "Enter the index of the subject you wish to delete: ";
        cin >> in;
        //Deletion of section/lecture first, so indexes remain the same.
        if (subject_codes[in + 1] == subject_codes[in] && subject_group[in + 1] == subject_group[in])
        {
            deletion(in + 1, counter);
        }
        deletion(in, counter);
        return;
    }
}

// I consider this a very bad implementation of deletion.
void deletion(int in, int *counter)
{
    for (int i = 0; i < *counter; i++)
    {
        if (regeistered_indexes[i] == in)
        {
            for (int j = i; j < *counter - 1; j++) //You can get out of range, if you really want that.
            {
                swap(regeistered_indexes[j], regeistered_indexes[j + 1]);
            }
            *counter -= 1;
        }
    }
}


void output(int counter)
{
    ofstream table;
    table.open("output.csv");
    for(int i = 0; i < counter; i++)
    {
        table << subject_names[regeistered_indexes[i]] << " ,";
        table << subject_codes[regeistered_indexes[i]] << " ,";
        table << subject_units[regeistered_indexes[i]] << " ,";
        table << subject_group[regeistered_indexes[i]] << " ,";
        table << subject_days[regeistered_indexes[i]] << ",";
        table << subject_periods[regeistered_indexes[i]] << '\n';
    }
    table.close();
    //A way to excute script.py should be added here.
    return;
}