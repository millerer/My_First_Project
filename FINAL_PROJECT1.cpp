/************************************************
Author: Eric Miller
Date Created: 06/08/2014
Filename: FINAL PROJECT.cpp

Overview:
This is the final project for CS 161. It is a simple text adventure game
based around escaping an old house. The player can perform basic commands
like 'use', 'talk', or 'eat', as well as travel in the 4 cardinal directions.

The player moves from room to room collecting and interacting with objects.
If objects are collected and used in a certain order, the game can be
completed.

This program is primarily based around class objects for the player and
each room they visit.


Output:
Text based interactive fiction.
*************************************************/

#include<iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include  <stdlib.h>
using namespace std;


string rand_food [2][2] //Requirement # 17//
{ {"Yogurt", "Panninni"},
  {"Airplane Peanuts", "Fruit cup"} };

/************************************************

!ACTIONS!

The below universal string array contains
all of the actions that are able to be put into
the program as well as key items

*************************************************/

string key_items [] {"KEY", "FORK", "LANTERN", "TANKARD", "RABBIT", "SOUP", "GUN", "MUSKET"}; //meets requirement #15//
//KEY ITEMS THAT ARE STORED IN THE PLAYER INVENTORY//

string valid_words [] {"NORTH", "N", "SOUTH", "S", "EAST", "E", "WEST", "W", "USE", "LOOK", "EAT", "TASTE", "ATTACK","HIT","OPEN", "TAKE", "PICKUP","KILL", "BREAK", "INSULT", "HARASS", "EXAMINE","TALK","SPEAK", "YELL", "PUNCH", "PICK", "READ"}; //list of valid commands by user//
//27 word string array to hold valid actions//

/************************************************

!TRAVELING!

The below universal int variable is used to flag
which room the player is in. The main () function
reads this number, then activates the room located
at that number to simulate travel.

Depending on user input for the 'room' (class function)
they find themselves in (such as NORTH, SOUTH, etc)
this variable will be updated.

*************************************************/

int room_num; //Global variable that holds value for room identifier. this can be accessed by any function in the program. Requirement #12//

/************************************************

!BOOL FUNCTIONS!

The below are bool functions used to compare
user input to the list of accepted actions,
as well as the list of accepted objects to
interact with. The latter list of objects is
based on local member variable values, while
the list of actions is based on the universal
string array "valid_words"

*************************************************/
bool validate_com (string &action, string act_list []);
//validates command by user//
//Parameter One is the input for an action//
//Parameter two is the list of actions//

bool validate_object (string &object, string obj_list[], int arr);
//validate object input by user//
//Parameter one is the object input by the user//
//Parameter two is the list of availible objects //
//Parameter three is the object array size//
/************************************************

!KEY ITEM FUNCTIONS!

The below void function and bool functions checks for special inventory
'Key Item' objects and outputs their actions accordingly
when called (if they player has picked them up).

*************************************************/

bool check_keyItems (string &object, string obj_list[], int arr); //Demonstrates passing requirement #103//
//validate object input by user//
//Parameter one is the object input by the user//
//Parameter two is the list of availible objects //
//Parameter three is the object array size//

void use_keyItems (string action, string item); //defined own function. Requirement # 10. Demonstrates overloading  requirement #14//
//validate object input by user//
//Parameter one is the action input by the user//
//Parameter two is the object being interacted with //

/************************************************

!CLASSES!

The below are class declarations. There are
is a class for the player and werewolf as well as a class
used to contain the experiences of each room.

In a sense, the main() function serves to
connect all of the rooms together so that when one
room object's member function ends, another can start.

This simulates exiting one room and entering another.

A class object is created after each class definition

*************************************************/

class all_items //class that give the player all of the key items. Activated via command line input//
{

    public:

    void avarice ();
    //gives player all of the key items//

    void player_message(int stars);
    //Give out a message via recursion. Star_count is the number of * characters put on screen//

};
all_items cheat;

class main_char //class for the player controlled character.
{

    public:
            void change_name(string player_name);
             //changes player name//
             //Parameter one is the string to be entered as the player name//

            void player_name ();
            //shows player name//

            main_char (int construct);

            void change_health (int damage);
            //changes health//
            // Parameter one is the int value that int health will change by//

            void get_food (string *food_pointer, string rand_food[][2]);
            //Sets the pointer 'food' to a random food in the rand_food array//
            //Parameter one is the pointer *food//
            //Parameter two is the random food generator array//

            string* food_pointer; //for requirement #22//

            string food;

            string action; //actions by the player//

            string object; //thing that the player wants to interact with//

    private:

            string Name;

            int health;
};
main_char player(7); //Global

main_char::main_char(int construct)
{
    health = construct;

}

class werewolf
{

    public:

        werewolf (int basemnt, int bullet, int disctract, int seenit); //constructor//

        void wolf_intro ();

        void victory();

        void defeat ();

        //the three above functions are for text output only//

        void therewolf();

        //initiates the werewolf encounter//

        void use_objects (string action, string item);
        //Gives results of object interaction//
        //Parameter one is the user action//
        //Parameter two is the item being interacted with//


        void use_keyItems (string action, string item, int wolf);
        //Gives results of key object interaction with the werewolf//
        //Parameter one is the user action//
        //Parameter two is the item being interacted with//
        //Parameter three is an extra parameter that allows me to override this function name to meet project requirement # 14//

        int dont_go_in_the_basement; //Sets up extra werewolf encounters in the cellar and kitchen//

       int silver_bullet;  //if I didn't make this public, I would have a syntax error because other outside non-member functions reference this variable. Requirement #8//
       //Equal to '1' if the werewolf has been defeated//

    private:

    string wolf_objects[2];

    int distracted; //Equal to '1' if the rabbit has been used//

    int been_there_done_that; //equal to '1' if the user already encountered the werewolf//


};
werewolf wolfy(0, 0, 0, 0);

werewolf::werewolf(int basemnt, int bullet, int disctract, int seenit)
{
    dont_go_in_the_basement = basemnt;

    silver_bullet = bullet;

    wolf_objects[0] = "WOLF";

    wolf_objects[1] = "WEREWOLF";

    distracted = disctract;

    been_there_done_that = seenit;

}

/************************************************

!ROOMS!

For further notes on rooms.

All contain the following:

-A <look> function that outputs a text description,

-A <goto> function that serves to take in user
input for that room,

-A <set_objects> function that creates a list of
interactive items for the room,

-A <use_obj> function that outputs a response to
 action/room item combinations

*************************************************/

class G_H //class for the great hall room//
{
    public:

    G_H (int arr); //constructor
    void look (); //Gives description of room//

    void goto_great_hall (); //opens the great hall

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    string GH_objects[6]; //interactive items in this room//

    int arr_size;

};
G_H GreatHall (6);

G_H::G_H(int arr)
{
    arr_size = arr;
}

class hall //class for the hallway requirement #21//
{

    public:

    void look (); //Gives description of room//

    void goto_hall (); //opens the great hall

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

};
hall hallway;

class front_door //For the Foyer//
{
    public:

    front_door (int arr); //constructor//

    void look (); //Gives description of room//

    void goto_front_door (); //opens the foyer//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    string front_door_objects[6]; //interactive items in this room//


    int arr_size;


};
front_door foyer(6);

front_door::front_door(int arr)
{
    arr_size = arr;
}

class kitchen //For the Kitchen//
{

    public:

    kitchen (int arr, int broken, int wolf); //constructor//

    void look (); //Gives description of room//

    void goto_kitchen (); //opens kitchen//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    string cook_objects[9]; //interactive items in this room//

    int arr_size;
    int broke; //if the dishes are broken, this is '1'//
    int show_wolf; //if the user has met the kitchen wolf//

};
kitchen cooking(9, 0, 0);

kitchen::kitchen(int arr, int broken, int wolf)
{
    arr_size = arr;
    broke = broken;
    show_wolf = wolf;
}

class basement //For the cellar//
{

    public:

    basement (int arr, int wolf); //constructor//

    void look (); //Gives description of room//

    void goto_basement (); //opens the cellar//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//


    private:

    int arr_size;

    string basement_objects[4]; //interactive items in this room//

    int show_wolf; //if the user has met the cellar wolf//
};

basement cellar(4, 0);

basement::basement(int arr, int wolf)
{
    arr_size = arr;

    show_wolf = wolf;
}

class libr //For the library//
{
    public:

    void look (); //Gives description of room//

    libr(int arr, int combi); //constructor//

    void goto_lib (); //opens the library//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    string lib_objects[12]; //interactive items in this room//

    int arr_size;

    int combine; //for combining musket and fork. '1' means that they have been combined.//
};
libr library(12,0);

libr::libr(int arr, int combi)
{
    arr_size = arr;
    combine = combi;
}

class final_room //for the bedroom//
{
    public:

    final_room (int arr); //constructor//

    void look (); //Gives description of room//

    void goto_bedroom (); //opens the bedroom//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    int arr_size;

    string bedroom_objects[6]; //interactive items in this room//
};

final_room bedroom(6);

final_room::final_room(int arr)
{
    arr_size = arr;
}

class gar_den // for the garden//
{

    public:

    gar_den(int arr, int oily, int squi); //constructor//

    void look (); //Gives description of room//

    void oil_gate (); //changes squeaky status of gate//

    void goto_garden (); //opens the garden//

    void set_objects (string obj[]);
    //sets interactive objects//
    //Parameter one is the list of objects//

    void use_objects (string action, string item);
    //Gives results of object interaction//
    //Parameter one is the user action//
    //Parameter two is the item being interacted with//

    private:

    string garden_objects[5]; //interactive items in this room//

    int arr_size;

    int oil; //if gate was oiled, this is 1//

    int squeaky; //flags '1' if the gate in the garden is squeaky//

};
gar_den garden(5,0,1);

gar_den::gar_den(int arr, int oily, int squi)
{
    arr_size = arr;
    oil = oily;
    squeaky = squi;
}

/************************************************

!INVENTORY!

The player inventory is controlled by a flagging
system ('0' for available, '1' for unavailable)
contained in a struct int array.

Many branching cases refer to this array to see if an
item is flagged as being available or not.

Which items correspond to which index number
is explained in the struct comments//

*************************************************/

struct inventory //holds inventory items. Requirement #20//
{

    int backpack [8];


/************************************************
    Values are either '1' or '0'.

    '0' means the player doesn't have that object.

    index [0]  is key 2
    index [1] is key 1
    item [2] is the silver fork
    item [3] is the lantern
    item [4] is the tankard
    item [5] is the rabbit
    item [6] is the soup
    item [7] is the musket
*************************************************/
    int arr_size;
    //size of the key item array//
};
void setup_inventory ();
//adds value for the inventory member variables//

inventory items;

void intro ();
//Introduction to the game//

void ending();
//The end of the game//

/************************************************

!MAIN FUNCTION!

The main function is based on loop that checks
to see which room the player is tagged as being
in when a room class function ends.

Generally, room functions end themselves when
the player leaves one room to go to another. Depending
on the direction they go, it changes the room tag so
that when main () loops again they will be brought to a new
area.

*************************************************/
int main(int argc, char* argv []) //Obfuscated most of the code outside main. Requirement #11. Command line arguments meet requirement # 19//
{
    player.get_food(player.food_pointer, rand_food);

    setup_inventory();

    if (argc >= 2) //checks for command line arguments//
    {
        string* dynamic_arr;

        dynamic_arr = new string [1]; //Requirement 18//

        dynamic_arr[0] = argv[1];

       // Debugged with the following code line:  cout<< "\n" << dynamic_arr[0] << " IS IS THE VALUE OF THE DYNAMIC ARRAY AT INDEX 0";

        if (dynamic_arr[0] == "CHEAT")

            {
                all_items* class_pointer;

                class_pointer = &cheat; //Requirement 24//

                class_pointer->avarice();

                class_pointer->player_message(7);
            }

        delete [] dynamic_arr;

    }

    intro();

    GreatHall.goto_great_hall();


    while (room_num < 1000) //Each room has a number code. When that code is activated, the current room function the player is in finishes, and they are taken to the room of that number in the below loop//
    {


        if (room_num ==1)

        {
            GreatHall.goto_great_hall(); //Goes to the chapel//
        }

        else if (room_num == 2)

        {
            foyer.goto_front_door(); //Goes to the foyer//
        }
        else if (room_num == 3)

        {
            cooking.goto_kitchen(); //goes to the kitchen//
        }

        else if (room_num == 4)

        {
            hallway.goto_hall(); //Goes to the hall way. Meets requirement # 21//
        }

        else if (room_num == 5)

        {
            cellar.goto_basement(); //goes to the basement//
        }

        else if (room_num == 6)

        {
            library.goto_lib(); //goes to the library//
        }

        else if (room_num == 7)

        {
            bedroom.goto_bedroom(); //goes to the bedroom//
        }

        else if (room_num == 8)

        {
            garden.goto_garden(); //goes to the bedroom//
        }

        else if (room_num ==9)

        {
            wolfy.therewolf(); //player encounters werewolf//
        }


    }

    cout<< "\n\n\n*****************************************" << endl
    << "THE END" << endl
    <<"*****************************************\n\n\n";

    return 0;
}


/************************************************

!FUNCTION DEFINITIONS!

The rest of the code is made up of function definitions.
These mostly are related to the classes declared
at the beginning of the program.

*************************************************/

void setup_inventory()
{

    items.arr_size = 8;

    for (int i = 0; i < 8; i++)
    {
        items.backpack[i] = 0;
    }

}

void main_char::change_name(string player_name)
{
    Name = player_name;
}

void main_char::change_health(int damage)
{
    health = health - damage;

    if (health <= 0)

    {
        wolfy.defeat();
    }
}

