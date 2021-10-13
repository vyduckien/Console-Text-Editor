/*
    Textbook - Project P-6.3, Chapter 6 Textbook, Page 266
    Write a simple text editor, which stores a string of characters using the list ADT, 
    together with a cursor object that highlights the position of some
    character in the string (or possibly the position before the first character).
    Your editor should support the following operations and redisplay the current text (that is, the list) after 
    performing any one of them.
        • left: Move cursor left one character (or nothing if at the beginning)
        • right: Move cursor right one character (or do nothing if at the end)
        • delete: Delete the character to the right of the cursor (or do nothing
        if at the end)
        • insert c: Insert the character c just after the cursor

    Scancode reference (set2 - IBM Personal Computer/AT): https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
        Example: when Left arrow key is pressed, the following 2-byte scancode is passed into the computer: 0xE0 0x4B
    The auto keyword specifies that the type of the variable that is being declared will be 
    automatically deducted from its initializer.
    Date: 9/2021
*/

#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include <conio.h>

#define KEY_LEFT 0x4B
#define KEY_RIGHT 0x4D
#define KEY_DEL 0x53 
#define KEY_BACKSPACE 0x0E
#define tcurse  '|' //symbol for the text cursor

/* move the cursor to the left by one character */
void moveleft(std::list<char> &l);

/* move the cursor to the right by one character */
void moveright(std::list<char> &l);

/* delete one character to the right of the cursor */
void del(std::list<char> &l);

/* delete one character to the left of the cursor */
void bspace(std::list<char> &l);

/* insert one character to the left of the cursor */
void insert(std::list<char> &l, char a);

/* print the list */
void printList(std::list<char> l);

int main()
{
    std::string a;
    std::cout << "Enter string: ";
    std::getline(std::cin, a); //use getline so that space will not be ignored
    std::list<char> l;
    for (int i = 0; i < a.length(); i++)
    {
        l.push_back(a.at(i));
    }
    l.push_back(tcurse);
    printList(l);
    char key, c;
    while ((key = getch()) != 27)  //27  is Escape, _getch() is to read a single-byte character
    {
        if (key == -32) //-32 (0xE0) is the fist scancode for special keys.
        {
            switch(key = getch())   //read the next scancode
            {
                case KEY_LEFT:
                    moveleft(l);
                    break;
                 case KEY_RIGHT:
                    moveright(l);
                    break;
                case KEY_DEL:
                    del(l);
                    break;
            }
        }
        else
        {
            if(key == 8)    //Delete character to the left of the cursor with Backspace
                bspace(l);
            if (key >= 32 && key <= 126)  //If key input is from SPACEBAR to ~ in the ASCII table
                insert(l, key);
        }
    }
}

void moveleft(std::list<char> &l)
{
    auto cursor_old = std::find(l.begin(), l.end(), tcurse);    //find the current cursor position

    // check if end of list is reached
    if (cursor_old == l.begin())
    {
        printList(l);
        return;
    }
    auto cursor_new = std::find(l.begin(), l.end(), tcurse);
    l.splice(--cursor_old, l, cursor_new);  //move the cursor to the left by one character
    printList(l);
}

void moveright(std::list<char> &l)
{
    auto cursor_old = std::find(l.begin(), l.end(), tcurse);    //find the current cursor position

    //check if beginning of list is reached
    if (++cursor_old == l.end())
    {
        printList(l);
        return;
    }
    auto cursor_new = std::find(l.begin(), l.end(), tcurse);
    ++cursor_old;
    l.splice(cursor_old, l, cursor_new);  //move the cursor to the right by one character 
    printList(l);
}

void del(std::list<char> &l)
{
    auto cursor = std::find(l.begin(), l.end(), tcurse);    //find the current cursor position

    //check if the cursor is at the end of list
    if (++cursor == l.end()) 
    {
            printList(l);

        return;
    }
    l.erase(cursor);    //cursor now points to the character to the right of the text cursor
    printList(l);
}

void bspace(std::list<char> &l)
{
    auto cursor = std::find(l.begin(), l.end(), tcurse);    //find the current cursor position

    //check if the cursor is at the end of list
    if (cursor == l.begin())
        return;
    l.erase(--cursor);  //cursor now points to the character to the left of the text cursor
    printList(l);
}

void insert(std::list<char> &l, char a)
{
    auto cursor = std::find(l.begin(), l.end(), tcurse);    //find the current cursor position
    l.insert(cursor,a); 
    printList(l);
}

void printList(std::list<char> l)
{
    for (std::list<char>::iterator it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
}