//Lexikális fordító



//példa input: 2003ISTRAB2003>=ARVAI{*DAVID**}<>(**CSABA*)128TAMAS$
//példa output:<konstans><azonsító><reláció> <azonosító> <relácó>...<konstans><EOF>

#include <iostream>
#include <string.h> 
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "hu");

    string userinput= "";
    string output="";

    std::cout << "\nInput:\n~~~~~~~~~\n";

    getline(cin, userinput);
    int length =userinput.length();
    //cout << "Input length: "<<length;


   for (int i=0; i < length; ++i) {
      
       if (isdigit(userinput[i])) {
           while (isdigit(userinput[i])) {
               ++i;
           }
           output += "<konstans>";
       }
       if (isalpha(userinput[i])) {
           while (isalpha(userinput[i])) {
               ++i;
           }
           output += "<azonosító>";
       }
       if (userinput[i]==':' && userinput[i+1] == '=') {
           i=i+2;
           output += "<reláció>";
       }
       
       //--------Ha { karaktert talál végigmegy a maradék karakter sorozaton a } karakter elsõ elõfordulását keresve
       if (userinput[i] == '{') {
           for (int j=i; j < length; ++j) {
               if (userinput[j] == '}') {
                   i = j;
                   output += "<{}komment>";
                   break;
               }
           }
       }

       //--------Ha ( és * követi egymást végigmegy a maradék karakter sorozaton * ) karakterek elsõ elõfordulását keresve
       if (userinput[i] == '(' && userinput[i+1]=='*') {
           for (int j = i+2; j < length; ++j) {
               if (userinput[j] == '*' && userinput[j+1]==')') {
                   i = j+1;
                   output += "<(**)komment>";
                   break;
               }
           }
        }
       
       if (userinput[i] == '<' && userinput[i + 1] == '>') {
           output += "<reláció>";

       }

       if (userinput[i] == '<' && userinput[i + 1] == '=') {
           output += "<reláció>";

       }

       if (userinput[i] == '>' && userinput[i + 1] == '=') {
           output += "<reláció>";

       }

       

       //-----Amikor $ karaktert talál befejezi az elemzést
       if (userinput[i] == '$') {
           output += "<EOF>";
           break; 
       }
   }

   cout <<"\nOutput:\n~~~~~~~~~\n"<< output << "\n \n \n";
}