void main_char::get_food(string *food_pointer, string rand_food[][2])
{
    srand(time(0));
    int food_indexA;
    int food_indexB;

    food_indexA = rand()% 2 + 1; //random number from 1-2 meets requirement #7//

    food_indexA = food_indexA - 1; //adjusting for index starting at 0//

    food_indexB = rand()% 2 + 1; //random number from 1-2//

    food_indexB = food_indexB - 1; //adjusting for index starting at 0//

   // NOTE: I used the following syntax for debugging and making sure that the random number worked:  cout << "Randomly Generated number is: " << food_index; Requirement #9//

    food_pointer = &rand_food[food_indexA][food_indexB]; //Requirement # 22//

    food = *food_pointer;

    //NOTE: I used the following syntax for debugging and making sure that the pointer to the array worked: cout << food; //
}

void main_char::player_name()
{
    cout<< Name;
}

void intro()
{
    string enter_name; //enter name//

    char temp; //Press to continue//

    cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "Final Project\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n"
            "Greetings and welcome to the text adventure game \"Eric's Final Project\". \nThis is a short interactive adventure where the user types in actions to \ninteract with the game world. \n"
            "\n"
            "Travel is done by typing one of the four cardinal directions (N-S-E-W) and \nactions are taken by typing in an action and then object such as \"TAKE, COIN\". \n"
            "\nYou can also get a description of a room you are in or an item by typing\n\"LOOK\", or \"EXAMINE\" followed by \"ROOM\" or the item name.\n"
            "\nNow that the explanation is out of the way, let's start!\n"
            "\n"
            "First, what is your name?\n"
            "\n";


    getline(cin, enter_name); //Requirement #2//

    player.change_name(enter_name);



    cout<< "\n\n\n"
           "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
            "\n"
            "You awake with a start from a particularly bad dream. \nPresperation drips from your brow, and you can see a full \nmoon's light dimly illuminating the room you lay in.\n"
            "\n"
            "At first you think you are back in your hotel. The cold stone floor you were \njust laying your head on was all to similar the last night's pillow. "
            "\n\nHowever you now realize you are someplace unfamiliar"
            "\n\n"
            "Blinking as your eyes adjust to the darkness, you try and remember what got you here....\n"
            "\n"
            "\n<ENTER ANY KEY TO CONTINUE>\n";
    cin>> temp;

    cin.ignore(10000, '\n');

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

    player.player_name();

    cout <<
            " , that's your name. A name only gets you so far though...\nwho are you exactly, and what do you do? \n"
            "\n"
            "The room blurs in and out of focus as your memory slowly returns.\n"
            "\n"
            "...\n\n"
            "You are a tourist. A tourist who ended up in the back-country of\nRomania of all places.\n"
            "\n"
            "Your tour group's bus started in Athens and was on the way to Prague, but the \ndriver insisted that taking a detour through the North-East Balkans was fastest.\n"
            "\n"
            "Last thing you remember, you were at a truck stop on the outskirts of a \nforeboding forest. You decided to stretch your legs with the other travelers \nas the driver"
            " refueled. \n\nYou were quite hungry, and pulled out the last bite of food from your backpack."
            "\n"
            "\n\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');


    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

    cout<<
            "Unfortunately there was only a long, long since expired " << player.food << " remaining.\n\nBeggars can't be choosers though, so you decided to take your chances and\n take a bite."
            "\n"
            "\nImmediately you regretted your decision...besides it tasting \nlike stale gym socks, the world began to spin into a blur of color as your\nstomach roared in protest.\n\nPanicking in a food poisened daze,you ran into the forest and remember no more."
            "\n"
            "\nNow all you know is that you have to get out of here...you have to get \nsome help. But how?"
            "\n\n"

            "Almost as if in answer to your question, you hear mournful howl of a \nwolf close-by...."
            "\n\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

}

void ending()
{
    char temp; //Press to continue//

    cout<< "\n\n\n"
    "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "With your heart still racing, you burst through\n"
    "the front door and to freedom.\n"
    "\n"
    "The forest outside is cold and dark, but anywhere\n"
    "is better than back inside that spooky cathedral.\n"
    "\n"
    "Running with all your strength down a lonely forest\n"
    "road, you stop to catch your breath.\n\n"
    "\"Now what?\" you wonder...did you just escape from\n"
    "the jaws of death only to put yourself in an even\n"
    "worse situation?\n"
    "\n"
    "\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "You stomach rumbles as you realize you are\n"
    "hungry again. At the same time from behind you\n"
    "comes a chorus of howls comes from the forest...\n"
    "\n"
    "You open your backpack once more for a last meal,\n"
    "and pull out the final bite of "<< player.food <<".\n"
    "Here goes nothing..."
    "\n"
    "\nIt still tastes like stale gym socks...\n"
    "\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "You wake up and find yourself in front of the gas station.\n"
    "\n"
    "The tour bus is parked out front and filled with everyone \n"
    "from before, and the tour guide is standing outside the bus\n"
    "conversing with two policemen. \n"
    "\n"
    "\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "He give s a shout upon seeing your face, and all three\n"
    "rush towards you. \n\n\"What Happened!?\" Demands one of the officers.\n"
    "\n"
    "The truth? Even you aren't sure, so you give a story of\n"
    "getting lost in the woods. The other officer nods knowingly,\n"
    "as if this happens all the time.\n"
    "\n"
    "Soon you are back on track again and on the bus to Prague.\n"
    "Your fellow travelers are still angry at you about\n"
    "the delay in their trip (you were missing for 5 hours)\n"
    "but you couldn't care less at this point.\n"
    "\n"
    "\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"

    "The woods give way to farmland, and the sun just starts \n"
    "to rise as you finally fall asleep. Was the whole thing a dream? You\n"
    "aren't sure, but no matter what happens you are never \n"
    "eating a "<< player.food <<" ever again.\n"
    "\n"
    "\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    room_num = 1000;
}

bool validate_com (string &action, string act_list[])
{

    int pass = 0;

    for (int j = 0; j < action.length(); j++)

        {
            action.at(j) = toupper(action.at(j));
        }


    //used for debugging: cout<< "IS UPPERCASE? " << action; //


    for (int i = 0; i < 28; i ++)
        //Had a runtime error here as I had made the count too high which made the program try to access a non-existent index value for ‘act_list’ Requirement #8//

        {

            if (action == act_list[i])

                {

                    pass = pass + 1;

                }


        }

    if (pass > 0)

    {
        return true;
    }

    else

    {
        return false;
    }


}

bool validate_object (string &object, string obj_list[], int arr)
{

    int pass = 0;

    for (int j = 0; j < object.length(); j++)

        {
            object.at(j) = toupper(object.at(j));
        }


    //used for debugging: cout<< "IS UPPERCASE? " << action; //


    for (int i = 0; i < arr; i ++)

        {

            if (object == obj_list[i])

                {

                    pass = pass + 1;

                }


        }

    if (pass > 0)

    {
        return true;


    }

    else

    {
        return false;
    }


}

bool check_keyItems (string &object, string obj_list[], int arr)
{

        int pass = 0;

    for (int j = 0; j < object.length(); j++)

        {
            object.at(j) = toupper(object.at(j));
        }


    //used for debugging: cout<< "IS UPPERCASE? " << action; //


    for (int i = 0; i < arr; i ++)

        {

            if (object == obj_list[i])

                {

                    pass = pass + 1;

                }


        }

    if (pass > 0)

    {
        return true;

    }

    else

    {


        return false;
    }



}


