#ifndef DA_PROJ1_FEUP_MENU_H
#define DA_PROJ1_FEUP_MENU_H

#include <string>
#include "App.h"

class Menu {
protected:
    App &app;
public:
    /**
     * Class constructor with an application object
     * @param app application object passed by reference
     */
    explicit Menu(App &app);
    /**
     * Class destructor to clear the object in memory
     */
    virtual ~Menu();
    /**
     * Displays the menu in the terminal
     */
    virtual void display()=0;
    /**
     * Gets a menu pointer to the next menu after this one
     * @return menu pointer
     */
    virtual Menu *nextMenu()=0;
    /**
     * Reads an integer number input from the terminal
     * @return integer number read
     */
    int readInt();
    /**
     * Reads a string input from the terminal
     * @return string read
     */
    std::string readStr();
    /**
    * Waits for enter key to be pressed
    */
    void waitForKey();
    /**
     * If there was an invalid input prints a message and returns a pointer the a current menu
     * @return menu pointer
     */
    Menu *invalidInput();
};

class MainMenu: public Menu{
public:
    explicit MainMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

#endif //DA_PROJ1_FEUP_MENU_H
