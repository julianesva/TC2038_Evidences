#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

//mcode1 and mcode 3 in transmission 1.
//mcode2 and mcode 1 in transmission 2.


//mcode1 
/*The palindromes are:

Larger -> 99C8B65E4F3A1A3F4E56B8C99
5A1F0B343B0F1A5
2F454F2*/

//mcode2 
/*The palindromes are:

A1B2C3D4E556E4D3C2B1A
78F1E23F4F32E1F87
Larger -> 9B00E7A1C2F12FF21F2C1A7E00B9*/

//mcode3 
/*The palindromes are:

Larger -> 45E6D9F8C7B6A9A6B7C8F9D6E54
12345FF54321
A1B21CDEFFEDC12B1A*/

void LPScreate(const string& virus, vector<int>& lps){
    // Step 1: Build the LPS (Longest Prefix Suffix) array
        int prevLPS = 0;  // Length of the previous longest prefix suffix
        int i = 1;        // Current index in pattern

        while (i < virus.size()) {
            if (virus[i] == virus[prevLPS]) {
                lps[i] = prevLPS + 1;
                prevLPS++;
                i++;
            } else {
                if (prevLPS == 0) {
                    lps[i] = 0;
                    i++;
                } else {
                    prevLPS = lps[prevLPS - 1];
                }
            }
        }
}

int KMPsearch(const std::string &transmissions, const std::string &virus) {
        if (virus.empty()) {
            return 0;
        }

        std::vector<int> lps(virus.size(), 0);
        LPScreate(virus, lps);//We create the LPS array in order to know how many comparissions we can avoid.

        // Step 2: Perform KMP search
        int i = 0;  // Pointer for text
        int j = 0;  // Pointer for pattern

        while (i < transmissions.size()) {
            if (transmissions[i] == virus[j]) {
                i++;
                j++;
            } else {
                if (j == 0) {
                    i++;
                } else {
                    j = lps[j - 1];
                }
            }

            // If we have matched the entire pattern
            if (j == virus.size()) {
                return i - virus.size();  // Found the match, return the starting index
            }
        }

        return -1;  // No match found
    }






    /*Este codigo enceuntra la subcadena comun mas larga entre dos cadenas.
Utiliza una matriz(dp) para almacenar las longitudes de las subcadenas comunes
entre s1 y s2. Si los caracteres coinciden, aumenta la longitud de la subcadena
,si no, la reinica. La funcion retorna los indices donde comienza y termina la
subcadena mas larga en s1.
Time complexity: O(M*N)
Space complexity: O(M*N)*/

pair<int, int> LongestCommonSubstring(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int mx = 0;
    int end = -1; 
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > mx) {
                    mx = dp[i][j];
                    end = i - 1;  
                }
            }
        }
    }
    
    if (mx > 0) {
        return {end - mx + 1, end};
    }
    
    return {-1, -1};
}

int main (){

    string virus1;
    string virus2;
    string virus3;
    string transmission1;
    string transmission2;

    const string directory = "Input_texts/";

    vector<string> filenames = {"mcode1.txt","mcode2.txt","mcode3.txt","transmission1.txt","transmission2.txt"};
    vector<string> filestosave = {virus1, virus2, virus3, transmission1, transmission2};
    vector<string> virus;
    vector<string> transmissions;

    int files_size = filenames.size();

    for(int i = 0; i < files_size; i++){
        
        
        string filepath = directory + filenames[i];
        std::ifstream file(filepath);  // Open the file
        if (!file.is_open()) {            // Check if the file opened successfully
            std::cerr << "Error: Could not open the file!" << std::endl;
            return 1;
        }

        std::string line;
        std::string fullText;  // This will store all the lines in one string

        // Read the file line by line
        while (std::getline(file, line)) {
            fullText += line;  // Append the line to fullText
        }

        file.close();  // Close the file when done

        filestosave[i] = fullText;

    }

    for (int i = 0; i < filestosave.size() ; i++){

        if (filenames[i].find("mcode") != string::npos){
            virus.push_back(filestosave[i]);
        }
        else{
            transmissions.push_back(filestosave[i]);
        }
    }

    int sizev= virus.size();
    int sizet = transmissions.size();

    for (int i = 0; i < sizet ; i++){
        for (int j = 0; j < sizev ; j++){
            int substrpos = KMPsearch(transmissions[i], virus[j]);
            if (substrpos != -1){
                cout<< "TRUE : The transmission"<< i+1 << " contains the substring mcode" << j+1 << endl;
            }
            else{cout<< "FALSE : The transmission"<< i+1 << " don't contains the substring mcode" << j+1 << endl;}
        }
    }

    auto [start, end] = LongestCommonSubstring(transmission1, transmission2);
    if (start != -1 && end != -1) {
        cout << "\nLongest common substring between transmission1.txt and transmission2.txt:\n";
        cout << "Start position in transmission1.txt: " << start << "\n";
        cout << "End position in transmission1.txt: " << end << "\n";
        cout << "Length: " << end - start + 1 << " characters\n";
        cout << "Longest common substring: " << transmission1.substr(start, end - start + 1) << "\n";
    } else {
        cout << "No common substring found between the two transmissions.\n";
    }

    return 0;
}
