// Jonah Belback
// Riley Adams
// Ethan Poe
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int choice(void);
int timeconv(int, int, char, int);
void menu_create(void);
void food_selection(char[][100], int, int[], int[], double[]); //WIP
int chartimeconv(char[7]);

//users can either change the menu avaliable, look at the menu, and order from the menu
//the menu is a text file that cna be rewritten and relooked at over and over


//if you don't get the menu, you havent download/loaded a menu.txt file yet
//it will auto make you make the menu if it doesn't exist yet

int main()
{
//reading premade menu doc from cafeteria provider (can be edited on here too)
	
	//c doesn't allow mult returns so we did it in main
	FILE *file_var;
	file_var = fopen("menu.txt","r");
	
	//if file is blank (never set up)
	//then it will set it as blank
	//so it can be set up later
	int empt_check;
	if (file_var == NULL)
	{
		file_var = fopen("menu.txt","w");
		fprintf(file_var, " ");
		fclose(file_var);
		file_var = fopen("menu.txt","r");
		empt_check = 1;
	}
	
	//setting up vars to read
	int i=0, numlines=0;
	char name[10000][100];
	double price[10000];
	//time
	int time1[10000],time2[10000];
	char time3[10000][2];
	int time4[10000],time5[10000];
	char time6[10000][2];
	int check_eof;
	
	//reading
	while(1==1)
	{
		check_eof = fscanf(file_var,"%s %lf %d:%d%s %d:%d%s",&name[i][0], &price[i], &time1[i], &time2[i], &time3[i][0], &time4[i], &time5[i], &time6[i][0]);
		if (check_eof == EOF)
		{break;}
		i++;
		numlines++;
	}
	
	//conv read times to army time for easy condition statements
	
	//ex: (8:00am ==> 800)
	//that 8:00am is read up as mult variables:
	//(8 is a int, 00 is a seperate int, the first letter(a/p) is a char)
	
	int timef1[10000], timef2[10000];
	char tempchar;
	
	for (i=0;i<numlines;i++)
	{tempchar = time3[i][0];
	 timef1[i] = timeconv(time1[i], time2[i], tempchar, numlines);}
	
	for (i=0;i<numlines;i++)
	{tempchar = time6[i][0];
	 timef2[i] = timeconv(time4[i], time5[i], tempchar, numlines);}

	//timef1 is an array conesponding with the items name & price telling when that item is put out (first avaliable)
	//timef2 is same but when that item is removed (no longer avaliable)

/////////////////////////////////////////////////////////////

//Feature choice variable
	int feature_choice;
	
	//checking if the menu.txt was blank
	//forces you to skip the menu and fill it out if thats the case
	if (empt_check != 1)
	{ feature_choice = choice();}
	else
	{
		feature_choice = 2;
		printf("ERROR: 'menu.txt' NOT FOUND\n");
		printf("PLEASE FILL OUT MENU");
	}

	if (feature_choice == 1)
	{
	//view file
	printf("\nYou have chosen to look at the current menu file.\n");
	printf("\nNAME\t\t\tPRICE\tSTART\tEND\n");
	printf("///////////////////////////////////////////////////\n");
		for(i=0;i<numlines;i++)
		{
			if (name[i][7] == '\0')
			{ printf("%s\t\t\t%.2lf\t%d\t%d\n",&name[i][0],price[i],timef1[i],timef2[i]); }
			else
			{ printf("%s\t\t%.2lf\t%d\t%d\n",&name[i][0],price[i],timef1[i],timef2[i]); }
		}
	}
	
	else if (feature_choice == 2)
	//overwrite file
	{
		printf("\nYou have chosen to edit the menu file.\n");
		menu_create();
	}

	else if (feature_choice == 3)
	//order
	{
		printf("\nYou have chosen to select a meal.\n");
		food_selection(name,numlines,timef1,timef2,price);
	}

	else
	//ERROR notification
	//I thought it was funny at least
	{ printf("\nYou have chosen death.\n"); }
	
	
//end
	fclose(file_var);
}

/////////////////////////////////////////////////////////////

