// GLS University, Ahmedabad
// Calender Version 1.0.0
// Bhautik Vgahamshi | B23CSE076
// Vasisht Brambhatt | B23CSE078
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>

#define MAX_EVENTS 100
#define MAX_EVENT_TITLE_LENGTH 50
#define MAX_EVENT_DESC_LENGTH 100
char *months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
int monthDay[] = {31,28,31,30,31,30,31,31,30,31,30,31};

struct Event 
{
    int day;
    int month;
    int year;
    char title[MAX_EVENT_TITLE_LENGTH];
    char description[MAX_EVENT_DESC_LENGTH];
};

struct Event events[MAX_EVENTS];
int eventCount = 0;

// Function to add an event
void addEvent(int year, int month, int day, char title[], char description[])
{
    if (eventCount < MAX_EVENTS)
    {
    	
        events[eventCount].year = year;
        events[eventCount].month = month;
        events[eventCount].day = day;
        strcpy(events[eventCount].title, title);
        strcpy(events[eventCount].description, description);
        eventCount++;
        printf("------------------------------------------------\n");
		printf("| \x1b[32m[+]\x1b[0m Event added successfully on %d - %d - %d |\n", day, month, year);
        printf("------------------------------------------------\n");
        while(getchar() !='\n');
    }
    else
    {
    	printf("-------------------------------------------------\n");
        printf("| \x1b[31m[-]\x1b[0m Event limit reached, Cannot add more events. |\n");
        printf("-------------------------------------------------\n");
	}
}

// Function to view events in a specific month
void viewEventsInMonth(int month, int year)
{
    int i;
    printf("------------------\n");
    if(eventCount>0)
    {
    	printf("\x1b[32m[+]\x1b[0m Events in %d - %d:\n", month, year);
    	for(i=0;i<eventCount;i++)
    	{
        	if(events[i].month==month && events[i].year==year)
            	printf("[*] %d/%d/%d: %s - %s\n", events[i].day, events[i].month, events[i].year,events[i].title, events[i].description);
    	}
		printf("------------------\n");
	}
	else if(eventCount==0)
	{
	 	printf("----------------------------\n");
		printf("| \x1b[33m[-]\x1b[0m Event(s) not found.  |\n");
		printf("----------------------------\n");	
	}
	
	while(getchar() != '\n');
}

// Function to delete an event
void deleteEvent(int year, int month, int day)
{
    int index = -1,i;
    for (i=0;i<eventCount;i++)
    {
        if (events[i].day==day && events[i].month==month && events[i].year==year)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        for (i=index;i<eventCount-1;i++)
        {
            events[i]=events[i+1];
        }
        eventCount--;
        printf("\x1b[32m[+]\x1b[0m Event on %d/%d/%d deleted.\n", day, month, year);
    }
    else
    {
    	printf("----------------------------\n");
		printf("| \x1b[33m[-]\x1b[0m Event not found.     |\n");
		printf("----------------------------\n");
	}
    
	while(getchar()!='\n');
}

int get_1st_weekday(int year)
{
    int d;
    d = (((year-1)*365)+((year-1)/4)-((year-1)/100)+((year)/400)+1)%7;
    return d;
}

