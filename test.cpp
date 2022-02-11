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

struct Binary
{
    string hpac;
    string hid;
    string htime;
    string htem;
    string hhu;
};

int logop;

int packetl;

/* Local variables store date and time values 
as a number */
int nyear, nmonth, nday, 
nhours, nminutes, nseconds;

/* Local variables store the name of 
input and output file without extension */
char new_inp[50], new_outp[50];

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
            packetl ++;
            ans += " ";
            space = 0;
        }
    }
    return ans;
}

/* function to convert time to second */
void ttosec(Data arr[],long int size) 
{   
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
            packetl++;
            res += " ";
            space = 0;
        }
        gr++;
    }

    return res;
}

/* print out date and time */
char cmonth[6];
void current_time(){
    /* time_t is arithmetic time type */
    time_t now;

    /* time() returns the current time of
    the system as a time_t value */
    time(&now);

    /* Localtime converts a time_t value to calendar time */
    struct tm *local = localtime(&now);

    nhours = local->tm_hour;             /* Get hours (0 - 23)   */
    nminutes = local->tm_min;            /* Get minutes (0 - 59) */
    nseconds = local->tm_sec;            /* Get seconds (0 - 59) */

    nday = local->tm_mday;               /* Get day (1 to 31)    */
    nmonth = local -> tm_mon + 1;        /* Get month (0 to 11)  */
    nyear = local -> tm_year + 1900;     /* Get year since 1900  */

    /* Convert month 
    from number to word */ 
    switch (nmonth)
    {
    case 1:
        strcpy(cmonth,"Jan");
        break;
    case 2:
        strcpy(cmonth,"Feb");
        break;
    case 3:
        strcpy(cmonth,"Mar");
        break;
    case 4:
        strcpy(cmonth,"Apr");
        break;
    case 5:
        strcpy(cmonth,"May");
        break;
    case 6:
        strcpy(cmonth,"Jun");
        break;
    case 7:
        strcpy(cmonth,"Jul");
        break;
    case 8:
        strcpy(cmonth,"Aug");
        break;
    case 9:
        strcpy(cmonth,"Sep");
        break;
    case 10:
        strcpy(cmonth,"Oct");
        break;
    case 11:
        strcpy(cmonth,"Nov");
        break;
    case 12:
        strcpy(cmonth,"Dec");
        break;
    default:
        break;
    }
}

/* Remove file extension of
input and output */
void rm_extension(char *s, char *s1){
    int i, j = 0;
    char extension[2] = ".";
    int siz = strlen(s);
    int siz1 = strlen(s1);
    
    /* Return new_inp as
    the input file name without file extension */
    for (int i = 0; i < siz; i++) {
        if (strstr(&s[i],extension) == &s[i])
            break;
        else
            new_inp[j++] = s[i];
        
    }
    new_inp[j] = '\0';
    j = 0;
    
    /* Return new_outp as the name of
    the output file without file extension */
    for (int i = 0; i < siz1; i++) {
        if(strstr(&s1[i],extension) == &s1[i])
            break;
        else
            new_outp[j++] = s1[i];
        
    }
}

/* Rename log file of -c flag */
void rename_log(char **s){
    
    char old_name[] = "data.log";
    
    /* Variables store values in the char type */
    char cyear[10], cmonth[10], cday[10], 
    chours[10], cminutes[10], cseconds[10];

    /* Convert int to char */
    itoa(nyear, cyear, 10);
    itoa(nmonth, cmonth, 10);
    itoa(nday, cday, 10);
    itoa(nhours, chours, 10);
    itoa(nminutes, cminutes, 10);
    itoa(nseconds, cseconds, 10);

    /* Remove extension of 
    the input and output name */
    rm_extension(s[1], s[2]);

    /* Combine components of 
    the log file name */
    strcat(new_inp, "_");
    strcat(new_inp, new_outp);
    strcat(new_inp, "_");
    strcat(new_inp, cyear);
    if (nmonth < 10)
        strcat(new_inp, "0");
    strcat(new_inp, cmonth);
    if (nday < 10)
        strcat(new_inp, "0");
    strcat(new_inp, cday);
    strcat(new_inp, "_");
    if (nhours < 10)
        strcat(new_inp, "0");
    strcat(new_inp, chours);
    if (nminutes < 10)
        strcat(new_inp, "0");
    strcat(new_inp, cminutes);
    if (nseconds < 10)
        strcat(new_inp, "0");
    strcat(new_inp, cseconds);
    strcat(new_inp, ".log");

    /* Change the log file name */
    rename(old_name, new_inp);
}

void logfile (char **s) {
    if (logop == 1) {
        fstream myFile;
    
        /* The initial log file of -c flag */
        myFile.open("data.log", ios::out);
        if (myFile.is_open()) {
            myFile << "Hihi" << endl;
        }
        myFile.close();

        current_time();
        /* Rename data.log file */
        rename_log(s);
    }

}

/* Function to print the data to the output file */
void printout(Data arr[], long int size, char **s) {
    const char *outp;
    
    fstream myFile;
    string temp;

    Binary hex[size];

    outp = s[2];
    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile << "id,time,temperature,humidity" << "\n";
        /* Print decrypted data to the output file. */
        for (int count = 0; count < size; count++) {
            hex[count].hid = decToHexa(arr[count].id);
            hex[count].htime = decToHexa(arr[count].date);
            hex[count].hhu = decToHexa(arr[count].hum);
            
            temp = detobi(arr[count].tem);
            hex[count].htem = ietohexa(temp);
            packetl += 4;
            hex[count].hpac = decToHexa(packetl);
            myFile << "00" << " ";
            myFile << hex[count].hpac;
            myFile << hex[count].hid;
            myFile << hex[count].htime;
            myFile << hex[count].htem;
            myFile << hex[count].hhu;
            myFile << "ff";
            myFile << "\n";
            cout << packetl << endl;
            packetl = 0;
        }
    }
    myFile.close();

    logfile(s);
}

void dtob(int n, char **s) {
    const char *inp, *outp;
    
    inp = s[1]; 
    outp = s[2];

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

        // cout << shum << endl;

        // if (shum == "")
        //     cout << "hihi"<<endl;

        if (fline == 1) {
            // cout << shum << "\n";

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
    printout(sen, lline, s);
    
}

/* function to perform s_command */
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
            dtob(n, s);
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