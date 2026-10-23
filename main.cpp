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

const int MAX_RACES = 15;

//vars for 3d array
const int currSim = 0;
const int totalSim = 1;

const int readSim = 0;
const int sortSim = 1;
const int insertSim = 2;
const int deleteSim = 3;

const int vectorNum = 0;
const int listNum = 1;
const int setNum = 2;

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
    //3d array. 2 is for current and total sims, 4 is the operations
    //and 3 is the containers (vec,list,set)
    long long results[2][4][3] = {};

    //loop will create a new race with resetted numbers
    for (int raceCounter = 0; raceCounter < MAX_RACES; raceCounter++){
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

        //3d array insertions here
        //Reading times, sorting times, inserting, deleting
        //then add all results before looping again
        results[currSim][readSim][vectorNum] = readingTimes.vectorTime;
        results[currSim][readSim][listNum] = readingTimes.listTime;
        results[currSim][readSim][setNum] = readingTimes.setTime;

        results[currSim][sortSim][vectorNum] = sortingTimes.vectorTime;
        results[currSim][sortSim][listNum] = sortingTimes.listTime;
        results[currSim][sortSim][setNum] = sortingTimes.setTime;

        results[currSim][insertSim][vectorNum] = insertingTimes.vectorTime;
        results[currSim][insertSim][listNum] = insertingTimes.listTime;
        results[currSim][insertSim][setNum] = insertingTimes.setTime;

        results[currSim][deleteSim][vectorNum] = deletingTimes.vectorTime;
        results[currSim][deleteSim][listNum] = deletingTimes.listTime;
        results[currSim][deleteSim][setNum] = deletingTimes.setTime;

        //Add all current results to total results
        results[totalSim][readSim][vectorNum] += results[currSim][readSim][vectorNum];
        results[totalSim][readSim][listNum] += results[currSim][readSim][listNum];
        results[totalSim][readSim][setNum] += results[currSim][readSim][setNum];
        
        results[totalSim][readSim][vectorNum] += results[currSim][readSim][vectorNum];
        results[totalSim][readSim][listNum] += results[currSim][readSim][listNum];
        results[totalSim][readSim][setNum] += results[currSim][readSim][setNum];
        
        results[totalSim][readSim][vectorNum] += results[currSim][readSim][vectorNum];
        results[totalSim][readSim][listNum] += results[currSim][readSim][listNum];
        results[totalSim][readSim][setNum] += results[currSim][readSim][setNum];
        

    }




    //bigRaceDisplay(readingTimes,sortingTimes,insertingTimes,deletingTimes);

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