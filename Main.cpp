#include "Main.h"
#include "MinHook.h"
#include "libzippp.h"
#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#define str std::string
#define s std::to_string

#define INFO logs << "[Info] "
#define ERROR logs << "[Error] "
#define WARNING logs << "[Warning] "


std::ofstream logs;



////////////////////////////////////////////////////////////////////
/////// UTILITIES //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


/* True if file exists, otherwise false */
bool fexists(char * path) {
    if (auto file = fopen("demo.txt", "r")) {
        fclose(file);
        return true;
    }
    return false;
}

/* This will show a popup message and block execution, until user clicks OK. */
void say(str message, LPCWSTR header = L"Message") {
    MessageBoxW(0, std::wstring(message.begin(), message.end()).c_str(), header, 0);
}



///////////////////////////////////////////////////////////////////
///////// GAME LOGIC //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


class Creature {
    public: 
    char has_ability(int ability_a2) {
        return 1;
    }
};



////////////////////////////////////////////////////////////////////
///////// HOOKING //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


/* Replaces a function in H5.exe with given function at given offset. */
template <typename Fn> int hook(Fn function, int offset) {
    auto address = (void*)offset;
    auto created = MH_CreateHook(address, (void *&)function, NULL);
    auto enabled = MH_EnableHook(address);
    if (created != MH_OK) {
        ERROR << "Create Hook: Code " << created << ", Offset: 0x" << std::hex << offset << std::endl;
        return created;
    }
    if (enabled != MH_OK) {
        ERROR << "Enable Hook: Code " << enabled << ", Offset: 0x" << std::hex << offset << std::endl;
    }
    return enabled;
}

void hookFunctions() {
    // Example of calling function from H5.exe:
    auto mightWeek = (int (__fastcall *)(int, int))0x00A356A0;
    INFO << "Calling Week of Might: " << mightWeek(10, 0x49) << std::endl;

    // Example of replacing a function in H5.exe:
    //hook(test, 0xd12160);
    hook(&Creature::has_ability , 0x8DB6F0);
}

void hookVariables() {
    // Example of reading a constant from H5.exe:
    auto chillBones = (float *)0x00E09FC4;
    INFO << "The value of Chilling Bones is: " << *chillBones << std::endl;
    //*chill_bones = 0.5f; // this will crash the game, as the value is used at multiple places

    // Example of setting a constant from H5.exe:
    auto bulb = (float *)0xF33BC0;
    *bulb = 1.0;
}



/////////////////////////////////////////////////////////////////////
///////// MAIN FUNCTION /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


void main() {
    // INITIALIZATION
    logs.open("H5x.log");
    INFO << "H5x.dll loaded!" << std::endl;

    MH_Initialize();

    hookVariables();
    hookFunctions();


    // Example of reading the content .pak files.
    if (!fexists("../data/test.pak")) {
        ERROR << "data/test.pak does not exist!";
        return;
    }

    libzippp::ZipArchive data("../data/test.pak");
    data.open(libzippp::ZipArchive::ReadOnly);

    data.getEntry("test.txt").readAsText();

    auto config = data.getEntry("text.xdb");
    if (config.isNull()) {
        ERROR << "data/test.pak/test.xdb does not exist!";
        return;
    }

    pugi::xml_document doc;

    doc.load_string(config.readAsText().c_str());

    INFO << doc.first_child().name() << std::endl;
    INFO << doc.first_child().first_child().name() << std::endl;
    INFO << doc.first_child().first_child().child_value() << std::endl;

    INFO << doc.child("hello").child("world").child_value() << std::endl;

    data.close();
}