#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <bits/stdc++.h>
#define SIZE 25000

using namespace std;

int error;
int flat;
long int lline;
int des;

struct Data
{
    int id;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    int hum;
    float tem;
    int date;
};

// struct Binary
// {
//     string hid;
//     string htime;
//     string htem;
//     string hhu;
// };


/* function to convert decimal to hexadecimal */
string decToHexa(int n)
{   
    /* char array to store hexadecimal number */
    string hexaDeciNum[100];
    string ans = "";
 
    /* counter for hexadecimal number array */
    int i = 0;
    while (n != 0) {
        /* temporary variable to store remainder */
        int temp = 0;
 
        /* storing remainder in temp variable. */
        temp = n % 16;
 
        /* check if temp < 10 */
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 87;
            i++;
        }
 
        n = n / 16;
    }

    if (i % 2 == 1) {
        hexaDeciNum[i++] = "0";
    }
    
    int space = 0;
    /* printing hexadecimal number array in reverse order */
    for (int j = i - 1; j >= 0; j--) {
        space++;
        ans += hexaDeciNum[j];
        if (space == 2) {
            ans += " ";
            space = 0;
        }
    }
    return ans;
}

/* function to convert time to second */
void ttosec(Data arr[],long int size) 
{   
    int date;
    time_t rawtime;
    struct tm * timeinfo;

    /* get current timeinfo: */
    time ( &rawtime ); 
    /* convert to struct: */
    timeinfo = localtime ( &rawtime ); 

    for (int i = 0; i < size; i++) {

        /* now modify the timeinfo to the given date: */
        timeinfo->tm_year   = arr[i].year - 1900;
        timeinfo->tm_mon    = arr[i].month - 1;    //months since January - [0,11]
        timeinfo->tm_mday   = arr[i].day;          //day of the month - [1,31] 
        timeinfo->tm_hour   = arr[i].hour;         //hours since midnight - [0,23]
        timeinfo->tm_min    = arr[i].min;          //minutes after the hour - [0,59]
        timeinfo->tm_sec    = arr[i].sec;          //seconds after the minute - [0,59]

        /* call mktime: create unix time stamp from timeinfo struct */
    
        arr[i].date = mktime(timeinfo);
    }
}

/* Perform -h command */
void h_command() {
    FILE *fptr;
    char c;

    /* Open readme file for reading */
    fptr = fopen("readme.txt", "r");
    c = fgetc(fptr);
    
    /* Print the content from readme.txt file */
    while (c != EOF) {
            printf ("%c", c); 
            c = fgetc(fptr);
        };
  
        fclose(fptr);
};

/* Function to sort the data */
void sort(Data arr[],long int size, int n) {
    bool swapped;
    do
    {
        swapped = false;
        if (des == 0)
            for (int count = 0; count < (size - 1); count++) {
                if (n  == 1)
                    if (arr[count].id > arr[count + 1].id) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 2)
                    if (arr[count].date > arr[count + 1].date) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 3)
                    if (arr[count].tem > arr[count + 1].tem) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 4)
                    if (arr[count].hum > arr[count + 1].hum) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
            
            }
        if (des == 1)
            for (int count = 0; count < (size - 1); count++) {
                if (n  == 1)
                    if (arr[count].id < arr[count + 1].id) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 2)
                    if (arr[count].date < arr[count + 1].date) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 3)
                    if (arr[count].tem < arr[count + 1].tem) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
                if (n == 4)
                    if (arr[count].hum < arr[count + 1].hum) {
                        swap(arr[count], arr[count + 1]);
                        swapped = true; 
                    }
            
            }
    } while (swapped);
    
}

/* function to convert real to binary */
string retobi(int n) {
    string temp, res;
    int i = 0;
    while (n != 0) {
        int du = n % 2;
        if (du == 1) 
            temp += "1";
        else 
            temp += "0";
        n /= 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        res += temp[j]; 
    }

    return res;
}

/* function to convert fraction to binary */
string fractobi(float n) {
    string res;
    int i = 0;
    while (i < 23) {
        n *= 2;
        if (n < 1) {
            res += "0";
            i++;
        }
        else {
            i++;
            res += "1";
            n -= 1;
        }
    }
    return res;
}

/* function to convert decimal to binary (IEEE 754) */
string detobi (float n) {
    float frac, ptr;
    int  real;
    int sign = 0;
    string res, sreal, sfrac, rres;
    string man;

    /* sign bit */
    if (n < 0) {
        res += "1";
        n *= -1;
    }
    else
        res += "0";

    frac = modf(n, &ptr);
    real = (int) ptr;

    /* exponent */
    sreal = retobi(real);
    int e = sreal.length();
    e += 126;
    res += retobi(e);


    /* mantissa */
    for (int i = 1; i < e - 126; i++) {
        res += sreal[i];
    }
    sfrac = fractobi(frac);

    res = res + sfrac;
    for (int i = 0; i < 32; i++) {
        rres += res[i];
    }

    return rres;

}

string decToHexa1(int n)
{   
    /* store hexadecimal number */
    string ans = "";
 
    /* check if temp < 10 */
    if (n < 10) {
        ans = n + 48;
    }
    else {
        ans = n + 87;
    }
    
    return ans;
}

string ietohexa(string st) {
    string res;
    int space = 0;
    int gr = 0, temp = 0;

    for (int i = 0; i < 32; i++) {
        if (st[i] == '1')
            temp += 1 * pow(2, 3-gr);
        if(gr == 3) {
            res += decToHexa1(temp);
            temp = 0;
            gr = -1;
            space ++;
        }
        if (space == 2) {
            res += " ";
            space = 0;
        }
        gr++;
    }

    return res;
}

