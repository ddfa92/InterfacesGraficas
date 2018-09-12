#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdlib.h>

#define MENU_ARCHIVO_NUEVO 1
#define MENU_ARCHIVO_ABRIR 2
#define MENU_ARCHIVO_SALIR 3
#define CAMBIAR_TITULO 4

LRESULT CALLBACK Procedimientos(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND); //Función para agregar menus
void AddControls(HWND);

HMENU hMenu; //definimos manejador de ventanas
HWND hEdit;

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
            case CAMBIAR_TITULO:
                wchar_t text[100];
                GetWindowTextW(hEdit, text, 100);
                Sleep(500);
                SetWindowText(hWnd,text);
                break;
            }
            break;

        case WM_CREATE:
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
    CreateWindowW(L"Static",L"Digite su texto aqui:",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER , 200,100,100,50,hWnd,NULL,NULL,NULL);
    hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL ,200,152,100,50, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Button",L"Cambiar el titulo", WS_VISIBLE | WS_CHILD, 200,204, 100,50, hWnd, (HMENU)CAMBIAR_TITULO, NULL, NULL);
}   //WS : Window Style, SS: Static Style, ES: Edit Style
