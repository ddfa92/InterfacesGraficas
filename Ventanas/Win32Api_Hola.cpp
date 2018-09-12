#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, //ID para la aplicación que es interpretado por el SO
                   HINSTANCE pInstance, //No en uso
                   LPSTR pCmdLine,      //Command line Arguments
                   int nCmdShow)
{
    MessageBox(NULL,"HELLO","My first GUI",MB_OK);
    return 0;
}