/* Function to print the data to the output file */
void printout(Data arr[], long int size, const char *outp) {
    fstream myFile;
    string temp;
    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile << "id,time,temperature,humidity" << "\n";
        /* Print decrypted data to the output file. */
        for (int count = 0; count < size; count++) {
            myFile << "00" << " ";
            myFile << decToHexa(arr[count].id);
            myFile << decToHexa(arr[count].date);
            temp = detobi(arr[count].tem);
            myFile << ietohexa(temp);
            myFile << decToHexa(arr[count].hum);
            myFile << "ff";
            myFile << "\n";
        }
    }
    myFile.close();
}

void dtob(const char *inp, const char *outp, int n, char **s) {
    ifstream myFileStream(inp);

    if (!myFileStream.is_open()) {
        cout<<"File failed to open"<<endl;
        return;
    }

    int fline = 0;
    string line;
    string sid, syear, smonth, sday, shour, smin, ssec,stem,shum;
    Data sen[SIZE];
    

    while (getline(myFileStream,line)) {
        stringstream ss(line);
        getline(ss, sid, ',');
        getline(ss, syear, '-');
        getline(ss, smonth, '-');
        getline(ss, sday, ' ');
        getline(ss, shour, ':');
        getline(ss, smin, ':');
        getline(ss, ssec, ',');
        getline(ss, stem, ',');
        getline(ss, shum, '\n');

        if (shum == "")
            cout << "hihi"<<endl;

        if (fline == 1) {
            cout << shum << "\n";

            sen[lline].id = stoi(sid);
            sen[lline].year = stoi(syear);
            sen[lline].month = stoi(smonth);
            sen[lline].day = stoi(sday);
            sen[lline].hour = stoi(shour);
            sen[lline].min = stoi(smin);
            sen[lline].sec = stoi(ssec);
            sen[lline].tem = stof(stem);
            sen[lline].hum = stoi(shum);

            lline++;
        }
        fline = 1;
    }

    ttosec(sen,lline);

    /* Sort Data */
    sort(sen, lline, n);

    myFileStream.close();

    /* print to the output file */
    printout(sen, lline, outp);
    
}

void s_command(char **s, int n) {
    const char *inp, *outp;
    
    char ans;
    int ansn = 1;
 
    inp = s[1];
    outp = s[2];

    /* Check if input file exists or not */
    if (fopen(s[1],"r") == NULL) {
        printf("Error 07: %s could not be opened.\n", s[1]);
        error = 1;
    }

    else {
        /* Check if output file exists or not */
        if (fopen(s[2], "r") != NULL) {
            printf("Warning: %s already exists."
            " Do you wish to overwrite (y, n)? ", s[2]);
            ans = getchar();
            ansn = 0;
            if (ans == 'y')
                ansn = 1;
            else 
                error = 1;
        }

        /* Convert csv file to txt file */
        if (ansn == 1) {
            dtob(inp, outp, n, s);
        }
    }
}


void option_error(int n, char **s){
    
    
    if (n == 1){
        printf("Error 02: Unrecognized command."
        " Type “./dataprocess –h” for help. \n");
        return;
    }

    /* perform -h flag */
    else if (n == 2 && !(strcmp(s[n - 1],"-h")))
        h_command();
    
    else if (n == 2 && (strcmp(s[n - 1],"-h"))) {
         printf("Error 01: Unknown command."
        " Type “./dataprocess –h” for help.");
        return;
    }
    else if (2 < n && n < 5) {
        printf("Error 01: Unknown command."
        " Type “./dataprocess –h” for help.");
        return;
    }

    else if (n == 5 && !(strcmp(s[n - 1],"-id")) && !(strcmp(s[n - 2],"-s"))) {
        flat = 1;
        s_command(s, flat);
    }

    else if (n == 5 && !(strcmp(s[n - 1],"-ti")) && !(strcmp(s[n - 2],"-s"))) {
        flat = 2;
        s_command(s, flat);
    }

    else if (n == 5 && !(strcmp(s[n - 1],"-te")) && !(strcmp(s[n - 2],"-s"))) {
        flat = 3;
        s_command(s, flat);
    }

    else if (n == 5 && !(strcmp(s[n - 1],"-hu")) && !(strcmp(s[n - 2],"-s"))) {
        flat = 4;
        s_command(s, flat);
    }

    else if (n == 6 && !(strcmp(s[n - 2],"-id")) && !(strcmp(s[n - 3],"-s")) && !(strcmp(s[n - 1],"-des"))) {
        flat = 1;
        des = 1;
        s_command(s, flat);
    }

    else if (n == 6 && !(strcmp(s[n - 2],"-ti")) && !(strcmp(s[n - 3],"-s")) && !(strcmp(s[n - 1],"-des"))) {
        des = 1;
        flat = 2;
        s_command(s, flat);
    }

    else if (n == 6 && !(strcmp(s[n - 2],"-te")) && !(strcmp(s[n - 3],"-s")) && !(strcmp(s[n - 1],"-des"))) {
        flat = 3;
        des = 1;
        s_command(s, flat);
    }

    else if (n == 6 && !(strcmp(s[n - 2],"-hu")) && !(strcmp(s[n - 3],"-s")) && !(strcmp(s[n - 1],"-des"))) {
        des = 1;
        flat = 4;
        s_command(s, flat);
    }

}

int main(int argc, char *argv[]){
    /* Peform the command line or
    detect errors in the command line */
    option_error(argc, argv);

    return 0;
}