#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>

//High intensty text
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"
#define UMAG "\e[4;35m"
#define reset "\e[0m"

char date[100];
char emit[100];
char name[50];
int numOrders;
int appOpt;
int resOpt;
int foodOpt;
int foodFreq[6] = {0};
char rcptNo[40];

int hours;
int  minutes;
int seconds;
int day;
int month;
int year;

struct order
    {
        char app[10];
        char hotel[10];
        char food[20];
    };


struct order ord;
struct order code;

struct order food1;
struct order food2;
struct order food3;
struct order food4;
struct order food5;

void welcomeText();
void appMenu();
void hotelMenu();
void foodMenu();
int priceCalc(int foodFreq[6]);
void generateApp_code(char app[10], char code[10]);
void generateHotel_code(char opt[10], char code[10]);
void generateReceipt_code();
void printOrdersum();
void upper(char str[100]);
int generateRand(int seedVal);
void generateReciept();


int main(int argc, char const *argv[])
{

    strcpy(food1.food, "UGALI & VEG");
    strcpy(food2.food, "EGG CURRY");
    strcpy(food3.food, "BEEF BURGER");
    strcpy(food4.food, "VEGAN BURGER");
    strcpy(food5.food, "CHIPS N' CHICKEN");

    time_t now;
    time(&now);

    struct tm *local = localtime(&now);

    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after the minute (0-59)

    day = local->tm_mday;           // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900

    sprintf(date, "%d/%d/%d", day, month, year);
    sprintf(emit, "%d:%d:%d", hours, minutes, seconds);

    welcomeText();
    appMenu();
    hotelMenu();
    foodMenu();

    generateApp_code(ord.app, code.app);
    generateHotel_code(ord.hotel, code.hotel);

    printf("\n\t\t\t%sORDER SUMMARY%s\n\n", UMAG, reset);
    printOrdersum();
    priceCalc(foodFreq);
    printf("\n\t\tTHE TOTAL WILL BE.... %sKES %d /=%s\n\n", HGRN, priceCalc(foodFreq), reset);
    generateReceipt_code();
    generateReciept();


    return 0;
}

void welcomeText()
{
    setlocale(LC_ALL, "en_US.utf8");
    const wchar_t food_emoji = 0x1F60B;
    const wchar_t cool_emoji = 0x1F60E;
    const wchar_t smiley_emoji = 0x1F601;


    printf("%s\t\t  __                _                  _             _\n\t\t / _|              | |                | |           | |\n\t\t| |_ ___   ___   __| |   ___ ___ _ __ | |_ _ __ __ _| |\n\t\t|  _/ _ \\ / _ \\ / _` |  / __/ _ \\ '_ \\| __| '__/ _` | |\n\t\t| || (_) | (_) | (_| | | (_|  __/ | | | |_| | | (_| | |\n\t\t|_| \\___/ \\___/ \\__,_|  \\___\\___|_| |_|\\__|_|  \\__,_|_|\n%s", HWHT, reset);
    printf("\t\t\t   %sVersion 1.0 March 2020 Update%s\n\n", HRED, reset);
    printf("\t\t\t\t%s%lc WELCOME TO OUR FOOD APP %lc%s \t\t\n\n", HBLU, cool_emoji, food_emoji, reset);

    printf("%sWhat is your name ? %lc%s >>> ", HGRN, smiley_emoji, reset);

    scanf("%[^\n]", name);
    upper(name);

    printf("\n\n%sHEY... %s%s %lc %sWELCOME TO OUR FOOD APP%s\n\n", HCYN, reset, name, smiley_emoji, HCYN, reset);
}

void appMenu()
{
    setlocale(LC_ALL, "en_US.utf8");
    const wchar_t palm_emoji = 0x1F334;
    const wchar_t phone_emoji = 0x1F4F2;

    printf("%sPLEASE SELECT AN APP TO CONTINUE... %lc %lc%s\n\n", HCYN, phone_emoji, palm_emoji, reset);
    printf("\t1. JUMIA FOODS\n\n\t2. UBER EATS\n\n\t3. GLOVO\n\n");
    printf("%s%s%s >>> ", HGRN, name, reset);
    scanf("%d", &appOpt);

    switch(appOpt)
    {
        case 1:
            strcpy(ord.app, "JM");
            break;

        case 2:
            strcpy(ord.app, "UB");
            break;

        case 3:
            strcpy(ord.app, "GL");
            break;

        default:
            printf("\n%sINVALID CHOICE !!%s\n\n", HRED, reset);
            appMenu();

    }
}

