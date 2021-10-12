/*
    Scancode reference (set2 - IBM Personal Computer/AT): https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
*/
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include <conio.h>

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DEL 0x53 //DEl key 
#define KEY_BACKSPACE 0x0e

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
    std::getline(std::cin, a);
    std::list<char> l;
    for (int i = 0; i < a.length(); i++)
    {
        l.push_back(a.at(i));
    }
    l.push_back('^');
    printList(l);
    char key, c;
    while ((key = _getch()) != 27)  //27  is Escape
    {
        if (key == -32) //-32 (0xE0) is the fist scancode for special keys
        {
            switch(c = _getch())
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
                // case KEY_BACKSPACE:
                //     bspace(l);
                //     break;
            }

        }
        else
        {
            if(key == 8)
            {
                bspace(l);
            }
            if (key >= 32 && key <= 126)  // If key is from SPACEBAR to ~
            {
                insert(l, key);
            }
        }
        // switch (key)
        // {
        //     case KEY_LEFT:
        //         moveleft(l);
        //         break;
        //     case KEY_RIGHT:
        //         moveright(l);
        //         break;
        //     case KEY_DEL:
        //         del(l);
        //         break;
        //     default:
        //         if (key >= 32 && key <= 126)  // If key is from SPACEBAR to ~
        //         {
        //             insert(l, key);
        //         }
        //         break;
        // }
    }
}

void moveleft(std::list<char> &l)
{
    auto cursor_old = std::find(l.begin(), l.end(), '^');

    // check if end of list is reached
    if (cursor_old == l.begin())
        return;

    auto cursor_new = std::find(l.begin(), l.end(), '^');
    l.splice(--cursor_old, l, cursor_new);  //move the cursor to the left by one character
    printList(l);

}

void moveright(std::list<char> &l)
{
    auto cursor_old = std::find(l.begin(), l.end(), '^');

    //check if beginning of list is reached
    if (++cursor_old == l.end())
        return;

    auto cursor_new = std::find(l.begin(), l.end(), '^');
    ++cursor_old;
    l.splice(cursor_old, l, cursor_new);  //move the cursor to the right by one character 
    printList(l);
}

void del(std::list<char> &l)
{
    auto cursor = std::find(l.begin(), l.end(), '^');
    if (++cursor == l.end())
        return;

    l.erase(cursor);
    printList(l);
}

void bspace(std::list<char> &l)
{
    auto cursor = std::find(l.begin(), l.end(), '^');
    if (++cursor == l.end())
        return;

    --cursor;
    --cursor;
    l.erase(cursor);
    printList(l);
}

void insert(std::list<char> &l, char a)
{
    auto cursor = std::find(l.begin(), l.end(), '^');
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