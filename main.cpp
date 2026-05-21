#include <windows.h>

#include "cli.h"


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Cli app = Cli();

    app.Run();
    
}