void hotelMenu()
{
    setlocale(LC_ALL, "en_US.utf8");
    const wchar_t tn_emoji = 0x1F44C;
    const wchar_t lc_emoji = 0x1F4CD;
    const wchar_t res_emoji = 0x1F3EA;

    printf("\n%sGREAT %lc NOW PLEASE SELECT THE RESTURANT YOU'D LIKE TO PLACE YOUR ORDER...%lc %lc %s\n\n", HCYN, tn_emoji, lc_emoji, res_emoji, reset);
    printf("\t1. KFC\n\n\t2. SIERRA\n\n\t3. BURGER KING\n\n");
    printf("%s%s%s >>> ", HGRN, name, reset);
    scanf("%d", &resOpt);

    switch(resOpt)
    {

        case 1:
            strcpy(ord.hotel, "KF");
            break;

        case 2:
            strcpy(ord.hotel, "SR");
            break;

        case 3:
            strcpy(ord.hotel, "BK");
            break;

        default:
            printf("\n%sINVALID CHOICE !!%s\n\n", HRED, reset);
            hotelMenu();

    }
}

void foodMenu()
{
    setlocale(LC_ALL, "en_US.utf8");
    const wchar_t ug_emoji = 0x1F371;
    const wchar_t ec_emoji = 0x1F372;
    const wchar_t bg_emoji = 0x1F354;
    const wchar_t c_emoji = 0x1F35F;
    const wchar_t ch_emoji = 0x1F357;
    const wchar_t vg_emoji = 0x1F343;
    const wchar_t clap_emoji = 0x1F44F;
    const wchar_t hrmit_emoji = 0x1F438;
    const wchar_t foodmenu_emoji = 0x1F4DC;
    const wchar_t monkey_emoji = 0x1F435;



    printf("\n%sI KNOW YOU ARE HUNGRY BUT YOU ARE ALMOST THERE...%lc%s\n\n", HCYN, clap_emoji, reset);
    printf("%sNOW WHAT WOULD YOU LIKE TO EAT...? %lc%s\n\n", HCYN, hrmit_emoji, reset);
    printf("\t\t\t %sFOOD MENU %lc%s\n\n", UMAG, foodmenu_emoji, reset);

    printf("\t1.%s %lc     \t\t =/50\n\n\t2.%s %lc     \t\t =/15\n\n\t3.%s %lc     \t\t =/100\n\n\t4.%s %lc%lc     \t =/120\n\n\t5.%s %lc%lc     \t =/150\n\n", food1.food, ug_emoji, food2.food, ec_emoji, food3.food, bg_emoji, food4.food, bg_emoji, vg_emoji, food5.food, c_emoji, ch_emoji);
    printf("%sNOW HOW MANY ORDERS WOULD YOU LIKE TO PLACE...? %lc%s\n\n", HCYN, hrmit_emoji, reset);
    printf("%s%s%s >>> ", HGRN, name, reset);
    scanf("%d", &numOrders);
    printf("\n");

    int food[numOrders];

    for(int i = 0; i < numOrders; i++)
    {
        printf("%lc Enter order #%d >>> ", monkey_emoji, i + 1);
        scanf("%d", &food[i]);

        switch(food[i])
        {
            case 1:
                ++foodFreq[food[i]];
                break;

            case 2:
                ++foodFreq[food[i]];
                break;

            case 3:
                ++foodFreq[food[i]];
                break;

            case 4:
                ++foodFreq[food[i]];
                break;

            case 5:
                ++foodFreq[food[i]];
                break;

            default:
                printf("\n%sINVALID CHOICE !!%s\n\n", HRED, reset);
                foodMenu();
        }
    }
}

void generateApp_code(char opt[10], char code[10])
{
    char randCode_str[100];
    strcpy(code, opt);
}

