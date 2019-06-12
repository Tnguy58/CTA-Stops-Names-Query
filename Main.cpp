// Project One by Timothy Nguyen 9/16/17

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/*
    get_number_of_lines takes in inputfile then returns the number of lines.
 */
int get_number_of_lines(string);

/*
 fill_arrays takes stop_id[], stop_names[] and inputfile then it fills the arrays.
 */
void fill_arrays(int stop_id[], string stop_names[], string inputfile);

/*
 user_interface lets users interact by asking for stop_id and displays the apropriate stop_name.
 */
void user_interface(int stop_id[], string stop_names[], int number_of_lines);

int main(){
    
    string inputfile = "stops.txt";
    int number_of_lines = get_number_of_lines(inputfile);
    
    // Initialize arrays.
    int stop_id[number_of_lines];
    string stop_names[number_of_lines];
    
    // Fill in Arrays.
    fill_arrays(stop_id, stop_names, inputfile);
    
    // User interface section.
    user_interface(stop_id, stop_names, number_of_lines);
    
    return 0;
}

int get_number_of_lines(string inputfile) {

    int i, j;
    char c;
    string line;
    ifstream file;
    
    file.open(inputfile);
    
    cout << "Opening " << inputfile << " ...  ";
    
    if (file.is_open())
    {
        while (getline(file, line))
        {
            // Count Lines
            i++;
            
            //  Count Stops
            if ((line.find("\"") + 1) and (line.find("\",\""))) {
                j++;
            }
        }
        
        // To count the last line.
        i++;
        
        file.close();
        
        cout << "Counted : " << i << " lines ...  ";
        cout << "Counted : " << j << " stops." << endl;
    }

    return i;
}

void fill_arrays(int stop_id[], string stop_names[], string inputfile) {

    int i;
    string line;
    ifstream file;
    
    file.open(inputfile);
    
    if (file.is_open())
    {
        while (getline(file, line))
        {
            // Gets stop_id_num by getting [0 to the first comma].
            int stop_id_helper = line.find(",");
            string stop_id_num = line.substr(0,stop_id_helper);
            
            // Converting String to Integer and storing in stop_id[].
            int int_id_num = atoi(stop_id_num.c_str());
            stop_id[i] = int_id_num;
            
            // Retrieve CTA stop name using substr() and storing to stop_names[].
            stop_names[i] = line.substr(line.find("\"") + 1, line.find("\",\"") - line.find("\"") - 1);
            i++;
        }
        file.close();
    }
}

void user_interface(int stop_id[], string stop_names[], int number_of_lines) {
    
    bool keep_going = true;
    bool in_list = false;
    int stop, j;
    
    while (keep_going) {
        cout << "Give a stop id (0 to stop) : ";
        cin >> stop;
        
        // Checks if CTA-stop exists.
        for(int i = 0; i < number_of_lines; i++){
            if(stop_id[i] == stop){
                // j is the practical index we use to access the arrays, not stop.
                j = i;
                in_list = true;
            }
        }
        
        if (stop == 0) {
            keep_going = false;
        }
        else if (in_list == true) {
            cout << "Stop " << stop_id[j] << " has name \"" << stop_names[j] << "\"" << endl;
        }
        else {
            cout << "There is no stop with id " << stop << endl;
        }
        in_list = false;
    }
}