void use_keyItems (string action, string item)
{

/************************************************
You will only be able to interact with key objects in certain rooms. All other rooms will say "You can't use the item in this way..." when you try to use them.
*************************************************/
/************************************************
For the tankard.
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if ( action == "USE" &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {
                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a pewter tankard with an ornate engraving of a deer in a forest.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the Keys
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "KEY")
        {
            if (items.backpack[0] == 1 || items.backpack[1] == 1 )

                {
                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nTo use a key, try traveling in the direction of the door\nyou want to unlock.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "KEY")

         {

             if (items.backpack[0] == 1 || items.backpack[1] == 1 )
                {
                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "KEY")

         {

             if (items.backpack[0] == 1 || items.backpack[1] == 1 )
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt looks like a key alright...\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the fork.
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "FORK")
        {
            if (items.backpack[2] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }



     if (  action == "USE" &&  item == "FORK")

         {

             if (items.backpack[2] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "FORK")

         {

             if (items.backpack[2] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a large fork made of silver.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the Lantern
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "LANTERN")

         {

             if (items.backpack[3] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "LANTERN")

         {

             if (items.backpack[3] == 1)
                {

                   cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a gas lantern that gives off a soft glow.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the rabbit
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "RABBIT")
        {
            if (items.backpack[5] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "RABBIT")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "RABBIT")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nA fluffy brown bunny lies asleep in your arms.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the musket
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  (item == "GUN" || item == "MUSKET") )
        {
            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  (item == "GUN" || item == "MUSKET"))

         {

             if (items.backpack[7] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<<"\nYou only have one shot- better save it for when\nyou absolutely need it.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  (item == "GUN" || item == "MUSKET"))

         {

             if (items.backpack[7] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nAn old hunting musket filled with powder and a fork.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

/************************************************
For the Soup
*************************************************/
     if ( (action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP"  || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "SOUP")
        {
            if (items.backpack[5] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }


     if ( action == "USE" &&  item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if ( (action == "EAT" || action == "TASTE") &&  item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nYou take a sip of the soup. It is a bit oily, \nbut otherwise not too bad.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if ( (player.action =="LOOK" || player.action == "EXAMINE") && item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                   cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nThe soup is filled with meat and a few vegetables. \nIt looks really oily and is still lukewarm.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


}


void all_items::avarice()
{

items.backpack[0] = 1;
items.backpack[1] = 1;
items.backpack[2] = 1;
items.backpack[3] = 1;
items.backpack[4] = 1;
items.backpack[5] = 1;
items.backpack[6] = 1;
items.backpack[7] = 1;


}

void all_items::player_message(int stars)
{
    if (stars ==0)

        {
            cout<<"\nCHEAT ACTIVATED: ALL ITEMS\n* * * * * * *\n\n";

            inventory* pointing;

            pointing = &items; //requirement # 23//

            int hold_struct_value = pointing->backpack[0];

            double explicit_typecast_example=  static_cast<double> (hold_struct_value); //this is to meet requirement # 3//

            cout.setf (ios:: fixed);

            cout.setf (ios ::showpoint);

            cout.precision (1) ;


            cout<< "\nAll Key item status is flagged as "<< explicit_typecast_example * 1.0 <<"\n";

            int bitwise = 5; //for requirement #5//

            bitwise = bitwise ^ 4; //0111
                                   //0100
                                   //0110

            cout<< "A flag status of "<< bitwise<<".0 places that item in the player's inventory.\n\n";

        }

    else
        {
            cout<<"* ";

            player_message(stars-1); //Recursion requirement # 16//
        }

}
/************************************************
!ROOM FUNCTION DEFINITIONS!
*************************************************/
void G_H::look()
{
    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
            "You are in what appears to be a long abandoned\n"
            "chapel. Stained glass windows peek from\n"
            "between columns along the wall, and faint moonlight\n"
            "spills in from a portion of the ceiling that\n"
            "has fallen in.\n"
            "\n"
            "In this light it is hard to make out what the \n"
            "windows depict, but the room is illuminated just \n"
            "enough to show some pews in various states of\n"
            "disrepair, as well as an altar.\n"
            "\n"
            "There is an arched corridor leading to a foyer \n"
            "to your north,and doors to your east and \n"
            "west.\n"
            "\n"
            "\n";
}

void G_H::set_objects (string obj[])
{
    obj[0] = "PEW";
    obj[1] = "PEWS";
    obj [2] = "ALTAR";
    obj [3] = "WINDOW";
    obj [4] = "WINDOWS";
    obj [5] = "NOTE";
}

void G_H::goto_great_hall ()
{
    int looping = 0;

    set_objects(GH_objects);

    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";


        cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "CHAPEL\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";


        if (wolfy.dont_go_in_the_basement == 1)

        {
            cout<< "\nYou hear a howl echoing through the chapel.\nIt is hard to hear where it came from, but it sounds close.\n\n";

        }

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {

            if (player.action == "NORTH" || player.action == "N" || player.action == "WEST" || player.action == "W" || player.action == "EAST" || player.action == "E")

            {
                cout<<"\n";

                if (player.action == "NORTH" || player.action == "N")

                {

                        room_num = 2; //go to the foyer.

                        break;

                }

                if (player.action == "EAST" || player.action == "E") //meets requirement #4//

                {

                        room_num = 3;// go to the kitchen//

                        break;

                }

                if (player.action == "WEST" || player.action == "W")

                {
                        if (items.backpack[3]== 1) //if the player has the backpack//

                            {
                                room_num = 4;// go to the hallway//

                                break;
                            }

                        else

                            {

                                cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                cout<< "The area ahead has no windows and is pitch black. \nYou'll need a light before you can continue.\n\n";
                            }



                }

            }

            else if (player.action == "SOUTH" || player.action == "S")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;


                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }


                cout<< "\n\n";

                if (check_keyItems(player.object, key_items, items.arr_size))

                    {   cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }

                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }

                else if(validate_object(player.object, GH_objects, arr_size))

                    {

                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                        use_objects(player.action, player.object);

                    }
                else

                    {
                        cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }





}


void G_H::use_objects(string action, string item)
{

/************************************************
This first section is for interacting with the windows.
*************************************************/

    if (action == "EAT" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nWhile the colored glass in the windows may turn out to be fruit flavored\n(with red glass for cherry and blue for that funky blue-raspberry taste),\nperhaps you'd better not risk it.\n\n";
        }

    if (action == "TASTE" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nIt tastes like dust and lead.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou violently bust a hole into a stained glass window with a scowl on your face. \nDoes it make you feel alive breaking things, you monster?\n\n";
        }

    if (action == "OPEN" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou aren't able to open the windows.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nWhile a stained glass window would make a neat present to take back home, you don't\nhave room in your suitcase.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou try verbally assaulting the stained glass windows, making a quip \nabout their mothers. Windows don't have mothers however, and your \nwords fall on deaf ears.\n\n";
        }

    if (action == "TALK" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nOpening up to the figures portrayed in the glass, you talk about your\ncurrent plight. It makes you feel a bit better.\n\n";
        }

    if (action == "READ" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nThere isn't much to read on stained glass windows...not unless you know latin.\n\n";
        }

    if (action == "USE" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nThe use of a window is to let light in from outside.\n\n";
        }

    if ( (action == "EXAMINE" || action == "LOOK") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout<< "\nThe stained glass windows portray religious scenes. Cracks and small holes \nare the only visible signs of damage. Faintly backlit by the \nfull moon outside, the windows provide a calming atmosphere.\n\n";
        }


/************************************************
This second section is for interacting with the pews.
*************************************************/

     if (action == "EAT" && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nThe pews are too big- you couldn't possibly eat all of one.\n\n";
        }

    if (action == "TASTE" && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nYou crouch down and take a nibble. It tastes a bit like oak.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "PEW" || item == "PEWS") )
        {
            cout << "\nMany of the pews are already splintered and broken, so what's the harm?\nYour attack on the pews however only leaves small dents in the thick wood.\n\n";
        }

    if (action == "OPEN" && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nYou spend a long time looking, but can't find any openings in the pews.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "PEW" || item == "PEWS") )
        {
            cout << "\nThe pews are too heavy, and you aren't interested in the broken pieces of pew the ground.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nYour words bounce from between the pews and echo into the vaulted ceiling above.\n\n";
        }

    if (action == "TALK" && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nTalking to inanimate objects is a sign of insanity.\n\n";
        }

    if (action == "READ" && (item == "PEW" || item == "PEWS") )
        {
            cout << "\nP-E-W. Pew is a short word to read.\n\n";
        }

    if (action == "USE" && (item == "PEWS" || item == "PEW") )
        {
            cout << "\nfinding one of the intact pews, you have a seat to gather your thoughts.\n\n";
        }

    if ((action == "EXAMINE" || action == "LOOK")&& (item == "PEWS" || item == "PEW") )
        {
            cout<< "\nBattered and scratched, the pews are in a sorry state. Some are even\nin pieces as if smashed with a large object.\n\n";
        }


/************************************************
This third section is for interacting with the Altar.
*************************************************/

      if (action == "EAT" && item == "ALTAR")
        {
            cout << "\nFor some reason looking at the altar reminds you of your \nprevious meal, and you loose all appetite.\n\n";
        }

    if (action == "TASTE" && item == "ALTAR" )
        {
            cout << "\nIt tastes just OK.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "ALTAR")
        {
            cout << "\nYour attack on the altar only leaves small dents in the thick wood.\n\n";
        }

    if (action == "OPEN" && item == "ALTAR")
        {
            cout << "\nThe back of the altar opens to a small cabinet, but someone\nhas already removed all the contents.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "ALTAR")
        {
            cout << "\nThe altar is too big to carry.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "ALTAR")
        {
            cout << "\nThe altar is unphased by your words. It has \nheard worse.\n\n";
        }

    if (action == "TALK" && item == "ALTAR")
        {
            cout << "\nThe altar doesn't seem to want to chat with you at the \nmoment.\n\n";
        }

    if (action == "READ" && item == "ALTAR")
        {
            cout << "\nThere is a note scratched into the altar.\nDid you mean to read the note?\n\n";
        }

    if (action == "USE" && item == "ALTAR")
        {
            cout << "\nThe altar doesn't have much use right now.\nMaybe if you feel like giving a sermon next time...\n\n";
        }

    if ((action == "EXAMINE" || action == "LOOK") && item == "ALTAR")
        {
            cout<< "\nThe wooden altar is in fairly good shape, outside of a\n note scratched on its front. Any decorations or items\nhave been stripped from the altar.\n\n";
        }


/************************************************
This fourth section is for interacting with the note.
*************************************************/

    if (item == "NOTE" && (action == "READ" || action == "EXAMINE" || action == "LOOK"))
        {
            if (items.backpack[3] == 1)
                {
                    cout << "\nThe note scratched into the altar reads:\" OMUL ESTE LUP PENTRU OM\".\n\n";
                }
            else
                {
                    cout << "\nIt is too dark to make out what is written.\n\n";
                }
        }

    if (item == "NOTE" && !(action == "READ" || action == "EXAMINE"))

        {
            cout<<"\nThat's not something you can do to a note...\n\n";
        }

    }

void front_door::look()
{

    cout<<"\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
        "You are in a small foyer, with a corridor leading to the\n"
        "main chapel to your south.\n"
        "\n"
        "The room is quite dark, but you can see a glimpse of\n"
        "the outside through two barred windows on the northern \n"
        "wall. \n"
        "\n"
        "A stand with a ratty coat strewn "
        "over it rests\n in the corner, and a smashed collection box \n"
        "lies in splinters on the ground.\n"
        "\n"
        "To your north is a great iron door.";
        "\n"
        "\n";

}

void front_door::set_objects(string obj[])
{
    obj[0] = "DOOR";
    obj[1] = "WINDOW";
    obj [2] = "WINDOWS";
    obj[3] = "STAND";
    obj [4] = "COAT";
    obj [5] = "BOX";
}

void front_door::use_objects(string action, string item)
{
/************************************************
This first section is for interacting with the windows.
*************************************************/


    if (action == "EAT" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nThe windows look delicious, but bars are in the way.\n\n";
        }

    if (action == "TASTE" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou stick your tongue through the bars, desperate for a taste of window. \nAlas, it is just out of reach and you decide to give up.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou strike at the bars covering the windows, but are unable to break them.\n\n";
        }

    if (action == "OPEN" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nBars prevent you from getting to the window.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nRemoving a window is one thing...removing a window with bars? That\nis beyond your paygrade.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nYou give it a go, but the windows seem to take everything you say in stride.\n\n";
        }

    if (action == "TALK" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nTalking to the window still doesn't convince it to open\n\n";
        }

    if (action == "READ" && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout << "\nThere are sadly no books outside of the window to read.\n\n";
        }


    if ( (action == "EXAMINE" || action == "USE" || action == "LOOK") && (item == "WINDOW" || item == "WINDOWS") )
        {
            cout<< "\nThe long windows stretch from floor to ceiling and are covered by metal bars.\nAn unusually bright moon allows you to see a bit of forest and a road that\ntrails off into darkness.\n\n";

        }
/************************************************
This second section is for interacting with the box.
*************************************************/

     if (action == "EAT" && item == "BOX")
        {
            cout << "\nYou try eating the broken box, but get a splinter in your tongue.\n\n";
        }

    if (action == "TASTE" && item == "BOX")
        {
            cout << "\nYou have a small bite. You taste dirt, wood, and shame.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "BOX" )
        {
            cout << "\nIt looks like someone already did that to the collection box for you.\n\n";
        }

    if (action == "OPEN" && item == "BOX" )
        {
            cout << "\nThe collection box is already broken open.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "BOX")
        {
            cout << "\nYou search through the remains of the collection box, but there is nothing left\nto take.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "BOX")
        {
            cout << "\nDon't be silly. Someone murdered the box, so it can no longer hear you.\n\n";
        }

    if (action == "TALK" && item == "BOX" )
        {
            cout << "\nDon't be silly. Someone murdered the box, so it can no longer hear you.\n\n";
        }

    if (action == "READ" && item == "BOX" )
        {
            cout << "\nNothing is written on the collection box.\n\n";
        }

    if (action == "USE" && item == "BOX" )
        {
            cout << "\nIn its current state, you can't really use the collection box anymore.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "BOX" )
        {
            cout<< "\nThe collection box has been over turned and completely smashed in. Someone has\ntaken all the money inside.\n\n";
        }


/************************************************
This third section is for interacting with the coat-stand.
*************************************************/

      if (action == "EAT" && item == "STAND")
        {
            cout << "\nThe stand is too long and won't fit in your mouth...if only you\nhad a saw!.\n\n";
        }

    if (action == "TASTE" && item == "STAND")
        {
            cout << "\nPerhaps it because of your now ravenous hunger, but the coat stand\ndoesn't taste too bad.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "STAND")
        {
            cout << "\nYou break off a piece of the coat stand, ensuring that it will never hold\na coat again.\n\n";
        }

    if (action == "OPEN" && item == "STAND")
        {
            cout << "\nYou can't open the coat stand.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "STAND")
        {
            cout << "\nYou pick up the coat stand.\nYou then put it back down because you remembered that you already own one.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "STAND")
        {
            cout << "\nNo need to get angry, the coat stand is just trying to do its job.\n\n";
        }

    if (action == "TALK" && item == "STAND")
        {
            cout << "\nThe coat stand doesnt seem to...underSTAND you.\n\n";
        }

    if (action == "READ" && item == "STAND")
        {
            cout << "\nThere is nothing written on the coat stand\n\n";
        }

    if (action == "USE" && item == "STAND")
        {
            cout << "\nYou are too cold to take off your jacket.\n\n";
        }

    if (action == "EXAMINE" && item == "STAND")
        {
            cout<< "\nIt is a fairly nondescript coat stand.\n\n";
        }


/************************************************
This fourth section is for interacting with the coat.
*************************************************/

       if (action == "EAT" && item == "COAT" )
        {
            cout << "\nWhy? Did you loose a bet?.\n\n";
        }

    if (action == "TASTE" && item == "COAT" )
        {
            cout << "\nOnce you've tried one coat, you've tried them all.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "COAT" )
        {
            cout << "\nThe coat is now even more wrinkly than before.\n\n";
        }

    if (action == "OPEN" && item == "COAT" )
        {
            cout << "\nThe is nothing inside the coat pockets except for lint.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && item == "COAT" )
        {
            cout << "\nAs soon as you pick up the coat, an hideous smell hits your nose.\nPerhaps you'd be better off with your own jacket.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "COAT" )
        {
            cout << "\nThe coat is already in bad shape- no need to rub it in.\n\n";
        }

    if (action == "TALK" && item == "COAT" )
        {
            cout << "\nCoats are to be seen, not to be heard.\n\n";
        }

    if (action == "READ" && item == "COAT")
        {
            cout << "\nThere is nothing to read on the coat.\n\n";
        }


    if ( action == "EXAMINE" && item == "COAT")
        {
            cout<< "\nThe coat is made of some sort of fabric and is filthy and ragged.\nRust colored stains are sprayed across the front, and you silently\nhope that it is not blood. It smells awful.\n\n";
        }

  /************************************************
This last section is for interacting with the front door.
*************************************************/
     if (action == "EAT" && item == "DOOR")
        {
            cout << "\nYou'll break a tooth, so you decide against it.\n\n";
        }

    if (action == "TASTE" && item == "DOOR")
        {
            cout << "\nIt tastes metallic.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "DOOR" )
        {
            cout << "\nThe door is strong and you can't damage it.\n\n";
        }

    if ( (action == "OPEN" || action == "USE") && item == "DOOR" )
        {
            if (items.backpack[0] == 1)
                {
                    cout << "\nYou unlock the door and can now leave.\n\n";
                }
            else
                {
                    if (items.backpack[1] ==1)

                        {
                            cout<<"\nYour current key doesn't seem to be the right one\nfor this door.\n\n";
                        }

                    cout << "\nThe door is locked tight.\n\n";
                }
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "DOOR")
        {
            cout << "\nThe door is attached to the wall.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "DOOR")
        {
            cout << "\nYou can't seem to distract the door from its job of being a door.\n\n";
        }

    if (action == "TALK" && item == "DOOR")
        {
            cout << "\nYou can't seem to distract the door from its job of being a door.\n\n";
        }

    if (action == "READ" && item == "DOOR")
        {
            cout << "\nNothing is written on the door.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "DOOR")

        {


            cout<< "\nA massive iron door stand between you and the outside.\n\n";

        }
}

void front_door::goto_front_door ()
{
    int looping = 0;

    set_objects(front_door_objects);




    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "FOYER\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "SOUTH" || player.action == "S" )

            {
                room_num = 1; //go to main hall//

                break;

            }
            else if (player.action == "NORTH" || player.action == "N")

            {

                if (items.backpack[0] == 1)

                    {
                        ending();

                        break;
                    }

                else

                    {
                        cout<< "\nThe door is locked tight, and you\ndon't have the key to open it.\n";
                    }
            }

            else if (player.action == "WEST" || player.action == "W" || player.action == "EAST" || player.action == "E")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if (check_keyItems(player.object, key_items, items.arr_size))

                    {
                         cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }


                else if(validate_object(player.object, front_door_objects, arr_size))
                {

                    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                    use_objects(player.action, player.object);

                }

                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }

                else
                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n";
                }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }


}


void kitchen::look ()
{

    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
        "You are in a rectangular stone room with\n"
        "thick wooden beams crossing the ceiling.\n"
        "The faint sent of spice mixed with mildew\n"
        "lingers in the air\n"
        "\n"
        "A large stove is against the eastern\n"
        "wall with a pot of soup still left \n"
        "on a burner. A sink and cabinet \n"
        "are against the southern wall.\n"
        "\n"
        "In the center of a room lies a heavy\n"
        "wooden table covered in gashes.\n"
        "\n";


    if (items.backpack[3] == 0)


        cout<< "A lit gas lantern burns softly on the table.\n";

    if (wolfy.dont_go_in_the_basement ==1)

    {
        cout<< "\nA rather vicious werewolf is in the room with you.\n\n";
    }


    cout <<"\n\n";


}

void kitchen::set_objects (string obj[])
{

    obj[0] = "TABLE";
    obj[1] = "STOVE";
    obj[2] = "DISHES";
    obj[3] = "DISH";
    obj[4] = "SINK";
    obj [5] = "CABINET";
    obj [6] = "LANTERN";
    obj [7] = "SOUP";
    obj [8] = "SILVERWARE";
}

void kitchen::use_objects(string action, string item)
{

/************************************************
This first section is for interacting with the dishes.
*************************************************/

    if (action == "EAT" && (item == "DISH" || item == "DISHES") )
        {
            cout << "\nUsually you eat what is on the dishes, not the dishes themselves.\n\n";
        }

    if (action == "TASTE" && (item == "DISH" || item == "DISHES")  )
        {
            cout << "\nThe dishes have been washed, so you can't taste anything on them.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "DISH" || item == "DISHES")  )
        {
            if ((broke ==0))
            {
                cout << "\nYou pull out a dishes and smash them to the ground.\n\n";

                broke = 1;
            }

            else

            {
                cout<<"\nThe dishes are already broken. \n\n";
            }
        }

    if (action == "OPEN" && (item == "DISH" || item == "DISHES") )
        {
            cout << "\nDishes are very open- you can't hide anything on them.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && (item == "DISH" || item == "DISHES")  )
        {
            if ((broke ==0))
                {
                    cout << "\nYou pull out a dish, causing a chain reaction. All at once\nthe dishes come pouring out of the cabinet and smash over the floor.\nFortunately you were not hurt.\n\n";

                    broke = 1;
                }

            else

                {
                 cout<<"\nThe dishes are broken and you can't use them. \n\n";
                }

        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "DISH" || item == "DISHES")  )
        {
            cout << "\nThe dishes seem indifferent to your rantings.\n\n";
        }

    if (action == "TALK" && (item == "DISH" || item == "DISHES")  )
        {
            cout << "\nThe dishes seem indifferent to your rantings.\n\n";
        }

    if (action == "READ" && (item == "DISH" || item == "DISHES")  )
        {
            cout << "\nThere are sadly no books outside of the window to read.\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") && (item == "DISH" || item == "DISHES")  )
        {
            if ((broke ==0))
                {
                    cout << "\nThe Dishes in the cabinet are white with a blue trim.\nSomeone has washed them.\n\n";

                }

                else

                {
                 cout<<"\nThe dishes lie broken on the floor. \n\n";
                }

        }
/************************************************
This second section is for interacting with the TABLE.
*************************************************/

     if (action == "EAT" && item == "TABLE")
        {
            cout << "\nEating the table is bad dinner manners.\n\n";
        }

    if (action == "TASTE" && item == "TABLE")
        {
            cout << "\nYou have a small bite. You taste dirt, wood, and shame.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "TABLE")
        {
            cout << "\nYou injure your hands striking the heavy wooden table with your fists.\n\n";
        }

    if (action == "OPEN" && item == "TABLE" )
        {
            cout << "\nTable are already very open- you can't hide anything on them.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "TABLE")
        {
            cout << "\nThe table is far too heavy to lift.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "TABLE")
        {
            cout << "\nYou yell at the table that it may be bigger than you,\nbut it has no soul.\n\n";
        }

    if (action == "TALK" && item == "TABLE")
        {
            cout << "\nTable-talk is difficult to do with only one person.\n\n";
        }

    if (action == "READ" && item == "TABLE")
        {
            cout << "\nNo letter, notes, or engravings are on the table.\n\n";
        }

    if (action == "USE" && item == "TABLE")
        {
            cout << "\nOddly enough, the room has no chairs.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "TABLE")
        {
            cout<< "\nIt is a thick and heavy wooden table. Stains cover its surface\nand it seems well used.\n\n";
        }


/************************************************
This third section is for interacting with the stove.
*************************************************/

     if (action == "EAT" && item == "STOVE")
        {
            cout << "\nYou have to remind yourself that stoves are to make things\nfor eating, not for eating themselves.\n\n";
        }

    if (action == "TASTE" &&  item == "STOVE")
        {
            cout << "\nYou scrape off a bit of grime with your finger and\nhave a taste. It tastes like oil and carbon.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") &&  item == "STOVE")
        {
            cout << "\nYou injure your hands striking the stove with your fists.\n\n";
        }

    if (action == "OPEN" &&  item == "STOVE")
        {
            cout << "\nThe oven beneath the stove seems functional but\ncurrently is empty.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") &&  item == "STOVE")
        {
            cout << "\nThe stove is attached to the wall.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") &&  item == "STOVE")
        {
            cout << "\n\"MICROWAVES ARE THE FUTURE!\" you yell.\n\n";
        }

    if (action == "TALK" &&  item == "STOVE")
        {
            cout << "\nThe stove seems shy.\n\n";
        }

    if (action == "READ" &&  item == "STOVE")
        {
            cout << "\nThere are some dials and marking on the stove to indicate\ntemperature.\n\n";
        }

    if (action == "USE" &&  item == "STOVE")
        {
            cout << "\nYou don't have anything you want to cook.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") &&  item == "STOVE")
        {
            cout<< "\nCast iron and black, the large stove looks somewhat foreboding \nthe glow of the lantern light. A large pot of \nsoup is on a burner, and a large oven in the center of the stove \nlies open and empty.\n\n";
        }
/************************************************
This fourth section is for interacting with the sink.
*************************************************/
     if (action == "EAT" && item == "SINK")
        {
            cout << "\nThere really isn't anything to eat in the sink.\n\n";
        }

    if (action == "TASTE" && item == "SINK")
        {
            cout << "\nEven you don't want to try the sink or the dirty water that it is\nfilled with.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "SINK")
        {
            cout << "\nYou injure your hands attacking the sink, but you think it has learned\nits lesson.\n\n";
        }

    if (action == "OPEN" && item == "SINK")
        {
            cout << "\nOpening a small cabinet door beneath the sink, you see some pipes and mold.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "SINK")
        {
            cout << "\nThe sink is firmly attached to the wall.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "SINK")
        {
            cout << "\nYou angrily lash out at the sink. You have always had issues with sinks\nsince that incident in 5th grade.\n\n";
        }

    if (action == "TALK" && item == "SINK")
        {
            cout << "\nThe sink gives you the cold shoulder.\n\n";
        }

    if (action == "READ" && item == "SINK")
        {
            cout << "\nYou don't feel like digging for reading materials in the dirty sink.\n\n";
        }

    if (action == "USE" && item == "SINK")
        {
            cout << "\nTurning a tap, a thin stream of water comes out.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "SINK")
        {
            cout<< "\nThe sink is copper and large enough to fit a grown man comfortably. It is\nfilled with murky water, and you would rather not stick your hand inside.\n\n";
        }

  /************************************************
This fifth section is for interacting with the cabinet.
*************************************************/
      if (action == "EAT" && item == "CABINET")
        {
            cout << "\nFood is usually in a pantry.\n\n";
        }

    if (action == "TASTE" && item == "CABINET")
        {
            cout << "\nFood is usually in a pantry.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "CABINET")
        {
            cout << "\nYou give the cabinet a good hard thump.\n\n";
        }

    if (action == "OPEN" && item == "CABINET")
            if (!(broke ==0))
                {
                    cout << "\nThe cabinet contains various types of silverware and dishes.\n\n";

                }

                else

                {
                 cout<<"\nThe cabinet contains various types of silverware. \n\n";
                }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "CABINET")
        {
            cout << "\nYou can't lift it.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "CABINET")
        {
            cout << "\nFor some reason, you pity the cabinet and decide not to.\n\n";
        }

    if (action == "TALK" && item == "CABINET")
        {
            cout << "\nThe cabinet won't judge you.\n\n";
        }

    if (action == "READ" && item == "CABINET")
        {
            cout << "\nYou can't find anything to read.\n\n";
        }

    if (action == "USE" && item == "CABINET")
        {
            cout << "\nIt seems full enough as it is.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "CABINET")
        {
            if ((broke ==0))
                {
                    cout << "\nThe cabinet is made of a handsome dark wood and stands on clawed feet. \nOpening the bronze handle doors reveals various types of silverware\n and dishes inside.\n\n";

                }

                else

                {
                 cout<<"\nThe cabinet is made of a handsome dark wood and stands on clawed feet. \nOpening the bronze handle doors reveals various types of silverware\ninside.\n\n";
                }
        }


/************************************************
This sixth section is for interacting with the soup.
*************************************************/

     if (action == "EAT" && item == "SOUP")
        {
            cout << "\nYou have a taste of the soup. \n\nIt has some sort of unknown meat mixed with vegetables as its base, \nand is both tasty and quite oily.\n";
        }

    if (action == "TASTE" && item == "SOUP")
        {
            cout << "\nYou have a taste of the soup. \n\nIt has some sort of unknown meat mixed with vegetables as its base, \nand is both tasty and quite oily.\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "SOUP")
        {
            cout << "\nSoup with bits of meat splashes everywhere as you pound the surface of the soup.\n\n";
        }

    if (action == "OPEN" && item == "SOUP")
        {
            cout << "\nYou can't find an opening in the soup.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "SOUP")
            if (items.backpack[4]== 1)
                {
                    cout << "\nYou scoop some soup into your tankard.\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got SOUP\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";


                    items.backpack[6] = 1;
                }

                else

                {
                 cout<<"\nYou have nothing to put the soup in, and the pot is too heavy to carry. \n\n";
                }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "SOUP")
        {
            cout << "\nIf you don't have anything nice to say about the soup, then just don't eat it.\n\n";
        }

    if (action == "TALK" && item == "SOUP")
        {
            cout << "\nYou talk about your feeling on politics while staring into the soup.\n\n";
        }

    if (action == "READ" && item == "SOUP")
        {
            cout << "\nThere are no letter shaped noodles like in alphabet soup. That would\nreally improve the dish though.\n\n";
        }

    if (action == "USE" && item == "SOUP")
        {
            cout << "\nYou don't have any use for that now.\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "SOUP")
        {
            cout<< "\nA very large pot is filled to the brim with soup. Given the aroma that \nstill lingers, it can't have been made too long ago. The surface \nof the soup is very oily, but it smells good.\n\n";
        }

/************************************************
This sixth section is for interacting with the silverware.
*************************************************/

     if (action == "EAT" && item == "SILVERWARE")
        {
            cout << "\nTrying to swallow a spoon, it gets stuck on the way down. \nIt turns out you are not suppose to eat those things\n\n\n";

            cout<< "\n*****************************************" << endl
            << "\nGAME OVER\n"
            <<"*****************************************"<< endl << endl;
            exit(1);
        }

    if (action == "TASTE" && item == "SILVERWARE")
        {
            cout << "\nNot much flavor to it.\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "SILVERWARE")
        {
            cout << "\nYou dent some of the silverware, possibly causing untold damage to priceless antiques.\n\n";
        }

    if (action == "OPEN" && item == "SILVERWARE")
        {
            cout << "\nYou open and close the cabinet.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "SILVERWARE")
            if (items.backpack[2]== 1)
                {
                    cout << "\nYou already took a piece of silverware.\n\n";

                }

                else

                {
                 cout<<"\nLooking at the options, you decide to grab a silver fork from the cabinet."
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the FORK\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                        items.backpack[2] = 1;
                }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "SILVERWARE")
        {
            cout << "\nThe silverware's reputation is now forever tarnished.\n\n";
        }

    if (action == "TALK" && item == "SILVERWARE")
        {
            cout << "\nLooking at your reflection on the back of a large spoon, you \nmake silly faces while talking gibberish.\n\nHopefully that is out of your system now.\n\n";
        }

    if (action == "READ" && item == "SILVERWARE")
        {
            cout << "\nThere is nothing written on the silverware.\n\n";
        }

    if (action == "USE" && item == "SILVERWARE")
        {
            cout << "\nYou don't have any use for that now.\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "SILVERWARE")
        {
            cout<< "\nAll sorts of silverware and cutlery lies in the cabinet.Some of it appears to be\n stainless, but some also appears to be genuine silver based on the tarnishing.\n\n";
        }


/************************************************
This last section is for interacting with the lantern.
*************************************************/

      if (action == "EAT" && item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nYou'd better leave fire-eating to the professionals.";

                }
        }

    if (action == "TASTE" && item == "LANTERN" )
        {

            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nYou'd better leave fire-eating to the professionals.";

                }
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nYou rough up the lantern.";

                }
        }

    if (action == "OPEN" && item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nYou open the lantern to look inside. Inside is even more lantern.";

                }
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && item == "LANTERN")
        {
            if (items.backpack[3] == 1)


                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {
                        cout << "\nYou pick up the lantern. Now you can travel in the dark.\n\n";
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the LANTERN\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                        items.backpack[3] = 1;

                }


        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK") && item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nMaybe you are still feeling the effects of the food poisoning...";

                }

        }


    if (action == "READ" && item == "LANTERN")
        {
            if (items.backpack[3] == 1)


                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {
                    cout << "\n\"MADE IN CHINA\".\n\n";

                }
        }



    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "LANTERN")
        {
            if (items.backpack[3] == 1)


                {
                    cout<< "\nIt is a gas lantern that gives off a soft glow.\n\n";
                }

            else

                {
                    cout << "\nA gas lantern gives off a warm glow from the tabletop.\nSeeing the light gives you comfort.\n\n";

                }
        }
}

void kitchen::goto_kitchen()
{
    int looping = 0;

    int haslamp = 0; //'1' means that the player has the lantern already//

    set_objects(cook_objects);

    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "KITCHEN\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";



        if (items.backpack[3] == 1) //if the player has the lamp already//

        {
            haslamp = 1;
        }


        if (wolfy.dont_go_in_the_basement == 1 && show_wolf == 0)
            //logic error here as I had written dont_go_in_the_basement = 1 instead of '==1'. This cause it to automatically come back as 'true' even if the value wasn't actually equal to 1.//

        {
            cout<< "\nEntering the kitchen, you are horrified to see a mass of black\nfur lapping hungrily at the pot of soup on the stove.\nNoticing your presence, the werewolf stops and turns towards you...\n\n ";

            show_wolf = 1;

        }

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "NORTH" || player.action == "N" || player.action == "WEST" || player.action == "W")

            {
                cout<< "\nYou head " << player.action<<  ".\n";

                if (player.action == "WEST" || player.action == "W")

                {

                        room_num = 1;

                        break;

                }
                if (player.action == "NORTH" || player.action == "N")

                {

                        room_num = 8;

                        break;

                }

            }



            else if (player.action == "SOUTH" || player.action == "S" || player.action == "EAST" || player.action == "E")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if ( (check_keyItems(player.object, key_items, items.arr_size)) && !(player.object== "SOUP") && !(player.object =="LANTERN") && !(player.action =="USE" && player.object== "TANKARD") )

                    {
                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }

                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }


                else if (player.object == "TANKARD" && items.backpack[4] == 1)

                {

                        cout<<"\nWhat do you want to use that on?\n";

                        cin>> player.object;

                        for (int j = 0; j < player.object.length(); j++)

                            {
                                player.object.at(j) = toupper(player.object.at(j));
                            }

                        if (player.object == "SOUP")

                            {
                               cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                cout << "\nYou scoop some soup into your tankard.\n\n"
                                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                                        "You got SOUP\n"
                                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";


                                items.backpack[6] = 1;
                            }
                        else

                            {
                                cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                cout<< "\nYou can't use the item in that way.\n\n";
                            }

                }


                else if(validate_object(player.object, cook_objects, arr_size))
                    {

                    cout<< "\n";
                    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    use_objects(player.action, player.object);

                    }

                    else if ( (player.object=="WOLF" || player.object =="WEREWOLF") && wolfy.dont_go_in_the_basement == 1)

                    {
                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                        wolfy.use_objects(player.action, player.object);

                    }

                else
                    {
                    cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }


        if (wolfy.dont_go_in_the_basement == 1)

        {

            cout<<"\nThe wolf savagely attacks, causing you injury.\n\n";
            player.change_health(1);

        }
    }


}

void hall::look()
{

    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
        "\n"
        "You are in a long corridor running from from north to south.\n"
        "\n"
        "The walls are covered in a faded green wallpaper \n"
        "patterned with gold stripes and silver fluer di lis.\n"
        "\n"
        "Nail holes in portions of the wall indicate that\n"
        "many paintings were once hung here, but they are long \n"
        "since gone now.\n"
        "\n"
        "There are doors to your North, East, and West.\n"
        "\n"
        "To the south stairs lead downwards."
        "\n"
        "\n";

}


void hall::use_objects(string action, string item)
{


    //No objects to be used in the hall way//


}

void hall::goto_hall()
{
        int looping = 0;

    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "HALL WAY\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        if (wolfy.dont_go_in_the_basement == 1)

        {
            cout<< "\nEntering the hall, you hear the sounds of crashing\nand thundering roars from nearby.\n\n";



        }

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "NORTH" || player.action == "N" || player.action == "WEST" || player.action == "W" || player.action == "EAST" || player.action == "E" || player.action == "SOUTH" || player.action == "S")

            {
                cout<< "\nYou head " << player.action<<  ".\n";

                if (player.action == "NORTH" || player.action == "N")

                {
                        if (items.backpack[1] == 1)

                            {
                                if (wolfy.silver_bullet == 1)

                                {
                                    room_num = 7; //go to the bedroom//

                                    break;
                                }

                                else

                                {

                                 room_num = 9;

                                 break;

                                }
                            }

                        else

                        {
                            cout<<"The door to this room is locked...you will\nneed to find a key.\n\n";
                        }

                }

                if (player.action == "EAST" || player.action == "E")

                {

                        room_num = 1;// go to the chapel//

                        break;

                }
                if (player.action == "SOUTH" || player.action == "S")

                {

                        room_num = 5; //go to the basement//
                        break;

                }

                if (player.action == "WEST" || player.action == "W")

                {

                        room_num = 6;// go to the library//

                        break;

                }
            }


            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if (check_keyItems(player.object, key_items, items.arr_size))

                    {

                        use_keyItems(player.action, player.object);
                    }


                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }

                else

                    {
                        cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }

}

void basement::look()
{
    cout<<"\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "You are in a tiny low-ceiling cellar with earthen \n"
    "walls. Wine casks are piled in a corner and a spigot\n"
    "is stuck into one of them.\n"
    "\n";

    if (items.backpack[4] == 0)
    {
        cout<< "A tankard lies under the spigot.\n";
    }

    cout<<"\nTo your north stairs lead back to the hall way."
        "\n"
        "\n";

    if (wolfy.dont_go_in_the_basement ==1)

    {
        cout<< "\nA rather vicious werewolf is in the room with you.\n\n";
    }

}

void basement::set_objects(string obj [])
{
    obj[0] = "SPIGOT";
    obj[1] = "BARREL";
    obj [2] = "TANKARD";
    obj [3] = "BARRELS";

}

void basement::use_objects(string action, string item)
{

/************************************************
This first section is for interacting with the barrels.
*************************************************/

    if (action == "EAT" && (item == "BARREL" || item == "BARRELS") )
        {
            cout << "\nIf only you could open the barrel to get to the juicy center.\n\n";
        }

    if (action == "TASTE" && (item == "BARREL" || item == "BARRELS")  )
        {
            cout << "\nIt tastes like a barrel. You don't know what else it would've tasted like.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "BARREL" || item == "BARRELS") )
        {
            cout<< "\nYou break open a barrel, but it seems to have been emptied of all contents.\nStaining on the inside of the barrel indicates that it once held wine.\n\n";
        }

    if (action == "OPEN" && (item == "BARREL" || item == "BARRELS") )
        {
            cout << "\nYou kick in a barrel, but it seems to have been emptied of all contents.\nStaining on the inside of the barrel indicates that it once held wine.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && (item == "BARREL" || item == "BARRELS") )
        {
            cout << "\nYou try picking up a barrel. It is quite light.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "BARREL" || item == "BARRELS") )
        {
            cout << "\n\"You're like, a barrel-full of IDIOTS!\" you shout at the barrels.\n\n";
        }

    if (action == "TALK" && (item == "BARREL" || item == "BARRELS")  )
        {
            cout << "\nTalking to the barrels is oddly soothing.\n\n";
        }

    if (action == "READ" && (item == "BARREL" || item == "BARRELS")  )
        {
            cout << "\n\"VIN\" is painted in white on the sides of the barrels.\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") && (item == "BARREL" || item == "BARRELS")  )
        {

            cout << "\nThe barrels are unremarkable save for \"VIN\" being painted in white on the side.\n One\f them has a spigot in it.\n\n";

        }

/************************************************
This second section is for interacting with the SPIGOT.
*************************************************/

     if (action == "EAT" && item == "SPIGOT")
        {
            cout << "\nYou can't pull it out from the barrel.\n\n";
        }

    if (action == "TASTE" && item == "SPIGOT")
        {
            cout << "\nYou can't pull it out from the barrel.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "SPIGOT")
        {
            cout << "\nYou injure your hands attacking the spigot.\n\n";
        }

    if (action == "OPEN" && item == "SPIGOT")
        {
            cout << "\nA few drops of red wine come out.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "SPIGOT")
        {
            cout << "\nYou can't pull it out from the barrel.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "SPIGOT")
        {
            cout << "\nYour theory that harassing the spigot will make it produce wine is\nproven false.\n\n";
        }

    if (action == "TALK" && item == "SPIGOT")
        {
            cout << "\nPleading with the spigot does not make it produce anything.\n\n";
        }

    if (action == "READ" && item == "SPIGOT")
        {
            cout << "\n\"VIN\" is painted in white on the sides of the barrel that the spigot is attached to.\n\n";
        }

    if (action == "USE" && item == "SPIGOT")
        {
            cout << "\nA few drops of red wine come out.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "SPIGOT")
        {
            cout<< "\nIt is a well worn spigot stuck into a barrel.\n\n";
        }


/************************************************
This third section is for interacting with the tankard.
*************************************************/

     if (action == "EAT" && item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }


            else

                {
                     cout << "It just won't fit in your mouth.\n\n";
                }

        }

    if (action == "TASTE" &&  item == "TANKARD")
        {


            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nNothing is inside to taste.\n\n";

                }


        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") &&  item == "TANKARD")
        {

            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nYou dent the tankard.\n\n";

                }

        }

    if (action == "OPEN" &&  item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nThe tankard has no lid.\n\n";

                }


        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" ) &&  item == "TANKARD")
        {

            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nYou pick up the tankard.\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the TANKARD\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                    items.backpack[4] = 1;

                }



        }


    if ((action == "USE") &&  item == "TANKARD")
        {

            if (items.backpack[4] == 1)

                {
                     cout<<"\nWhat do you want to use that on?\n";

                    cin>> player.object;

                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nYou pick up the tankard.\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the TANKARD\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                    items.backpack[4] = 1;

                }



        }



    if ((action == "INSULT" || action == "HARASS" || action == "YELL") &&  item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nYou vent your rage at the tankard.\n\n";

                }

        }

    if (action == "TALK" &&  item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nTalking into the tankard makes an echo sound.\n\n";

                }

        }

    if (action == "READ" &&  item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nThere are no words on the tankard.\n\n";

                }

        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") &&  item == "TANKARD")
        {
            if (items.backpack[4] == 1)

                {
                    cout<< "\nIt is a pewter tankard with an ornate engraving of a deer in a forest.\n\n";
                }

            else

                {

                    cout<< "\nIt is a pewter tankard with an ornate engraving of a deer in a forest.\n\n";

                }

        }

}
void basement::goto_basement()
{

    int looping = 0;

    int hastankard = 0; //If the user has the tankard in their inventory//

    set_objects(basement_objects);


    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "CELLAR\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        if (wolfy.dont_go_in_the_basement == 1 && show_wolf == 0) //logic error here as I had written dont_go_in_the_basement ‘= 1’ instead of '==1'. This caused it to automatically come back as 'true' even if the value wasn't actually equal to 1. Requirement # 8//

            {


                cout<< "\nEntering the cellar, you are startled to see that you are\nnot alone. A werewolf of massive size breaks through the barrels\nand dashes towards you at breakneck speed..\n\nUnfortunately, this time you don't have any silverware.\n\n";

                show_wolf = 1;


            }


        if (items.backpack[4] == 1) //if the player has the tankard already//

            {
                hastankard = 1;
            }


        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "NORTH" || player.action == "N" )

            {
                        cout<< "\nYou head " << player.action<<  ".\n";

                        room_num = 4;

                        break;

            }

            else if (player.action == "SOUTH" || player.action == "S" || player.action == "EAST" || player.action == "E" || player.action == "WEST" || player.action == "W")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if ( (check_keyItems(player.object, key_items, items.arr_size)) && !(player.object == "TANKARD") )

                    {
                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }


                else if(validate_object(player.object, basement_objects, arr_size))

                    {
                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_objects(player.action, player.object);

                    }

                else if ( (player.object=="WOLF" || player.object =="WEREWOLF") && wolfy.dont_go_in_the_basement == 1)

                    {
                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                        wolfy.use_objects(player.action, player.object);

                    }

                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }

                else

                    {
                        cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }


        if (wolfy.dont_go_in_the_basement == 1)

        {

            cout<<"\nThe wolf savagely attacks, causing you injury.\n\n";
            player.change_health(1);

        }
    }

}

void libr::look()
{
    cout<<"\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
     "The room appears to be a personal library of sorts.\n"
    "Bookshelves line the walls, and a roaring fire\n"
    "lies lit in a fireplace on the southern wall. \n"
    "\n"
    "A leather chair is placed near the fire along with a \n"
    "large decorative vase. \n"
    "\n"
    "Above the fire a mounted moose head looks down sorrowfully.\n"
    "\n";
    if (items.backpack[4] == 0)
    {
        cout<< "An old musket is placed on the mantel beneath the head.\n";
    }

    cout<<"\nTo your East a door leads back to the hall way."
    "\n"
    "\n";


}

void libr::set_objects(string obj[])
{

    obj[0] = "VASE";
    obj[1] = "CHAIR";
    obj [2] = "MUSKET";
    obj [3] = "MOOSE";
    obj [4] = "HEAD";
    obj [5] = "BOOK";
    obj [6] = "BOOKS";
    obj [7] = "SHELVES";
    obj [8] = "SHELF";
    obj [9] = "FIRE";
    obj [10] = "FIREPLACE";
    obj [11] = "GUN";
}

void libr::use_objects(string action, string item)
{
/************************************************
This first section is for interacting with the shelves and books.
*************************************************/

    if (action == "EAT" && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {
            cout << "\nYou casually peruse through the bookshelves until you find a particularly \ninteresting leather bound book."
                    "Opening to the first page, you see a drawing of \nan apple so realistic that you bite into the paper. \n\nUnfortunately it was just a drawing, and not at tasty one at that.\n\n";
        }

    if (action == "TASTE" && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS")  )
        {
            cout << "\nYou casually peruse through the bookshelves until you find a particularly \ninteresting leather bound book."
                    "Opening to the first page, you see a drawing of \nan apple so realistic that you bite into the paper. \n\nUnfortunately it was just a drawing, and not at tasty one at that.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {

                cout << "\nYou go up to the bookshelves with intentions of violence. However at the last\nsecond you remember that books are the greatest treasure of all. You \ndecide to leave them alone.\n\n";
        }

    if (action == "OPEN" && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {
            cout << "\nTaking a book from the shelf, you open it up to read but find that everything is in Romanian.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS"))
        {
            cout << "\nTaking a book from the shelf, you open it up to \nread but find that everything is in Romanian.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {
            cout << "\nBooks don't have feelings that you can break.\n\n";
        }

    if (action == "TALK" && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {
            cout << "\nTalking to books is the first symptom of schizophrenia.\n\n";
        }

    if (action == "READ" && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS") )
        {
            cout << "\nTaking a book from the shelf, you open it up to read but find that everything is in Romanian.\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") && (item == "SHELF" || item == "SHELVES" || item == "BOOK" || item == "BOOKS"))
        {

            cout<< "\nBooks are piled high in shelves against the walls. The books look\nimpressive, but you can't understand their titles.";

        }
/************************************************
This second section is for interacting with the fireplace.
*************************************************/

     if (action == "EAT" && item == "FIREPLACE")
        {
            cout << "\nThere is nothing to eat around the fireplace, not even \na marshmallow.\n\n";
        }

    if (action == "TASTE" && item == "FIREPLACE") //Meets requirement #1//
        {
            cout << "\nThere is nothing to eat around the fireplace, not even \na marshmallow.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "FIREPLACE")
        {
            cout << "\nYour actions do nothing to damage the fireplace.\n\n";
        }

    if (action == "OPEN" && item == "FIREPLACE" )
        {
            cout << "\nThe fireplace is already open with a crackling fire inside.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "FIREPLACE")
        {
            cout << "\nThe fireplace is attached to the wall.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "FIREPLACE")
        {
            cout << "\n\"Santa would never come here!\" you shout.\n\n";
        }

    if (action == "TALK" && item == "FIREPLACE")
        {
            cout << "\nThe primal nature of fire has you regressing to an animal-like state.\n\n";
        }

    if (action == "READ" && item == "FIREPLACE")
        {
            cout << "\nNothing to read here.\n\n";
        }

    if (action == "USE" && item == "FIREPLACE")
        {
            cout << "\nYou warm up a bit by the fire.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "FIREPLACE")
        {
            cout<< "\nA sturdy stone fireplace sits in the middle of the wall.\nHot flames dance within as it heats the room.\n\n";
        }


/************************************************
This third section is for interacting with the FIRE.
*************************************************/

     if (action == "EAT" && item == "FIRE")
        {
            cout << "\nFire eating should be left to the professionals.\n\n";
        }

    if (action == "TASTE" &&  item == "FIRE")
        {
            cout << "\nFire eating should be left to the professionals.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") &&  item == "FIRE")
        {
            cout << "\nYou run into the fire in full-on attack mode.\n\n...unfortunately for you, the fire wins.\n\n";

            cout<< "\n*****************************************" << endl
            << "\nGAME OVER\n"
            <<"*****************************************"<< endl << endl;
            exit(1);

        }

    if (action == "OPEN" &&  item == "FIRE")
        {
            cout << "\nOpening a fire sounds dangerous.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") &&  item == "FIRE")
        {
            cout << "\nYou burn your hands trying to take some fire.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") &&  item == "FIRE")
        {
            cout << "\nFire seems to make you angry.\n\n";
        }

    if (action == "TALK" &&  item == "FIRE")
        {
            cout << "\nThe primal nature of fire has you regressing to an animal-like state.\n\n";
        }

    if (action == "READ" &&  item == "FIRE")
        {
            cout << "\nNo messages from the fire today.\n\n";
        }

    if (action == "USE" &&  item == "FIRE")
        {
            cout << "\nYou warm up a bit by the fire.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") &&  item == "FIRE")
        {
            cout<< "\nBright flames send shadows dancing across the room from the fire.\nThe warmth and light is almost hypnotic.\n\n";
        }
/************************************************
This fourth section is for interacting with the moose head.
*************************************************/
     if (action == "EAT" && (item == "MOOSE" || item == "HEAD") )
        {
            cout << "\nIt is a bit tough, but you get a bite of moose down.\n You could use a drink of water.\n\n";
        }

    if (action == "TASTE" && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nLeathery and gamey are the flavors that come to mind.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nThat which is dead can never die.\n\n";
        }

    if (action == "OPEN" && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nYou can't find an opening in the moose.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nIt is too bulky.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nYou give your best angry Bullwinkle impression.\n\n";
        }

    if (action == "TALK" && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\n\"Why the long face?\"\n\n";
        }

    if (action == "READ" && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nMoose are notoriously bad readers, so it\nmakes no sense to have one in a library.\n\n";
        }

    if (action == "USE" && (item == "MOOSE" || item == "HEAD"))
        {
            cout << "\nIt's too high up.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && (item == "MOOSE" || item == "HEAD"))
        {
            cout<< "\nA large stuffed and mounted moose head looks down\nfrom above the fire. It looks rather calm for being\na head on a wall.\n\n";
        }

  /************************************************
This fifth section is for interacting with the vase.
*************************************************/
      if (action == "EAT" && item == "VASE")
        {
            cout << "\nFood is usually in a pantry.\n\n";
        }

    if (action == "TASTE" && item == "VASE")
        {
            cout << "\nFood is usually in a pantry.\n\n";
        }


    if ( (action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN" ) && (item == "VASE") )
          {

           if ( items.backpack[1] == 0 )
                {
                    cout << "\nYou break open the side of the vase, revealing a\nsmall copper key on the bottom. You decide to hang onto the\nkey, just in case...\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the SMALL KEY\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                        items.backpack[1] = 1;
                }

                else

                {
                 cout<<"\nYou already broke open the vase. \n\n";
                }
          }
    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "VASE")
        {
            cout << "\nYou can't lift it.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "VASE")
        {
            cout << "\nFor some reason, you pity the cabinet and decide not to.\n\n";
        }

    if (action == "TALK" && item == "VASE")
        {
            cout << "\nThe cabinet won't judge you.\n\n";
        }

    if (action == "READ" && item == "VASE")
        {
            cout << "\nYou can't find anything to read.\n\n";
        }

    if (action == "USE" && item == "VASE")
        {
            cout << "\nIt seems more for decorative purposes.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "VASE")
        {
            if (items.backpack[1] == 0)
                {
                    cout << "\nThe vase is white with blue glazed vines going\nup its sides. It is quite large and goes up to your waist.\nyou can see something at the bottom of the vase out of\nreach.\n";

                }

            else
                {
                 cout<<"\nThe vase is white with blue glazed vines going\nup its sides. It may have been pretty once, but someone broke it.\n\n";
                }
        }


/************************************************
This sixth section is for interacting with the musket.
*************************************************/
     if (action == "EAT" && (item == "GUN" || item == "MUSKET") )
        {
            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nThat sounds dangerous.\n\n";

                }

        }

    if (action == "TASTE" && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1)

                {
                   cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nIt tastes like gunpowder.\n\n";

                }

        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nIt might come in handy- you shouldn't break it.\n\n";

                }

        }

    if (action == "OPEN" && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nThe gun is empty outside of some powder.\n\n";;

                }

        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "GUN" || item == "MUSKET"))
            if (combine ==1 && items.backpack[7] == 0)
                {
                    cout << "You take the fork loaded musket from the mantel.\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the MUSKET\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                        items.backpack[7] = 1;

                }

            else

                {


                if (items.backpack[7] == 1)

                    {
                        cout<< "\nYou can't use the item in that way.\n\n";
                    }

                else

                    {

                        cout<<"\nInspecting the musket, it is packed with powder but\nthere are no bullets. Perhaps you'd better come back later\nwhen you have something to put in it.\n\n";

                    }


                }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "GUN" || item == "MUSKET"))
        {


            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nShhhhh! Please keep your voice down in the library.";

                }
        }

    if (action == "TALK" && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nYou let the gun do the talking.\n\n";

                }

        }

    if (action == "READ" && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout << "\nThere are no words on the gun, but who\nreads a gun in a library?\n\n";

                }
        }

    if (action == "USE" && (item == "GUN" || item == "MUSKET"))
        {
            if (items.backpack [7] ==1 )

                {
                    cout<<"\nWhat do you want to use that on?\n";

                    cin>> player.object;

                    cout<<"\nYou only have one shot- better save it for when\nyou absolutely need it.\n\n";
                }

           else
                {
                    cout << "It's useless without some sort of ammunition.\n";
                }
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && (item == "GUN" || item == "MUSKET"))
        {

            if (items.backpack[7] == 1 || combine == 1)

                {
                    cout<< "\nAn old hunting musket filled with powder and a fork.\n\n";
                }

            else

                {

                    cout<< "\nIt is an old musket, filed with powder but\nno bullets.\n\n";

                }

        }

/************************************************
This last section is for interacting with the chair.
*************************************************/
     if (action == "EAT" && item == "CHAIR" )
        {
            cout << "\nSadly, it does not taste like hamburger.\n\n";
        }

    if (action == "TASTE" && item == "CHAIR")
        {
            cout << "\nSadly, it does not taste like hamburger.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "CHAIR")
        {
            cout << "\nThat cow already died a long time ago.\n\n";
        }

    if (action == "OPEN" && item == "CHAIR")
        {
            cout << "\nYou can't find an opening in the chair.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "CHAIR")
        {
            cout << "\nIt is too heavy.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "CHAIR")
        {
            cout << "\"YOU ARE CONTRIBUTING TO THE WORLD'S OBESITY PROBLEM!\" you shout.\n\n";
        }

    if (action == "TALK" && item == "CHAIR")
        {
            cout << "\nNo answer comes from the chair.\n\n";
        }

    if (action == "READ" && item == "CHAIR")
        {
            cout << "\nYou would need a book first.\n\n";
        }

    if (action == "USE" && item == "CHAIR")
        {
            cout << "\nYou take a seat. It is really comfy.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "CHAIR")
        {
            cout<< "\nAn old leather chair. It looks very comfortable.\n\n";
        }


}

void libr::goto_lib()
{

    int looping = 0;


    set_objects(lib_objects);


    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";


        cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "LIBRARY\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "EAST" || player.action == "E" )

            {
                        cout<< "\nYou head " << player.action<<  ".\n";

                        room_num = 4;

                        break;

            }

            /*else if (player.action == "LOOK")

            {
                look();

            }*/

            else if (player.action == "SOUTH" || player.action == "S" || player.action == "NORTH" || player.action == "N" || player.action == "WEST" || player.action == "W")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                for (int j = 0; j < player.object.length(); j++) //LOCAL VARIABLE ONLY Requirement #12//

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if ((check_keyItems(player.object, key_items, items.arr_size)) && (!(player.object == "GUN")) && (!(player.object == "MUSKET")) && (!(player.object == "FORK")))

                    {
                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }


                else if((validate_object(player.object, lib_objects, arr_size)) || (player.object =="FORK" && items.backpack[2] ==1))

                    {
                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                        if(player.object =="FORK" && items.backpack[2] ==1)

                        {
                            if (player.action== "USE" && items.backpack[7] == 0)

                            {
                                cout<<"\nWhat do you want to use that on?\n";

                                cin>> player.object;

                                for (int j = 0; j < player.object.length(); j++)

                                    {
                                        player.object.at(j) = toupper(player.object.at(j));
                                    }

                                if (player.object == "GUN" || player.object == "MUSKET")

                                    {
                                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                        cout<<"\nYou stuff the fork into the musket barrel.\n\n";
                                        combine = 1;
                                    }
                                else

                                {
                                   cout<< "\nYou can't use the item in that way.\n\n";
                                }
                            }

                            else

                            {
                                cout<< "\nYou can't use the item in that way.\n\n";
                            }
                        }


                        else
                        {

                            use_objects(player.action, player.object);

                        }
                    }


                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")
                {

                    look();
                }

                else

                    {
                    cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }



}

void final_room::look()
{
    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
        "A four coaster bed rests on the Eastern wall, facing a\n"
        "boarded up window.\n"
        "\n"
        "Posters advertising cross-Europe bus services litter the\n"
        "floor, and dark stains are splashed across the far left\n"
        "corner.\n"
        "\n"
        "Directly in front of you is a closet with partially \n"
        "unhinged doors.\n"
        "\n\n";

}

void final_room::set_objects(string obj [])
{
    obj[0] = "BED";
    obj[1] = "STAIN";
    obj [2] = "STAINS";
    obj [3] = "POSTER";
    obj [4] =  "POSTERS";
    obj [5] = "CLOSET";



}

void final_room::use_objects(string action, string item)
{
/************************************************
This first section is for interacting with the posters.
*************************************************/

    if (action == "EAT" && (item == "POSTER" || item == "POSTERS") )
        {
            cout << "\nYou could use the extra fiber in your diet.\n\n";
        }

    if (action == "TASTE" &&  (item == "POSTER" || item == "POSTERS") )
        {
            cout << "\nIt tastes rather bland.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") &&  (item == "POSTER" || item == "POSTERS") )
        {

                cout << "\nYou tear a poster to shreds....\n\n";
        }

    if (action == "OPEN" &&  (item == "POSTER" || item == "POSTERS") )
        {
            cout << "\nYou open a hole in the poster.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") &&  (item == "POSTER" || item == "POSTERS"))
        {
            cout << "\nYou don't want to take anything that might remind you again\nof that bus ride.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") &&  (item == "POSTER" || item == "POSTERS"))
        {
            cout << "\nYou give the posters a verbal beat-down.\n\n";
        }

    if (action == "TALK" &&  (item == "POSTER" || item == "POSTERS") )
        {
            cout << "\nThese posters don't seem to be interactive.\n\n";
        }

    if (action == "READ" &&  (item == "POSTER" || item == "POSTERS") )
        {
            cout << "\n\"Take a trip through scenic Europe by bus!\".\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") &&  (item == "POSTER" || item == "POSTERS"))
        {

            cout<< "\nIt is an advertisement for bus tours and services. One of these\nwas handed to you by a man at your hotel in Athens.";

        }
/************************************************
This second section is for interacting with the Bed.
*************************************************/

     if (action == "EAT" && item == "BED")
        {
            cout << "\nIt's tough and a a bit stale tasting.\n\n";
        }

    if (action == "TASTE" && item == "BED")
        {
            cout << "\nIt's tough and a a bit stale tasting.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "BED")
        {
            cout << "\nYour actions cause goose feathers to fly everywhere from the mattress.\n\n";
        }

    if (action == "OPEN" && item == "BED" )
        {
            cout << "\nThere is nothing but feathers inside the bed.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "BED")
        {
            cout << "\nYou really should get a truck to move the mattress with first.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "BED")
        {
            cout << "\nThe bed looks depressed now.\n\n";
        }

    if (action == "TALK" && item == "BED")
        {
            cout << "\nPerhaps you need a nap?\n\n";
        }

    if (action == "READ" && item == "BED")
        {
            cout << "\nNothing to read here.\n\n";
        }

    if (action == "USE" && item == "BED")
        {
            cout << "\nYou lay down and gather your thoughts.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "BED")
        {
            cout<< "\nA ratty mattress covered in claw marks and bleeding feathers sits\non an intricately carved frame. The four posters on the bed\nappear to have been gnawed on.\n\n";
        }

/************************************************
This third section is for interacting with the stain.
*************************************************/

    if (action == "EAT" && (item == "STAIN" || item == "STAINS") )
        {
            cout << "\nYou are hungry, but not THAT hungry.\n\n";
        }

    if (action == "TASTE" &&  (item == "STAIN" || item == "STAINS")  )
        {
            cout << "\nEven you would rather not go around licking mysterious stains.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") &&  (item == "STAIN" || item == "STAINS")  )
        {

                cout << "\nIt's soaked into the wall and floor- you can't get to it.\n\n";
        }

    if (action == "OPEN" &&  (item == "STAIN" || item == "STAINS")  )
        {
            cout << "\nIt's soaked into the wall and floor- you can't get to it.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") &&  (item == "STAIN" || item == "STAINS") )
        {
            cout << "\nIt's soaked into the wall and floor- you can't get to it.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") &&  (item == "STAIN" || item == "STAINS") )
        {
            cout << "\n\"BILLY MAYS IS COMING FOR YOU!!!!!\"\n\n";
        }

    if (action == "TALK" &&  (item == "STAIN" || item == "STAINS")  )
        {
            cout << "\nThese stains can't be reasoned or negotiated with.\n\n";
        }

    if (action == "READ" &&  (item == "STAIN" || item == "STAINS")  )
        {
            cout << "\n* is what is says\".\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") &&  (item == "STAIN" || item == "STAINS") )
        {

            cout<< "\nIs it blood? Something else? You'd rather not think about it.";

        }

    /************************************************
This fourth section is for interacting with the Closet.
*************************************************/

     if (action == "EAT" && item == "CLOSET")
        {
            cout << "\nYou chip a tooth- better knock that off.\n\n";
        }

    if (action == "TASTE" && item == "CLOSET")
        {
            cout << "\nIt tastes dusty.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "CLOSET")
        {
            cout << "\nThe closet door is already broken.\n\n";
        }


    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "CLOSET")
        {
            cout << "\nIt's attached to the wall.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "CLOSET")
        {
            cout << "\nThe monster in the closet is ignoring you.\n\n";
        }

    if (action == "TALK" && item == "CLOSET")
        {
            cout << "\nThe monster in the closet is ignoring you.\n\n";
        }

    if (action == "READ" && item == "CLOSET")
        {
            cout << "\nNothing to read here.\n\n";
        }


    if ((action == "EXAMINE" || action == "OPEN" || action == "USE" || action == "LOOK") && item == "CLOSET")
        {
            cout<< "\nOpening the closet's one unhinged door, you take a peek inside.\n";

            if (items.backpack[0] == 0)

            {

                cout<< "\nThe closet is mostly empty save for a large iron key on the ground.\nYou pick it up and put it in your pocket.\n\n"
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the IRON KEY\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n";



                items.backpack[0] = 1;
            }


            else

            {
                cout<<"\nThere is nothing left remaining in the closet.\n\n";
            }
        }



}

void final_room::goto_bedroom()

{

    int looping = 0;

    set_objects(bedroom_objects);

    while (looping == 0 )

    {

        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";


        cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "BEDROOM\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "SOUTH" || player.action == "S" )

            {


                        room_num = 4;

                        break;

            }

            else if (player.action == "NORTH" || player.action == "N" || player.action == "EAST" || player.action == "E" || player.action == "WEST" || player.action == "W")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;


                for (int j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                if (check_keyItems(player.object, key_items, items.arr_size))

                    {   cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object);
                    }


                else if(validate_object(player.object, bedroom_objects, arr_size))

                    {
                        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_objects(player.action, player.object);

                    }

                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM")

                    {

                        look();
                    }

                else

                    {
                        cout<< "\nI'm afraid that's not something you can interact with.\n";
                    }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }




}


void gar_den::look()
{

cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "You are in a small courtyard surrounded on all\n"
    "sides by high stone walls.\n"
    "\n"
    "The courtyard itself is fairly overgrown with\n"
    "weeds and wildflowers.A patch of dirt with \n"
    "vegetables lies on the west"
    "wall. \n\nIn the center of the courtyard is a stone\n"
    "fountain";
if (items.backpack[5] == 0 && garden.squeaky == 0) //if the player doesn't have the rabbit and the gate is not squeaky//
    {
        cout<< " with a rabbit sleeping under it.\n";
    }
else
{
    cout << ".\n";
}
cout<<
    "\nTo your south is an iron gate between the courtyard\n"
    "garden and a short path to the kitchen \n"
    "door.\n"
    "\n"
    "\n";





}

void gar_den::use_objects(string action, string item)

{

   /************************************************
This section is for interacting with the vegetables.
*************************************************/

     if (action == "EAT" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nYou eat some of the vegetables from the garden. They are both delicious \nand healthy!\n\n";
            player.change_health(-1);
        }

    if (action == "TASTE" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nThe vegetables are quite fresh and delicious.\n\n";
            player.change_health(-1);
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nYou splatter a tomato into the dirt.\n\n";
        }

    if (action == "OPEN" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nYou pull out a carrot and open it.\nThere is carrot inside.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && (item == "VEGETABLE" || item == "VEGETABLES"))
        {
            cout << "\nYou take a vegetable, but are so hungry that you\neat it right away.\n\n";
            player.change_health(-1);
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nYou've sunk to a new low.\n\n";
        }

    if (action == "TALK" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nThey say that talking to your plants makes them grow\nfaster.\n\n";
        }

    if (action == "READ" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nVegetables are brought to you by the letter 'V'.\n\n";
        }

    if (action == "USE" && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout << "\nYou have a bite of the nearest vegetable.\n\n";
            player.change_health(-1);
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && (item == "VEGETABLE" || item == "VEGETABLES") )
        {
            cout<< "\nThere is quite a large variety of vegetables here, from tomatoes to\ncelery.\n\n";
        }


/************************************************
This third section is for interacting with the fountain.
*************************************************/

      if (action == "EAT" && item == "FOUNTAIN")
        {
            cout << "\nThe stone fountain is not edible.\n\n";
        }

    if (action == "TASTE" && item == "FOUNTAIN" )
        {
            cout << "\nMossy with a hint of stone.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "FOUNTAIN")
        {
            cout << "\nYou injure your hands on the stone fountain.\n\n";
        }

    if (action == "OPEN" && item == "FOUNTAIN")
        {
            cout << "\nThere is nothing to open on the fountain.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "FOUNTAIN")
        {
            cout << "\nIt is too big and heavy.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "FOUNTAIN")
        {
            cout << "\nYou startle some birds perched on the wall with \nyour yelling.\n\n";
        }

    if (action == "TALK" && item == "FOUNTAIN")
        {
            cout << "\nYou make a wish.\n\n";
        }

    if (action == "READ" && item == "FOUNTAIN")
        {
            cout << "\nNothing is written on the fountain.\n\n";
        }

    if (action == "USE" && item == "FOUNTAIN")
        {
            cout << "\nThe fountain doesn't seem to be working\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "FOUNTAIN")
        {
            cout<< "\nThe fountain is made of a large pool with a stone fish\nshaped spout in the center. The water is not currently\nrunning, and the pool is filled with algae.\n\n";
        }

   /************************************************
This third section is for interacting with the gate.
*************************************************/

      if (action == "EAT" && item == "GATE")
        {
            cout << "\nAre you looking to add some...iron to your diet?.\n\n";
        }

    if (action == "TASTE" && item == "GATE" )
        {
            cout << "\nThe gate tastes metallic.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "GATE")
        {
            cout << "\nThe gate hold up to your blows.\n\n";
        }

    if (action == "OPEN" && item == "GATE")
        {
            cout << "\nYou open the gate, but a spring shuts \nit closed again.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "GATE")
        {
            cout << "\nIt is too big and heavy.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "GATE")
        {
            cout << "\nYou startle some birds perched on the wall with \nyour yelling.\n\n";
        }

    if (action == "TALK" && item == "GATE")
        {
            cout << "\n\"Hello Gate!\" \n\n";
        }

    if (action == "READ" && item == "GATE")
        {
            cout << "\nNothing is written on the gate.\n\n";
        }

    if (action == "USE" && item == "GATE")
        {
            cout << "\nYou open and close the gate.\n\n";
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "GATE")
        {
            cout<< "\nA rusty iron gate closes off the garden area.\nA spring in the hinge pops it back into place when opened.\n";

            if (squeaky == 1)

            {
                cout<<"\nThe gate is very squeaky. Perhaps you could fix it with\nsome oil...\n";
            }

            cout<< "\n";
        }

   /************************************************
This third section is for interacting with the rabbit.
*************************************************/

      if (action == "EAT" && item == "RABBIT")
        {
            if (items.backpack[5] ==1)

            {
                    cout<< "\nYou can't use the item in that way.\n\n";

            }


            else if (squeaky == 1)

                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {


                       cout << "\nBiting the rabbit only serves to make it angry.\nYour life ends in a flash of teeth and fluffy paws.\n\n";

                        cout<< "\n*****************************************" << endl
                        << "\nGAME OVER\n"
                        <<"*****************************************"<< endl << endl;
                        exit(1);

                }
        }

    if (action == "TASTE" && item == "RABBIT" )
        {

            if (items.backpack[5] ==1)

            {

                    cout<< "\nYou can't use the item in that way.\n\n";

            }

            else if (squeaky == 1)

                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {

                       cout << "\nBiting the rabbit only serves to make it angry.\nYour life ends in a flash of teeth and fluffy paws.\n\n";

                        cout<< "\n*****************************************" << endl
                        << "\nGAME OVER\n"
                        <<"*****************************************"<< endl << endl;
                        exit(1);

                }
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && item == "RABBIT")
        {

             if (items.backpack[5] ==1)
             {

                    cout<< "\nYou can't use the item in that way.\n\n";


             }

             else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {

                       cout << "\nAttacking the rabbit only serves to make it angry.\nYour life ends in a flash of teeth and fluffy paws.\n\n";

                        cout<< "\n*****************************************" << endl
                        << "\nGAME OVER\n"
                        <<"*****************************************"<< endl << endl;
                        exit(1);

                }
        }

    if (action == "OPEN" && item == "RABBIT")
        {
             if (items.backpack[5] ==1)

             {
                 cout << "\nYou can't use the item in that way.\n\n";

             }

             else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {

                       cout << "\nYou aren't a vet.\n\n";

                }
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP") && item == "RABBIT")
        {

             if (items.backpack[5] ==1)

             {
                 cout<<"\nYou can't use the item in that way.\n\n";

             }

            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                        cout << "\nYou pick up the rabbit. Amazingly it continues to\nsleep.\n\n";
                        "\n\n\n^^^^^^^^^^^^^^^^^^^^^^\n"
                        "You got the RABBIT\n"
                        "^^^^^^^^^^^^^^^^^^^^^^\n\n";

                        items.backpack[5] = 1;

                }


        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && item == "RABBIT")
        {
            if (items.backpack[5] ==1)

             {
                 cout<<"\nYou can't use the item in that way.\n\n";

             }


            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                    cout << "\nThe rabbit keeps on sleeping.\n\n";

                }

        }

    if (action == "TALK" && item == "RABBIT")
        {
            if (items.backpack[5] ==1)

             {
                 cout<< "\nYou can't use the item in that way.\n\n";

             }


            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                    cout << "\nThe rabbit keeps on sleeping.\n\n";

                }
        }

    if (action == "READ" && item == "RABBIT")
        {

          if (items.backpack[5] ==1)

             {
                 cout<< "\nYou can't use the item in that way.\n\n";

             }

            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                    cout << "\nThe rabbit keeps on sleeping despite your \nstory about the time you microwaved a fork.\n\n";

                }
        }

    if (action == "USE" && item == "RABBIT")
        {
            if (items.backpack[5] ==1)

             {
                    cout<<"\nWhat do you want to use that on?\n";

                    cin>> player.object;

                    cout<<"\nYou can't use the item in that way.\n\n";

             }

            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                    cout << "\nYou can't use that here.\n\n";

                }
        }

    if ((player.action =="LOOK" || player.action == "EXAMINE") && item == "RABBIT")
        {

            if (items.backpack[5] ==1)

             {
                 cout<< "\nA fluffy brown bunny lies asleep in your arms.\n\n";

             }


            else if (squeaky == 1)


                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n\n";
                }

            else

                {
                    cout << "\nA fluffy brown bunny lies asleep at the base of the\nfountain. Every now and then it give a twitch of its nose.\n\n";

                }
        }


}

void gar_den::set_objects(string obj [])
{

    obj[0] = "GATE";
    obj[1] = "RABBIT"; //Big syntax error: Spelled "Rabiit" instead of "Rabbit"....this led to a lot of confusion//
    obj [2] = "FOUNTAIN";
    obj [3] = "VEGETABLE";
    obj [4] = "VEGETABLES";
}

void gar_den::oil_gate ()
{
    squeaky = 0;
}

void gar_den::goto_garden()

{
    int j; //for looping LOCAL ONLY Requirement #12//
    int looping = 0;
    int repeat_prevention = 0;

    set_objects(garden_objects);

    if (squeaky ==1)

    {

        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

        cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
                "COURTYARD\n"
                "^^^^^^^^^^^^^^^^^^^^^^\n"
                "\n";

        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
        cout<< "\n\nRight after exiting the kitchen you find yourself\nopening a small iron gate to enter a courtyard\ngarden. It creaks loudly, causing something in the garden to\nscamper away.\n\n";
    }

    while (looping == 0 )

    {
       int repeat_prevention = 0; //prevents the last section of code from repeating//
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "Courtyard\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "SOUTH" || player.action == "S" )

            {
                        cout<< "\nYou head " << player.action<<  ".\n";

                        room_num = 3;

                        if (oil ==1)

                        {
                            oil_gate();
                        }

                        break;

            }

            else if (player.action == "NORTH" || player.action == "N" || player.action == "EAST" || player.action == "E" || player.action == "WEST" || player.action == "W")
            {
                cout << "\nYou can't go that direction\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                if ( (check_keyItems(player.object, key_items, items.arr_size)) && (player.object!= "RABBIT") )

                    {
                       if  (player.object == "SOUP" && items.backpack[6] == 1 && player.action == "USE" )

                            {
                                cout<<"\nWhat do you want to use that on?\n";

                                cin>> player.object;

                                for (j = 0; j < player.object.length(); j++)

                                    {
                                        player.object.at(j) = toupper(player.object.at(j));
                                    }


                                if (player.object == "GATE")

                                    {
                                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                        cout<<"\nYou pour some of the soup onto the gate hinge.\nThe oily soup seems to have lubricated it.\n\n";

                                        oil = 1;

                                        repeat_prevention = 1;
                                    }
                                else

                                {
                                   cout<< "\nYou can't use the item in that way.\n\n";
                                   repeat_prevention = 1;
                                }

                            }

                        else

                            {
                                cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                use_keyItems(player.action, player.object);
                                repeat_prevention = 1;
                            }
                    }


                if (((validate_object(player.object, garden_objects, arr_size)) || player.object== "RABBIT") && repeat_prevention == 0)

                {
                    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    use_objects(player.action, player.object);

                }


                else if ((player.action =="LOOK" || player.action == "EXAMINE") && player.object == "ROOM" && repeat_prevention == 0)
                {

                    look();
                }

                else if (repeat_prevention !=1)
                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n";
                }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }

    }

}


void werewolf::wolf_intro()
{
 char temp;

    cout<< "\n\n\n"
           "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
           "You slowly push open the locked door and step \n"
            "inside. \n"
            "\n"
            "the first thing that catches your eye is a\n"
            "clipboard on the floor. It looks very familiar\n"
            "somehow...you bend down and pick it up to examine.\n"
            "\n"
            "The clipboard has the logo of the bus tour company\n"
            "you were riding on it. A list of names shows who\n"
            "was on board with check marks next to each one...\n\n"
            "Each one that is, except for a name circled in red:\n"
            "\n\"";

            player.player_name();

            cout <<"\"\n\n"
            "\n\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');


    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
            "*DRIP* *DRIP*\n"
            "\n"
            "Something from above you is leaking onto the list.\n"
            "You look up to see where it is coming from, only to \n"
            "get some liquid in your eye along with a blast of hot air.\n"
            "\n"
            "Cringing, you rub your eyes before lifting up your \n"
            "lantern again to get a better look."
            "\n\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    cout <<"\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "The first thing you notice are the eyes.\n"
    "\n"
    "Shining a good two feet above you,\n"
    "the thing's eyes glow a pale yellow reflected\n"
    "in the light as it looks down on you hungrily.\n"
    "\n"
    "Silva drips from its long white fangs, and hisses\n"
    "as it falls onto the surface of the lantern. \n"
    "\n"
    "Time seems frozen for a moment...then the\n"
    "great beast lets out a mournful howl\n"
    "that freezes you to the spot and sends chills \n"
    "through your spine.\n"
    "\n"
    "\n"
    "Of all the spooky European forest cliches,\n"
    "it had to be  werewolves."

    "\n\n<ENTER ANY KEY TO CONTINUE>\n";

    cin>> temp;

    cin.ignore(10000, '\n');

    been_there_done_that == 1;


}

void werewolf::use_keyItems(string action, string item, int wolf)

{
      int j; //local variable for loop//


/************************************************
For the tankard.
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if ( action == "USE" &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {
                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                            {
                                        player.object.at(j) = toupper(player.object.at(j));
                            }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {

                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<<"\nThe wolf doesn't seem thirsty, and hitting\nit with the tankard seems to have no effect.\n\n";

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }


                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "TANKARD")

         {

             if (items.backpack[4] ==1 )
                {

                   cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a pewter tankard with an ornate engraving of a deer in a forest.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the Keys
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "KEY")
        {
            if (items.backpack[0] == 1 || items.backpack[1] == 1 )

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "KEY")

         {

             if (items.backpack[0] == 1 || items.backpack[1] == 1 )
                {
                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {

                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<<"\nYou throw the key at the werewolf, but it bounces harmlessly\noff its skull.\n\n";

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "KEY")

         {

             if (items.backpack[0] == 1 || items.backpack[1] == 1 )
                {


                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt looks like a key alright...\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the fork.
*************************************************/

     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "FORK")
        {
            if (items.backpack[2] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }



     if (  action == "USE" &&  item == "FORK")

         {

             if (items.backpack[2] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {


                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<<"\nYou stab at the werewolf, but it just snarls and\nand bats you aside.\n\n";

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "FORK")

         {

             if (items.backpack[2] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a large fork made of silver.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the Lantern
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "LANTERN")
        {
            if (items.backpack[3] == 1)

                {
                    cout<< "\nNow is not the time to use that item.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "LANTERN")

         {

             if (items.backpack[3] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;


                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {

                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<< "\nYou yell while wildly swinging the lantern in front of you.\nIt isn't helping.\n\n";

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }


                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "LANTERN")

         {

             if (items.backpack[3] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nIt is a gas lantern that gives off a soft glow.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the rabbit
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "RABBIT")
        {
            if (items.backpack[5] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "RABBIT")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {


                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<< "\nPanicking and desperate, you throw the sleeping rabbit at the werewolf.\n"
                                    "The rabbit spins through the air before plopping on the werewolf's\nface.\n\nAt first nothing happens...then the rabbit's beady black \neyes shoot open, filled with rage.\n\n"

                                    "Biting and tearing, the rabbit scurries down the wolf and onto the floor.\nit nimbly darts to and fro, avoiding the bites and grabs of the\nwerewolf while lashing out with its small teeth like tiny knives in\nthe dark.\n"
                                    "\nThe werewolf seems to have its hands full.\n\n";

                                    distracted = 1;

                                    items.backpack[5] = 0;

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }


                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  item == "RABBIT")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nA fluffy brown bunny lies asleep in your arms.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }
/************************************************
For the musket
*************************************************/
     if ( (action == "EAT" || action == "TASTE" || action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  (item == "GUN" || item == "MUSKET") )
        {
            if (items.backpack[7] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }

     if (  action == "USE" &&  item == "GUN" || item == "MUSKET")

         {

             if (items.backpack[7] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {

                            if (distracted == 0)
                            {
                               cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                                cout<< "\nYou try and lift the musket to fire, but the werewolf is\ntoo quick and knocks you over; snapping at your throat.\n\nIf only you had something to distract the werewolf with...\n\n";
                            }

                            else
                            {

                               cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                               victory();

                            }

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }


                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if (  (player.action =="LOOK" || player.action == "EXAMINE") &&  (item == "GUN" || item == "MUSKET"))

         {

             if (items.backpack[7] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nAn old hunting musket filled with powder and a fork.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }

/************************************************
For the soup
*************************************************/
     if ( (action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT" || action == "OPEN"|| action == "TAKE" || action == "PICK" || action == "PICKUP"  || action == "INSULT" || action == "HARASS" || action == "YELL" || action == "TALK" || action == "READ") &&  item == "SOUP")
        {
            if (items.backpack[5] == 1)

                {
                    cout<< "\nYou can't use the item in that way.\n\n";
                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }

        }


     if ( action == "USE" &&  item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\nWhat do you want to use it on?\n\n";

                    cin>>player.object;

                    for (j = 0; j < player.object.length(); j++)

                    {
                        player.object.at(j) = toupper(player.object.at(j));
                    }

                    if (player.object == "WOLF" || player.object == "WEREWOLF")


                        {


                            cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                            cout<< "\nYou offer a bit of soup to the werewolf. It pauses\nfor a moment as if confused, then growls.\n\n";

                        }

                    else

                        {
                            cout<< "\nYou can't use the item in that way.\n\n";
                        }


                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }


     if ( (action == "EAT" || action == "TASTE") &&  item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nYou take a sip of the soup. It is a bit oily,\n but otherwise not too bad.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }



     if ( (player.action =="LOOK" || player.action == "EXAMINE") && item == "SOUP")

         {

             if (items.backpack[5] == 1)
                {

                    cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                    cout<< "\nThe soup is filled with meat and a few vegetables. \nIt looks really oily and is still lukewarm.\n\n";

                }

            else

                {

                    cout<< "\nI'm afraid that's not something you can interact with.\n";

                }
         }





}


void werewolf::use_objects(string action, string item)
{

/************************************************
This is for interacting with the werewolf using normal objects.
*************************************************/

    if (action == "EAT" && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout << "\nDoes eating a werewolf make you a cannibal? \nThe ethical questions of the situation prevent you from\neating the werewolf.\n\n";
        }

    if (action == "TASTE" && (item == "WOLF" || item == "WEREWOLF")  )
        {
            cout << "\nYou can't get close enough to taste it.\n\n";
        }

    if ((action == "ATTACK" || action == "KILL" || action == "PUNCH" || action == "BREAK" || action == "HIT") && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout<< "\nYou attack the werewolf, but your blows\nseem to be annoying rather than hurting it.\n\n";
        }

    if (action == "OPEN" && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout << "\nYou can't do that.\n\n";
        }

    if ((action == "TAKE" || action == "PICK" || action == "PICKUP" || action == "USE") && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout << "\nYou don't need a new pet.\n\n";
        }

    if ((action == "INSULT" || action == "HARASS" || action == "YELL") && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout << "\n\"BAD WOLF! BAD, BAD WOLF! YOU GO HOME!\" you shout.\n\nThe werewolf ignores your comments as it does not appear trained.\n\n";
        }

    if (action == "TALK" && (item == "WOLF" || item == "WEREWOLF")  )
        {
            cout << "\nReasoning with the werewolf fails...\n\n";
        }

    if (action == "READ" && (item == "WOLF" || item == "WEREWOLF") )
        {
            cout << "\nYou can't read the werewolf.\n\n";
        }


    if ( (player.action =="LOOK" || player.action == "EXAMINE") && (item == "WOLF" || item == "WEREWOLF")  )
        {

            cout << "\nThe hulking werewolf towers over you. It is\nalmost eight feet of pure fur, muscle, and claws.\nDespite its beastly exterior you sense a wicked \nintelligence behind its eyes.\n\n";

        }





}


void werewolf::victory()
{
    cout<<"\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n"
    "With the rabbit still in a blood-frenzy keeping\n"
    "the werewolf busy, you take aim and fire the\n"
    "musket.\n"
    "\n"
    "With a loud bang, whine, and flash of gunpowder,\n"
    "the deed is done. \n"
    "\n"
    "You lower the musket.\n"
    "\n"
        "The rabbit has run off, but werewolf lies on the\n"
    "ground dead...pierced by the silver fork. \n\nBefore you can"
    "get too relived however, you\nhear another"
    "howl echoing from somewhere inside the house \nsouth of you.\n"
    "\n"
    "\n"
    "...You have to get out of here, fast.";

    silver_bullet = 1;
    dont_go_in_the_basement = 1;


}


void werewolf::defeat()
{
        cout << "\nThe werewolf strikes a fatal blow, raking you across\nthe chest with dagger-like claws. Your last living memory\nis of its teeth closing around your neck...\n\n";

        cout<< "\n*****************************************" << endl
        << "\nGAME OVER\n"
        <<"*****************************************"<< endl << endl;
        exit(1);



}

void werewolf::therewolf()
{

    int looping = 0;


    if (been_there_done_that == 0)

        {
            wolf_intro();

            been_there_done_that = 1;
        }


    while (looping == 0 )

    {
        cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

            cout << "^^^^^^^^^^^^^^^^^^^^^^\n"
            "YOU ARE BEING ATTACKED\n"
            "^^^^^^^^^^^^^^^^^^^^^^\n"
            "\n";

        cout<< "\nEnter a command:\n";

        cin>> player.action;

        if (validate_com(player.action, valid_words))

        {
            if (player.action == "SOUTH" || player.action == "S" )

            {
                cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                cout<<"\nThe wolf savagely attacks, causing you injury.\n\n";
                player.change_health(1);
                cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                cout<< "You just barely escape, locking the door behind you.\n\n";
                room_num = 4;

                break;
            }

            if ( player.action == "WEST" || player.action == "W" || player.action == "EAST" || player.action == "E" || player.action == "NORTH" || player.action == "N" )

            {
                cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                cout << "\nThe werewolf leaps in front of you to block your path.\n\n";
            }

            else
            {
                cout << "\nWhat do you want to do that to?\n";

                cin>> player.object;

                if (check_keyItems(player.object, key_items, items.arr_size) )

                    {
                        cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
                        use_keyItems(player.action, player.object, 8);
                    }


                else if(validate_object(player.object, wolf_objects, 2))
                {

                    cout << "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";

                    use_objects(player.action, player.object);

                }
                else
                {
                    cout<< "\nI'm afraid that's not something you can interact with.\n";
                }

            }
        }

        else
        {
            cout<< "\nI'm afraid I don't know what you mean\n";
        }


        if (silver_bullet ==1)

        {
            room_num = 7;
            break;
        }

        else
        {

           cout<< "\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n\n";
           cout<<"\nThe wolf savagely attacks, causing you injury.\n\n";
            player.change_health(1);
        }

    }






}




