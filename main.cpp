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



/*Este codigo enceuntra la subcadena comun mas larga entre dos cadenas.
Utiliza una matriz(dp) para almacenar las longitudes de las subcadenas comunes
entre s1 y s2. Si los caracteres coinciden, aumenta la longitud de la subcadena
,si no, la reinica. La funcion retorna los indices donde comienza y termina la
subcadena mas larga en s1.
Time complexity: O(M*N)
Space complexity: O(M*N)*/

pair<int, int> longuestCommonSubstring(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    int dp[n + 1][m + 1];
    int mx = 0, end = -1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                if (mx < dp[i][j]) {
                    mx = dp[i][j];
                    end = i - 1;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return {end - mx + 1, end};
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

     // Perform the longest common substring analysis
    auto [start, end] = LongestCommonSubstring(transmission1, transmission2);
    cout << "\nLongest common substring between transmission1.txt and transmission2.txt:\n";
    cout << "Start position in transmission1.txt: " << start << "\n";
    cout << "End position in transmission1.txt: " << end << "\n";
    cout << "Length: " << end - start + 1 << " characters\n";


    return 0; 
}
