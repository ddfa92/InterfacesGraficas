#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdlib.h>
#include <wchar.h>

#define MENU_ARCHIVO_NUEVO 1
#define MENU_ARCHIVO_ABRIR 2
#define MENU_ARCHIVO_SALIR 3
#define CAMBIAR 4

LRESULT CALLBACK Procedimientos(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND); //Función para agregar menus
void AddControls(HWND);
void loadImages();

HMENU hMenu; //definimos manejador de ventanas
HWND hName;
HWND hAge;
HWND hOut;
HWND hTablero;
HBITMAP hImagenTablero;


int WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPrevInst,
                   LPSTR pCmdLine,
                   int nCmdShow)
{

    const wchar_t NOMBRE_DE_CLASE[] = L"miClaseDeVentana";

    WNDCLASSW wc= { }; //Es una estructura, la estamos inicializando

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ; //define el color de fondo de la ventana
    wc.hCursor = LoadCursor(NULL,IDC_ARROW); //carga el cursor
    wc.hInstance = hInst;

    wc.lpszClassName = NOMBRE_DE_CLASE; //Nombre de la clase de esta ventana
    wc.lpfnWndProc = Procedimientos; //Nombre de la función que nos manejará los mensajes

    if (!RegisterClassW(&wc))
        return -1;
    //              TIPO DE VENTANA, TITULO, ESTILO, POSICION X, POSICION Y, TAMAÑO X, TAMAÑO Y,
    CreateWindowW(NOMBRE_DE_CLASE, L"El titulo", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100,100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = { }; //inicializa un mensaje

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK Procedimientos(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {

        case WM_COMMAND:
            switch(wp){
            case MENU_ARCHIVO_SALIR:
                DestroyWindow(hWnd);
                break;
            case MENU_ARCHIVO_NUEVO:
                MessageBeep(MB_OK);
                break;
            case CAMBIAR:
                wchar_t name[30], age[10], out[50]=L"";
                GetWindowText(hName, name,30);
                GetWindowText(hAge, age,10);
                wcscat(out,name);
                wcscat(out,L" tiene ");
                wcscat(out,age);
                wcscat(out,L" anios.");
                SetWindowText(hOut, out);
                break;
            }
            break;

        case WM_CREATE:
            loadImages();
            AddMenus(hWnd);
            AddControls(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }//end switch
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    //          Manejador, Tipo de menu, Identificador(para los mensajes, parametro wp), Título del menu

    HMENU hMenuArchivo = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING,NULL, L"Item de submenu");

    //Menu Archivo
    AppendMenu(hMenuArchivo, MF_STRING, MENU_ARCHIVO_NUEVO, L"Nuevo");
    AppendMenu(hMenuArchivo, MF_POPUP, (UINT_PTR)hSubMenu, L"Abrir");
    AppendMenu(hMenuArchivo, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hMenuArchivo, MF_STRING, MENU_ARCHIVO_SALIR, L"Salir");

    //Barra de menú
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenuArchivo, L"Archivo");
    AppendMenu(hMenu, MF_STRING, NULL, L"Ayuda");
    SetMenu(hWnd, hMenu);
}

//Funcion para los controles Estáticos y Editables, ventanas hijas
void AddControls(HWND hWnd)
{
    CreateWindowW(L"Static",L"Nombre:",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 100,50,100,20,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Edad:",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 100,75,100,20,hWnd,NULL,NULL,NULL);
    hName= CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL ,300,50,100,20, hWnd, NULL, NULL, NULL);
    hAge= CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL ,300,75,100,20, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Button",L"Asignar", WS_VISIBLE | WS_CHILD, 200,100,100,20, hWnd, (HMENU)CAMBIAR, NULL, NULL);
    hOut=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL ,100,125,300,200, hWnd, NULL, NULL, NULL);
    hTablero =CreateWindowW(L"Static",NULL,WS_VISIBLE | WS_CHILD | SS_BITMAP, 100,75,100,20,hWnd,NULL,NULL,NULL);
    SendMessage(hTablero,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM) hImagenTablero);
}   //WS : Window Style, SS: Static Style, ES: Edit Style


void loadImages()
{
    hImagenTablero = (HBITMAP)LoadImageW(NULL, L"tablero.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
}
