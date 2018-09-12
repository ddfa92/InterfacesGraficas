#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);


//función principal para la ventana
// hInstance es el manejador de una instancia o un módulo. El sistema operativo usa este valor para identificar el ejecutable cuando éste es cargado en memoria. Este manejador es necesario para ciertas funciones de Windows como cargar íconos o imagenes
// pInstance no tiene uso actualmente. Fue usado en Windows de 16 bit, pero ahora es 0
// pCmdLine contiene los argumentos de la linea de comandos como una cadena unicode
// nCmdShow es un señalador que dice si la aplicación será minimzada, maximizada o mostrada normalmente
int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE pInstance,
					LPSTR pCmdLine,
					int nCmdShow)
{
    // Register the window class.
    const wchar_t NOMBRE_DE_CLASE[]  = L"Ejemplo de una clase de ventana";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProcedure;	//defines mos of the behavior of the window
    wc.hInstance     = hInstance;
    wc.lpszClassName = NOMBRE_DE_CLASE;		// una cadena que identifica la clase de ventana

    RegisterClass(&wc);

    //---------------------- Create the window.
	// CreateWindowEx devuelve un manejador a la nueva ventana, o 0 si la función falla.Para mostrar la ventana, para el manejador de la ventana a la función ShowWindow
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        NOMBRE_DE_CLASE,                     // Window class
        L"Aprenda a programar ventanas",    // El título de la ventana
        WS_OVERLAPPEDWINDOW,            // Window style, es una constante que  tienes varias propiedades: tener una barra para el titulo, un borde, un menu del sistema, y los botones de minimizar, maximizar y cerrar

        // Size and position
        //CW_USEDEFAULT es una constante que usa valores por defecto
        CW_USEDEFAULT, // Posición en x de la ventana
		CW_USEDEFAULT,   // Posición en y de la ventana
		640, // Anchura de la ventana
		640, // Altura de la ventana

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

		//Si no se crea el manejador de la ventana, termine la función WinMain y devuelva 0, es decir, la ventana no se muestra
    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); //Muestre la ventana en pantalla
	//El parámetro hwnd es el manejador de la ventana devuelto por CreateWindowEx. El parámetro nCmdShow puede ser utilizado para minimizar o maximizar una ventana. El sistema operativo pasa este valor al programa atravéz de la función WinMain


	//-------------Message loop
	//Los mensajes son útiles, pues permiten a nuestro programa interactuar con el usuario y el sistema operativo. Un mensaje es simplemente un código numérico que designa un evento particular, por ejemplo si el usuario presiona el click izquierdo del mouse, la ventana recibe un mensaje que tiene el siguiente código: #define WM_LBUTTONDOWN 0X0201. Algunos mensajes tienen datos asociados con ellosm por ejemplo el anterior mensaje incluye la coordenada x y  y del cursor.
	//El loop de mensajes se encarga de recibir los mensajes y enviarlos a donde corresponda
	//Los mensajes se acomodan en una fila. Uno no puede manupular dicha cola directamente, pero podemos obtener un mensaje de la fila al llamar la función GetMessage de la siguiente forma
	//MSG msg;
	//GetMessage(&msg, NULL, 0,0)
	//Esta función remueve el primer mensaje de la cabeza de la fila


	// Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); //Está relacionada con las entradas de teclado. Traduce "el oprimir" y el soltar una tecla en caracteres. No debemos preocuparnos por cómo funciona, pero si de llamarla antes de DispatchMessage
        DispatchMessage(&msg);	//Esta función le dice al sistema operativo que llame al procedimiento de la ventana que es el destinatario del mensaje. Cuando el procedimiento de la ventana termina, regresa a la función DispatchMessage. Este regresa al loop de mensajes en espera del siguiente mensaje.
		//En nuestro caso el procedimiento es WindowProcedure
    }

	// GetMessage(&msg, NULL, 0, 0) usualmente devuelve 1, lo que nos permite que el loop esté activo y pendiente de cualquier mensaje que le interese a nuestra ventana, pero devuelve el valor 0 si por ejemplo cerramos la ventana. Por lo que dejará de estar pendiente de los mensajes y se terminará el loop
    return 0;
}

//Prodedimiento de la ventana
//hwnd: manejador de la ventana
// uMsg es el código del mensaje, por ejemplo WM_SIZE
// wParam y lParam contienen datos adicionales pertinentes al mensaje. El significado exacto de cada uno de ellos depende del mensaje

//LRESUL es un valor entero que nuestro programa devuelve a Windows. Este contiene la respuesta de nuestro programa a un mensaje particular. El significado de este valor depende del codigo del mensaje. CALLBACK es la convención de llamada para la función
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) //usando un switch dependiendo del mensaje que se recibe
    {

    case WM_DESTROY: //este mensaje cierra la ventana
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: //este mensaje dibuja la ventana // redibuja la ventana
        {
            //Al pintar una ventana solo somos responsables por lo que hay dentro de ella. Esta área se conoce como area del cliente. Los bordes son dibujados por el so. También hay una región que se actualizará y se redibujará,por ejemplo cuando otra ventana se situa delante de la que creamos y luego volvemos a nuestra ventana
            PAINTSTRUCT ps; //Paintstruct es una estructura que contiene información para una aplicación. Esta información puede ser usada para pintar el área del cliente de una ventana propia de una aplicación.
            HDC hdc = BeginPaint(hwnd, &ps); //Comenzamos la operación de dibujar la ventana al llamar la función beginpaint. Esta función llena con información la estructura paintstruct para la petición de redibujar. La región actual que se actualizará esta dada en el rcPaint de Paintstruct. Esta región está definida relativa al área del cliente
              //--Aquí dentro se pinta todo lo que estará en la ventana
              FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
                // aquí termina
              EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_CLOSE:
        if (MessageBox(hwnd, L"¿Realmente quieres salir?", L"Problema del caballo", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        // Else: User canceled. Do nothing.
        return 0;



    case WM_KEYDOWN:
		if (wParam==0x26)
		{
			MessageBox(hwnd, L"Presionaste la tecla Flecha hacia arriba.", L"Problema del caballo", MB_OK);
		}
		return 0;



    } //fin del switch




	//si no pasamos ningun procedimiento en particular, devolvemos lo que nos retorne la función DefWindowProc, que ejecuta la acción por defecto para el mensaje.
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



//Evitar los cuellos de botella en nuestra ventana.
//Mientras un procedimiento de ventana se ejecuta, bloquea cualquier otro mensaje para la ventana creada en el mismo hilo, por eso se han de evitar procedimientos largos dentro de los procedimientos de la ventana. Para eso, si hay algun procedimiento largo, debemos moverlo a otro hilo(thread) usando las herramientas multitarea que están construidas en Windows