void generateHotel_code(char opt[10], char code[10])
{

    char randCode_str[100];
    strcpy(code, opt);
}

int priceCalc(int foodFreq[6])
{
    int price;
    int cost = 1;
    int total = 0;

    for(int i = 1; i < 6; i++)
    {
        switch(i)
        {
            case 1:
                price = 50;
                cost = price * foodFreq[i];
                break;
            case 2:
                price = 15;
                cost = price * foodFreq[i];
                break;
            case 3:
                price = 100;
                cost = price * foodFreq[i];
                break;
            case 4:
                price = 120;
                cost = price * foodFreq[i];
                break;
            case 5:
                price = 150;
                cost = price * foodFreq[i];
                break;
        }

        total += cost;
    }
    return total;
}

void printOrdersum()
{

    for(int i = 1; i < 6; i++)
    {
        if(foodFreq[i] != 0)
        {
            switch(i)
            {
                case 1:
                    printf("\t\t%d. %s  \tx%d\n", i, food1.food, foodFreq[i]);
                    break;
                case 2:
                    printf("\t\t%d. %s  \t\tx%d\n", i, food2.food, foodFreq[i]);
                    break;
                case 3:
                    printf("\t\t%d. %s  \tx%d\n", i, food3.food, foodFreq[i]);
                    break;
                case 4:
                    printf("\t\t%d. %s  \tx%d\n", i, food4.food, foodFreq[i]);
                    break;
                case 5:
                    printf("\t\t%d. %s  \tx%d\n", i, food5.food, foodFreq[i]);
                    break;

            }
        }
    }
}

void upper(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i]>='a' && str[i]<='z')
        {
           str[i] -= 32;  //s[i] = s[i] - 32
        }

        i++;
    }
}

void generateReciept()
{
    setlocale(LC_ALL, "en_US.utf8");
    const wchar_t wait_emoji = 0x231B;

    char reply[2];

    printf("\n%sDO YOU WISH TO PROCEED TO CHECKOUT...?%s (Y/N) >>> ", HCYN, reset);
    scanf("%s", reply);

    upper(reply);

    switch(reply[0])
    {
        case 'Y':
            printf("\n%sTHANK YOU...%s %s %sYOUR ORDER IS NOW BEING PROCESSED... %lc%s\n", HCYN, reset, name, HCYN, wait_emoji, reset);
            printf("%sHERE IS YOUR RECEIPT%s\n\n", HCYN, reset);
            printf("\t\t\t %sRECIEPT%s \n\n", UMAG, reset);
            printf("\t\tNAME      :\t %s \n", name);
            printf("\t\tRECIEPT NO:\t %s%s%s \n", HYEL, rcptNo, reset);
            printf("\t\tDATE      :\t %s \n", date);
            printf("\t\tTIME      :\t %s \n\n", emit);
            printf("\t\tITEMS\n\n");
            printOrdersum();
            printf("\n\t\tTOTAL   =    %sKES %d /=%s\n\n\n", HGRN, priceCalc(foodFreq), reset);
            break;

        case 'N':
            foodMenu();

        default:
            printf("\n%sINVALID ENTRY !!!%s\n\n", HRED, reset);
            generateReciept();
            break;
    }
}

int generateRand(int seedVal)
{
    srand(time(NULL));
    int randCode = rand() % seedVal;

    return randCode;
}

void generateReceipt_code()
{

    char app[5];
    char hotel[5];
    char order[5] = "";
    int randCode_num = generateRand(10000);
    char randCode_str[100];

    char strFreq[5];

    strcpy(app, code.app);
    strcpy(hotel, code.hotel);

    for(int i = 1; i < 6; i++)
    {
        sprintf(strFreq, "%d", foodFreq[i]);
        strcat(order, strFreq);
    }

    sprintf(randCode_str, "%d", randCode_num);//converts our random code to a string

    sprintf(rcptNo, "%s%s%s#%s", app, hotel, order, randCode_str);
}

/*void createFile()
{
    FILE *usrFile;
    FILE *jmFile;
    FILE *glFile;
    FILE *ubFile

    char userName[20];
    char userPass[20];


}*/

