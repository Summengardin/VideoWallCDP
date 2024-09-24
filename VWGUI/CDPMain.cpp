#include <CDPStarter.h>
#include <Libraries.h>
#include <QApplication>

/*!
DO NOT MODIFY - ONLY FOR ADVANCED USERS FOR VERY SPECIFIC TASKS.
IF YOU ARE NEW TO CDP STUDIO, GO TO HELP AND READ: A GETTING STARTED GUIDE.

This is the entry-point for the application.

It starts the CDP application, which uses the configuration along with the linked libraries
to generate and configure the application based on the configuration.

To edit the configuration, use Configure mode to add/remove/configure existing CDP objects.
To create a new CDP object, create a library (from Welcome mode) and write your logic into a component,
so it becomes a reusable resource for your system.
*/

int main (int argc, char* argv[])
{
    int ret = 0;
    QApplication app(argc, argv);
    CDPStarter CDPMain(argc, argv);
    if (!CDPMain.hasArgument("--help"))
    {
        printf("This application is based in part on the work of the Qt framework licensed under LGPL v2.1 and LGPL v3.0.\n");
        printf("For full licenses, see files 'LICENSE.LGPLv21' and 'LICENSE.LGPLv3' in application directory.\n");
        ret = CDPMain.Start();
        printf("Good Bye!\n");
    }
    else
        CDPMain.PrintHelp();

    return ret;
}
