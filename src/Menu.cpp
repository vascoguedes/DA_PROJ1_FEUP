#include "../include/Menu.h"

#include <sstream>
#include "iostream"

using namespace std;

Menu::~Menu() = default;

Menu::Menu(App &app): app(app) {}

int Menu::readInt() {
    int opt;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> opt;
        if(!ss.fail() && ss.eof() && opt>=0) break;
        cout << "Invalid input. Try a valid integer..." << endl;
    }
    cout << endl;
    return opt;
}

void Menu::waitForKey() {
    string str;
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, str);
}

std::string Menu::readStr() {
    string str,ret;
    cout << ": ";
    getline(cin, str);
    for(char &c : str){
        ret += toupper(c);
    }
    return ret;
}

Menu *Menu::invalidInput() {
    cout << "Invalid input option!" << endl;
    return this;
}

MainMenu::MainMenu(App &app): Menu(app){}

void MainMenu::display(){
    cout << endl;
    cout << "Main Menu:" << endl;
    cout << "1 - Scenery 1" << endl;
    cout << "2 - Scenery 2" << endl;
    cout << "3 - Scenery 3" << endl;
    cout << "4 - Options Menu" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MainMenu::nextMenu() {
    switch (readInt()) {
        case 1: return new Scenery1(app);
        case 2: return new Scenery2(app);
        case 3: return new Scenery3(app);
        case 4: return new OptionsMenu(app);
        case 0: return nullptr;
        default: return invalidInput();
    }
}

OptionsMenu::OptionsMenu(App &app) : Menu(app) {

}

void OptionsMenu::display() {
    cout << endl;
    cout << "Options Menu:" << endl;
    cout << "1 - Option 1" << endl;
    cout << "2 - Option 2" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *OptionsMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            return this;
        }
        case 2:{
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

Scenery1::Scenery1(App &app) : Menu(app) {

}

void Scenery1::display() {
    cout << endl;
    cout << "Options Menu:" << endl;
    cout << "1 - Execute" << endl;
    cout << "2 - Show Data" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *Scenery1::nextMenu() {
    switch (readInt()) {
        case 1: {
            return this;
        }
        case 2:{
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

Scenery2::Scenery2(App &app) : Menu(app) {

}

void Scenery2::display() {
    cout << endl;
    cout << "Options Menu:" << endl;
    cout << "1 - Execute" << endl;
    cout << "2 - Show Couriers" << endl;
    cout << "3 - Show Packages" << endl;
    cout << "4 - Normal Packages" << endl;
    cout << "5 - Reverse Packages" << endl;
    cout << "6 - Show shipments" << endl;
    cout << "7 - Unload shipments" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *Scenery2::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << app.scenery2() << endl;
            return this;
        }
        case 2: {
            app.printCouriers();
            return this;
        }
        case 3: {
            app.printPackages();
            return this;
        }
        case 4: {
            app.sortPackages(true);
            return this;
        }
        case 5: {
            app.sortPackages(false);
            return this;
        }
        case 6: {
            app.printShipments();
            return this;
        }
        case 7: {
            app.unloadShipments();
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

Scenery3::Scenery3(App &app) : Menu(app) {

}

void Scenery3::display() {
    cout << endl;
    cout << "Options Menu:" << endl;
    cout << "1 - Execute" << endl;
    cout << "2 - Show Data" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *Scenery3::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << app.scenery3() << endl;
            return this;
        }
        case 2:{
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