int choice(void)
{
	int feature_choice = 6; //rand val above 3 to make it work (no negs)
	
	do
	{
		printf("Input 1 to view the menu file\n");
		printf("Input 2 to edit the menu file\n");
		printf("Input 3 for food selection\n");
		printf("ENTER: ");
		scanf(" %d", &feature_choice);
		printf("\n");
	}while (feature_choice <= 1 && feature_choice >= 3); //i swear these signs are the opposite that theyre supposed to be but it works???
	
	return feature_choice;
}
/////////////////////////////////////////////////////////////
int timeconv(int time1, int time2, char tempchar, int numlines)
{
//converts something like "8:am" to army time: 800
//easy to use a var
	int timef;
	
	if(tempchar == 'a' )
	{ timef = (time1*100)+time2; }
	 
	else if(tempchar == 'p')
	{ timef = 1200 + (time1*100)+time2; }
	 
	else
	{ printf("\nERROR"); }
		
	//OVER RIDE: 12am 12pm thing
	if(tempchar == 'p' && time1 == 12)
	{ timef = 1200; }
	if(tempchar == 'a' && time1 == 12)
	{ timef = 0; }
	
	return timef;
}
/////////////////////////////////////////////////////////////
void menu_create(void)
{
	FILE *file_var;
	file_var = fopen("menu.txt","w");
	int i=0;
	char fname[100],time1[7],time2[7],repeat;
	double price;


do
{
//food name
	printf("Enter food item: ");
	scanf(" %[^\n]", fname);  //scanf doesn't like recording spaces when inputed but I found this solution online
	
	//makes spaces into underscores for error reasons when reading
	while(i<99)
	{
		if(fname[i] == ' ')
		{ fname[i] = '_'; }
		i++;
	}
	
	//print to file
	fprintf(file_var, fname);
	
//price
	printf("Enter price (#.## format): ");
	scanf(" %lf", &price);
	fprintf(file_var,"\t%.2lf", price);
	
//available time
	printf("Enter time when it is put out (#:##(a/p)m format): ");
	scanf(" %s", time1);
	fprintf(file_var, "\t");
	fprintf(file_var, time1);

//closed off time
	printf("Enter time when it is removed (#:##(a/p)m format): ");
	scanf(" %s", time2);
	fprintf(file_var, "\t");
	fprintf(file_var, time2);
	
//next line
	fprintf(file_var,"\n");

//repeat
	printf("\n\nWould you like to add another item (Y/N)\?");
	do
	{
		printf("\nEnter: ");
		scanf(" %c", &repeat);
	}while(repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N');
	
	if(repeat == 'y' || repeat == 'Y')
	{ printf("\n"); }
	
	else if(repeat == 'n' || repeat == 'N')
	{ printf("\nwow okay, fine then bye"); }
	
	else
	{ printf("\nERROR: INVALID INPUT"); }
	
}while(repeat == 'y' || repeat == 'Y');

//end
	fclose(file_var);
}
/////////////////////////////////////////////////////////////
void food_selection(char name[][100], int numlines, int timef1[], int timef2[], double price[])
{
	//needs: (name[][]) (numlines) (timef1) (timef2) (price)
	
	//ask for time you wanna schedule
	char showtime[7];
	int atime;
	printf("When are you ordering? (#:##(a/p)m format): ");
	scanf(" %s", &showtime[0]);
	
//convert showtime to army time (conditions purposes)
//too much of a difference from previous func that I just made it its own
	atime = chartimeconv(showtime);
	//printf("%d\n",atime);

//display items and pick out

	//int exist_check is set up to see if there was anything AT ALL available at the time entered
	int i=0, it=0, exist_check=0;
	int item=0;
	double itemprice=0;
	//new arrays based on avaliable items
	//can't easily remove items from arrays sooooo
	double price_n[10000];
	
	printf("\nHere are your following options available:\n");
	for (i=0;i<numlines;i++)
	{
		if(timef1[i] <= atime && timef2[i] >= atime)
		{
			printf("Enter (%d) for %s\n",it+1,&name[i][0]);
			price_n[it] = price[i];
			//printf("%.2lf",price[i]);
			//printf("\t%.2lf\n",price_n[it]);
			it++;
			//if even one item shows up it'll make it = 1
			exist_check = 1;
		}
		else {}
		//printf("bruh");
	}
	
if (exist_check != 1)
{
	printf("\n\nThere is nothing available.\n");
	printf("Enter another time or check back later.");
}
else
{
	do
	{
		printf("Enter: ");
		scanf("%d", &item);
		item = item - 1;
	}while(item < 0);
	itemprice = itemprice + price_n[item];
	
	
	while(1==1)
	{
		printf("Enter other item (exit with zero): ");
		scanf("%d", &item);
		if(item == 0)
		{ break; }
		else
		{
			item = item - 1;
			itemprice = itemprice + price_n[item];
		}
	}

	//end
	printf("\nYour total is: %.2lf", itemprice);
}

}
/////////////////////////////////////////////////////////////
int chartimeconv(char showtime[7])
{
//convert showtime to army time (conditions purposes)
//too much of a difference from conv chars then with the previous func that I just made it its own

//rather then make the army time from a collection of variables (int, int, then char),
//it makes an army time from just one char ('8:00am' ==> 800)
	int exptime;
	if(showtime[0] == '1')
	{
		exptime = (10 + (int)showtime[1] - 48)*100; //need to subtract 48 inorder to make conversion from char to int (learned this from testing)
		exptime = exptime + ( (int)showtime[3] - 48 )*10;
		exptime = exptime + ( (int)showtime[4] - 48 );
		
		 
		if(showtime[5] == 'p' && showtime[1] != '2' )
		{ exptime = exptime + 1200; }
		
		//OVER RIDE: 12am 12pm thing
		if(showtime[5] == 'a' && showtime[1] == '2')
		{exptime = 0;}
	}
	else
	{
		exptime = ( (int)showtime[0] - 48)*100;
		exptime = exptime + ( (int)showtime[2] - 48)*10;
		exptime = exptime + ( (int)showtime[3] - 48 );
		
		if(showtime[4] == 'a' )
		{ }
		 
		else if(showtime[4] == 'p')
		{ exptime = exptime + 1200; }
	}
//	printf("%d\n",exptime);
	return exptime;
}