// Function to view specific month of a year
void printMonth(int year, int month)
{
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[2] = 29;
    
    printf("\n\n---------------%d, %d-------------------\n", month, year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int dayOfWeek = (year+(year/4)-(year/100)+(year/400)+((13*month+8)/5)+1)%7;
    int i,day;
    
    for(i=0;i<dayOfWeek;i++) 
        printf("     ");
    
    for (day = 1; day <= daysInMonth[month]; day++) 
    {
        if ((day + dayOfWeek) % 7 == 1)
            printf("\033[1;31m%5d\033[0m", day);
        else
            printf("%5d", day);
        
        if ((day + dayOfWeek)%7==0 || day==daysInMonth[month]) 
		{
            printf("\n");
        }
    }
    while(getchar()!='\n');
}


// Function to view calender of a year
void display_year(int year)
{
	int month,day,daysInMonth,weekDay=0,startingDay;
		if ((year%4==0 && year%100!=0) || year%400==0)
        	monthDay[1] = 29;

    	startingDay=get_1st_weekday(year);

    	for(month=0;month<12;month++)
    	{
        	daysInMonth = monthDay[month];
        	printf("\n\n---------------%s, %d-------------------\n", months[month], year);
        	printf("\n  Sun  Mon  Tue  Wed  Thurs  Fri  Sat\n");

        	for(weekDay=0;weekDay<startingDay;weekDay++)
            	printf("     ");

        	for(day=1;day<=daysInMonth;day++)
        	{
        		if (weekDay == 0)
                	printf("\033[1;31m%5d\033[0m", day);
				else
					printf("%5d",day);

            	if(++weekDay>6)
            	{
            		
                	printf("\n");
                	weekDay=0;
            	}
            	startingDay=weekDay;
        	}
    	}
    while(getchar()!='\n');
}

// Function to validate input
int valid(int number, int min, int max)
{
	while(1)
	{
        if(scanf("%d", &number) != 1)
		{
            while(getchar() != '\n');
				printf("\x1b[31m[!]\x1b[0m Invalid input, enter a valid number: ");
        } 
		else if(number<min || number>max) 
            printf("\x1b[31m[!]\x1b[0m Invalid input, enter a valid number: ");
		else
			return number;
    }
}

// Function to view holidays in a year
void holidays(int year) 
{
	printf("\n\x1b[32m[+]\x1b[0m Holidays in %d :\n", year);
	int i;
	char holidaysName[7][20] = {"Uttarayan", "Republic Day","Ambedkar Jayanti", "Eid al-Fitr", "Independence Day", "Gandhi Jayanti", "Christmas Day"};
	char holidaysDate[7][20] = {"14th January", "26th January", "14th April", "22nd April", "15th August", "2nd October", "25th December"};
	
	for(i=0;i<7;i++)
	{
		printf("[*] %s - %s, %d\n",holidaysDate[i], holidaysName[i], year);
	}
	while(getchar()!='\n');
}

// Function main
int main()
{
	int mainChoice, subChoice1, subChoice2;
	int return_val;
	
	int year, month, day;
	char title[MAX_EVENT_TITLE_LENGTH];
    char description[MAX_EVENT_DESC_LENGTH];
    
    time_t t;
    time(&t);
    char *curtime = ctime(&t);
    
	while(return_val!=6)
	{
		printf("\n");
		printf("          =========================\n");
		printf("     - W E L C O M E to C A L E N D E R -\n");
		printf("          =========================\n");
		printf("   [*] TODAY : %s", curtime);
		printf("==============================\n");
		printf("1. View Calender\n2. Add new Event\n3. Display Event\n4. Delete event\n5. View Public Holidays\n6. Exit\n");
		printf("==============================\n");
		printf("Enter your choice : ");
		return_val = valid(mainChoice,1,6);
		switch(return_val)
		{
			case 1:
			{
				while(return_val!=3)
				{
					system("cls");
					printf("----------------------\n");
					printf("1. View whole year\n2. View a particular month of a year\n3. Go back\n");
					printf("----------------------\n");
					printf("Enter choice : ");
					return_val = valid(subChoice1, 1, 3);
					switch(return_val)
					{
						case 1:
							printf("Enter year : ");
							return_val = valid(year,1000,9999);
							display_year(return_val);
							printf("\n----------------------------------");
							printf("\n[*] Press any key to continue...");
							while(getchar() != '\n');
							break;
						
						case 2:
							printf("Enter year : ");
							year = valid(year,1000,9999);
							printf("Enter month : ");
							month = valid(month,1,12);
							printMonth(year, month);
							printf("\n----------------------------------");
							printf("\n[*] Press any key to continue...");
							while(getchar() != '\n');
							break;
					}
				}
				system("cls");
				break;
			}
			case 2:
				system("cls");
				printf("======================\n");
				printf("Enter year: ");
				year = valid(year,1000,9999);
                printf("Enter month: ");
                month = valid(month,1,12);
                while (1)
    			{
        			printf("Enter day: ");
        			day = valid(day, 1, month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : monthDay[month - 1]);
        			if (!(month == 2 && day <= 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) || (day <= monthDay[month - 1])))
        			{
            			printf("\x1b[31m[!]\x1b[0m Invalid day for the selected month. Please enter a valid day.\n");
            			continue;
        			}
        			break;
    			}	
                printf("Enter event title: ");
                scanf(" %[^\n]s",&title);
                printf("Enter event description: ");
                scanf(" %[^\n]s",&description);
                addEvent(year, month, day, title, description);
                printf("\n----------------------------------");
                printf("\n[*] Press any key to continue...");
                while(getchar() != '\n');
                system("cls");
				break;
			case 3:
				system("cls");
				printf("======================\n");
				printf("Enter month: ");
                month = valid(month,1,12);
                printf("Enter year: ");
                year = valid(year,1000,9999);
                viewEventsInMonth(month, year);
                printf("\n----------------------------------");
                printf("\n[*] Press any key to continue...");
                while(getchar()!='\n');
                system("cls");
                break;
			case 4:
				system("cls");
				printf("======================\n");
				printf("Enter year : ");
				year = valid(year,1000,9999);
                printf("Enter month : ");
                month = valid(month,1,12);
				while(1)
				{
					printf("Enter day: ");
        			day = valid(day, 1, month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : monthDay[month - 1]);
        			if (!(month == 2 && day <= 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) || (day <= monthDay[month - 1])))
        			{
            			printf("\x1b[31m[!]\x1b[0m Invalid day for the selected month. Please enter a valid day.\n");
            			continue;
        			}
        			break;
				}
                deleteEvent(year, month, day);
                printf("\n----------------------------------");
                printf("\n[*] Press any key to continue...");
                while(getchar()!='\n');
                system("cls");
				break;
			case 5:
				system("cls");
				printf("======================\n");
				printf("Enter year : ");
				year = valid(year,1000,9999);
				holidays(year);
				printf("\n----------------------------------");
				printf("\n[*] Press any key to continue...");
				while(getchar()!='\n');
				system("cls");
				break;
				
			case 6:
				printf("==============\n");
				printf("| Exiting... |\n");
				printf("==============\n");
				break;
		}
	}
	getch();
	return 0;
}
