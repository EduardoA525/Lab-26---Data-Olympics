//Eduardo Avila
//COMSC - 210 - 5293
//Lab 26 - Data Olympics

#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

//this will hold final time
struct TotalTimes{
    long long vectorTime;
    long long setTime;
    long long listTime;
};

void bigRaceReading(vector<string> &readVector, list<string> &readList,
                    set<string> &readSet, TotalTimes &times);

void bigRaceSorting(vector<string> &sortVector, list<string> &sortList,
                    set<string> &sortSet, TotalTimes &times);

void bigRaceInserting(vector<string> &insertVector, list<string> &insertList,
                      set<string> &insertSet, TotalTimes &times);

void bigRaceDeleting(vector<string> &deleteVector, list<string> &deleteList,
                      set<string> &deleteSet, TotalTimes &times);

void bigRaceDisplay(TotalTimes &readingTimes, TotalTimes &sortingTimes,
                    TotalTimes &insertingTimes, TotalTimes &deletingTimes);

int main() {
    //SUPER CLEAN MAIN
    vector<string> mainVector;
    set<string> mainSet;
    list<string> mainList;

    TotalTimes readingTimes;
    TotalTimes sortingTimes;
    TotalTimes insertingTimes;
    TotalTimes deletingTimes;

    bigRaceReading(mainVector, mainList, mainSet, readingTimes);
    bigRaceSorting(mainVector, mainList, mainSet, sortingTimes);
    bigRaceInserting(mainVector, mainList, mainSet, insertingTimes);
    bigRaceDeleting(mainVector, mainList, mainSet, deletingTimes);

    bigRaceDisplay(readingTimes,sortingTimes,insertingTimes,deletingTimes);

    return 0;
}

void bigRaceReading(vector<string> &readVector, list<string> &readList,
                  set<string> &readSet, TotalTimes &times) {

    //Vector's reading race
    auto start = high_resolution_clock::now();

    ifstream finVector("codes.txt");
    if (!finVector.is_open()){
        cout << "Vector File Error." << endl;
        return;
    }

    string text;

    while (finVector >> text) {
        readVector.push_back(text);
    }

    finVector.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    times.vectorTime = duration.count();


    //List's reading race
    start = high_resolution_clock::now();

    ifstream finList("codes.txt");
    if (!finList.is_open()){
        cout << "List File Error." << endl;
        return;
    }

    while (finList >> text) {
        readList.push_back(text);
    }

    finList.close();

    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);

    times.listTime = duration.count();


    //Set's reading race
    start = high_resolution_clock::now();

    ifstream finSet("codes.txt");
    if (!finSet.is_open()){
        cout << "Set File Error." << endl;
        return;
    }

    while (finSet >> text) {
        readSet.insert(text);
    }

    finSet.close();

    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);

    times.setTime = duration.count();
}

void bigRaceSorting(vector<string> &sortVector, list<string> &sortList,
                    set<string> &sortSet, TotalTimes &times){
    //Vector's sorting
    auto start = high_resolution_clock::now();

    sort(sortVector.begin(), sortVector.end());

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-start);

    times.vectorTime = duration.count();

    //List's sorting
    start = high_resolution_clock::now();

    sortList.sort();

    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);

    times.listTime = duration.count();

    //Set sorting
    times.setTime = -1;
}

void bigRaceInserting(vector<string> &insertVector, list<string> &insertList,
                      set<string> &insertSet, TotalTimes &times){
    //Vector's insertion
    auto start = high_resolution_clock::now();

    insertVector.insert(insertVector.begin() + insertVector.size() / 2, "TESTCODE");

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    times.vectorTime = duration.count();

    //List's insertion
    start = high_resolution_clock::now();
    auto listMiddle = insertList.begin();

    advance(listMiddle,insertList.size() / 2);
    insertList.insert(listMiddle, "TESTCODE");

    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end-start);

    times.listTime = duration.count();
    
    //Set's insertion
    //since set is always sorted, we dont need to choose middle
    start = high_resolution_clock::now();

    insertSet.insert("TESTCODE");

    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    times.setTime = duration.count();

}

void bigRaceDeleting(vector<string> &deleteVector, list<string> &deleteList,
                     set<string> &deleteSet, TotalTimes &times){
    //Vector's deletion
    auto start = high_resolution_clock::now();

    deleteVector.erase(deleteVector.begin() + deleteVector.size() / 2);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    times.vectorTime = duration.count();

    //List's deletion
    start = high_resolution_clock::now();
    auto listMiddle = deleteList.begin();

    advance(listMiddle, deleteList.size() / 2);

    deleteList.erase(listMiddle);

    end = high_resolution_clock::now();

    duration = duration_cast<nanoseconds>(end-start);

    times.listTime = duration.count();

    //Set's deletion
    start = high_resolution_clock::now();
    auto middleSet = deleteSet.begin();
    advance(middleSet, deleteSet.size() / 2);
    deleteSet.erase(middleSet);
    
    end = high_resolution_clock::now();

    duration = duration_cast<nanoseconds>(end-start);

    times.setTime = duration.count();
}

void bigRaceDisplay(TotalTimes &readingTimes, TotalTimes &sortingTimes,
                    TotalTimes &insertingTimes, TotalTimes &deletingTimes){

    cout << "\n\t*** THE GRAND RACE OF THE AGES ***\n" << endl;
    cout << "RACERS:  Vector\t\tList\t\tSet" << endl;
    cout << "==================================================" << endl;

    cout << "READING: " << readingTimes.vectorTime << " ns\t"
         << readingTimes.listTime << " ns\t" << readingTimes.setTime << " ns"<< endl;

    cout << "SORTING: " << sortingTimes.vectorTime << " ns\t"
         << sortingTimes.listTime << " ns\t" << sortingTimes.setTime << " ns" << endl;

    cout << "INSERTING: " << insertingTimes.vectorTime << " ns\t"
         << insertingTimes.listTime << " ns\t" << insertingTimes.setTime << " ns" << endl;

    cout << "DELETING: " << deletingTimes.vectorTime << " ns\t"
         << deletingTimes.listTime << " ns\t" << deletingTimes.setTime << " ns" << endl;

    cout << "==================================================" << endl;
    cout << "\n\t*** THANK YOU TO OUR SPONSORS ***\n" << endl;
    cout << "\t\tProfessor Dietrich" << endl;
    cout << "\t\tDiablo Valley College" << endl;
    cout << "\t\tEduardo Avila\n" << endl;
}