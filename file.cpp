#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inputFile("properties.json");
    string jsonContent;
    
    if (inputFile.is_open()) {
        // Read the entire JSON content from the file
        string line;
        while (getline(inputFile, line)) {
            jsonContent += line;
        }
        inputFile.close();

        // Find the position of the version field
        size_t versionPos = jsonContent.find("\"version\":");
        //cout<<versionPos<<endl;
        
        if (versionPos != string::npos) {
            // Find the position of the version value
            size_t versionValueStart = jsonContent.find("\"", versionPos + 10) + 1;// in find first part is for searing word and second part is for starting point latter where should we start the search
            //cout<<versionValueStart<<endl;
            size_t versionValueEnd = jsonContent.find("\"", versionValueStart);
            // Extract the current version value
            string currentVersion = jsonContent.substr(versionValueStart, versionValueEnd - versionValueStart);//substr(start,length)
            //cout<<currentVersion<<endl;

            // Increment the version number
            int loc = currentVersion.rfind('.');//last occurance
            if (loc != string::npos) {
                string str = currentVersion.substr(loc + 1);
                int versionNumber = stoi(str);
                ++versionNumber;
                currentVersion = currentVersion.substr(0, loc + 1) + to_string(versionNumber);
            } else {
                cerr << "Invalid version format." << endl;
                return 1;
            }

            // Replace the old version with the new version in the JSON content7
            jsonContent.replace(versionValueStart, versionValueEnd - versionValueStart, currentVersion);//replace(startPoint,lenth,newcontaint)

            // Write the updated JSON content back to the file
            ofstream outputFile("properties.json");
            if (outputFile.is_open()) {
                outputFile << jsonContent;
                outputFile.close();
                cout << "Version incremented to: " << currentVersion << endl;
            } else {
                cerr << "Error opening output file." << endl;
                return 1;
            }
        } else {
            cerr << "Version field not found in JSON." << endl;
            return 1;
        }
    } else {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    return 0;
}
