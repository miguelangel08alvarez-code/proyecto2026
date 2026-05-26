#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Variable global para el idioma (1=Español, 2=Inglés)
int idioma = 1;

// Aquí defini la estructura de cada personaje por ejemplo 
// Cada personaje tiene su numero, nombre, reino, vida, defensa, ataque y energia
struct Personaje {
    int id;              // numero del personaje
    char nombre[20];     // nombre que le pongo
    char reino[10];      // puede ser Ceniza, Sombra, Vacio o Luz
    int hp;              // vida actual
    int hp_max;          // vida maxima (para restaurar despues de cada pelea)
    int def;             // defensa actual (escudo)
    int def_max;         // defensa maxima
    int atq;             // ataque base
    int ce;              // costo de energia (lo uso en la formula del daño)
};

// Variables globales (las uso en todas las funciones)
struct Personaje catalogo[20];   // aqui guardo todos los personajes, maximo 20
int totalPersonajes = 12;        // al inicio solo hay 12 personajes base
struct Personaje equipo1[5];     // los 5 personajes del jugador 1
struct Personaje equipo2[5];     // los 5 personajes del jugador 2
int danioTotal1 = 0;             // voy sumando el daño del jugador 1
int danioTotal2 = 0;             // voy sumando el daño del jugador 2
int equiposListos = 0;           // esto es para saber si ya formaron equipos o no

// Prototipos (le aviso al compilador que estas funciones existen)
void seleccionarIdioma();
void cargarCatalogoBase();
void mostrarCatalogo();
void crearPersonaje();
void formarEquipo(struct Personaje equipo[5], int numeroJugador);
void menuCarta(struct Personaje equipo[5], int numeroJugador);
float calcularDaño(struct Personaje atacante, struct Personaje defensor);
float ventaja(char reinoAtacante[10], char reinoDefensor[10]);
void batalla();
void estadisticas();
void soporteAcademico();
void seleccionarEquiposAleatorios();
int menu();
void pausa();

// Esta funcion es para que el jugador elija el idioma al empezar
void seleccionarIdioma()
{
    int opcion;
    printf("\n1. Español\n");
    printf("2. English\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    if(opcion == 2) idioma = 2;
    else idioma = 1;
}

// Esta es la funcion principal, aqui empieza todo está belleza 
int main()
{
    int opcion;
    seleccionarIdioma();
    srand(time(NULL));          // esto es para que los numeros aleatorios salgan diferentes cada vez
    cargarCatalogoBase();       // cargo los 12 personajes que ya vienen en el juego
    
    do
    {
        opcion = menu();        // muestro el menu y pregunto que quiere hacer
        
        switch(opcion)
        {
            case 1:
                crearPersonaje();   // opcion para crear un personaje nuevo
                break;
            case 2:
                mostrarCatalogo();  // opcion para ver todos los personajes disponibles
                break;
            case 3:
                if(idioma == 1) printf("\nJUGADOR 1\n");
                else printf("\nPLAYER 1\n");
                formarEquipo(equipo1, 1);
                if(idioma == 1) printf("\nJUGADOR 2\n");
                else printf("\nPLAYER 2\n");
                formarEquipo(equipo2, 2);
                equiposListos = 1;
                break;
            case 4:
                if(idioma == 1) printf("\nJUGADOR 1\n");
                else printf("\nPLAYER 1\n");
                menuCarta(equipo1, 1);
                if(idioma == 1) printf("\nJUGADOR 2\n");
                else printf("\nPLAYER 2\n");
                menuCarta(equipo2, 2);
                break;
            case 5:
                if(equiposListos == 0)
                {
                    if(idioma == 1) printf("\nNo has formado equipos. Se asignaran personajes al azar.\n");
                    else printf("\nYou haven't formed teams. Random characters will be assigned.\n");
                    seleccionarEquiposAleatorios();
                    equiposListos = 1;
                }
                batalla();
                break;
            case 6:
                estadisticas();
                break;
            case 7:
                soporteAcademico();
                break;
            case 8:
                if(idioma == 1) printf("Saliendo...\n");
                else printf("Exiting...\n");
                break;
            default:
                if(idioma == 1) printf("Opcion no valida\n");
                else printf("Invalid option\n");
        }
    } while(opcion != 8);
    
    return 0;   // el programa termina bien
}

// Esta funcion hace una pausa y espera que el usuario presione ENTER
void pausa()
{
    printf("\nPresione ENTER para continuar...\n");
    getchar();
    getchar();
}

// Si el jugador no formo equipos, esta funcion elige personajes al azar
void seleccionarEquiposAleatorios()
{
    int usadosEquipo1[12], usadosEquipo2[12];
    int contadorEquipo1 = 0, contadorEquipo2 = 0;
    int numeroAleatorio, repetido;
    
    for(int i = 0; i < 12; i++)
    {
        usadosEquipo1[i] = 0;
        usadosEquipo2[i] = 0;
    }
    
    if(idioma == 1) printf("\n--- EQUIPO 1 (Aleatorio) ---\n");
    else printf("\n--- TEAM 1 (Random) ---\n");
    while(contadorEquipo1 < 5)
    {
        numeroAleatorio = rand() % totalPersonajes;
        repetido = 0;
        for(int j = 0; j < contadorEquipo1; j++)
        {
            if(usadosEquipo1[j] == numeroAleatorio) repetido = 1;
        }
        if(repetido == 0)
        {
            equipo1[contadorEquipo1] = catalogo[numeroAleatorio];
            usadosEquipo1[contadorEquipo1] = numeroAleatorio;
            contadorEquipo1++;
            if(idioma == 1) printf("Agregado: %s\n", catalogo[numeroAleatorio].nombre);
            else printf("Added: %s\n", catalogo[numeroAleatorio].nombre);
        }
    }
    
    if(idioma == 1) printf("\n--- EQUIPO 2 (Aleatorio) ---\n");
    else printf("\n--- TEAM 2 (Random) ---\n");
    while(contadorEquipo2 < 5)
    {
        numeroAleatorio = rand() % totalPersonajes;
        repetido = 0;
        for(int j = 0; j < contadorEquipo2; j++)
        {
            if(usadosEquipo2[j] == numeroAleatorio) repetido = 1;
        }
        if(repetido == 0)
        {
            equipo2[contadorEquipo2] = catalogo[numeroAleatorio];
            usadosEquipo2[contadorEquipo2] = numeroAleatorio;
            contadorEquipo2++;
            if(idioma == 1) printf("Agregado: %s\n", catalogo[numeroAleatorio].nombre);
            else printf("Added: %s\n", catalogo[numeroAleatorio].nombre);
        }
    }
    
    if(idioma == 1) printf("\nEquipos aleatorios asignados!\n");
    else printf("\nRandom teams assigned!\n");
}

// Muestra las opciones del menu
int menu()
{
    int opcion;
    if(idioma == 1) printf("\n=== MENU ===\n");
    else printf("\n=== MENU ===\n");
    
    if(idioma == 1)
    {
        printf("1.Crear personaje\n");
        printf("2.Ver catalogo\n");
        printf("3.Formar equipos\n");
        printf("4.Usar carta potenciacion\n");
        printf("5.Iniciar batalla\n");
        printf("6.Ver estadisticas\n");
        printf("7.Soporte Academico\n");
        printf("8.Salir\n");
    }
    else
    {
        printf("1.Create character\n");
        printf("2.View catalog\n");
        printf("3.Form teams\n");
        printf("4.Use power-up card\n");
        printf("5.Start battle\n");
        printf("6.View statistics\n");
        printf("7.Academic Support\n");
        printf("8.Exit\n");
    }
    
    printf("Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

// Aqui cargo los 12 personajes que ya vienen en el juego
void cargarCatalogoBase()
{
    struct Personaje personaje1 = {1,"Hisoka","Ceniza",40,40,25,25,35,5};
    struct Personaje personaje2 = {2,"Mikhail","Ceniza",50,50,25,25,25,4};
    struct Personaje personaje3 = {3,"Castiel","Ceniza",35,35,20,20,45,5};
    struct Personaje personaje4 = {4,"Lysander","Sombra",45,45,25,25,30,4};
    struct Personaje personaje5 = {5,"Espectador","Sombra",50,50,30,30,20,2};
    struct Personaje personaje6 = {6,"SombraFugitiva","Sombra",35,35,25,25,40,3};
    struct Personaje personaje7 = {7,"Ciel","Vacio",40,40,25,25,35,4};
    struct Personaje personaje8 = {8,"ActorEnFuga","Vacio",50,50,25,25,25,3};
    struct Personaje personaje9 = {9,"CuerpoSinSombra","Vacio",35,35,25,25,40,4};
    struct Personaje personaje10 = {10,"AgenteDelVacio","Luz",45,45,25,25,30,3};
    struct Personaje personaje11 = {11,"PortadorDelReloj","Luz",50,50,25,25,25,4};
    struct Personaje personaje12 = {12,"Instructor","Luz",55,55,25,25,20,2};
    
    catalogo[0] = personaje1;
    catalogo[1] = personaje2;
    catalogo[2] = personaje3;
    catalogo[3] = personaje4;
    catalogo[4] = personaje5;
    catalogo[5] = personaje6;
    catalogo[6] = personaje7;
    catalogo[7] = personaje8;
    catalogo[8] = personaje9;
    catalogo[9] = personaje10;
    catalogo[10] = personaje11;
    catalogo[11] = personaje12;
}

// Muestra todos los personajes que hay en el catalogo
void mostrarCatalogo()
{
    if(idioma == 1) printf("\n--- CATALOGO ---\n");
    else printf("\n--- CATALOG ---\n");
    
    printf("-----------------------------------------------------\n");
    printf("ID  NOMBRE               REINO      V   D   A   E\n");
    printf("-----------------------------------------------------\n");
    
    for(int i = 0; i < totalPersonajes; i++)
    {
        printf("%-3d %-20s %-9s %3d %3d %3d %3d\n",
               catalogo[i].id,
               catalogo[i].nombre,
               catalogo[i].reino,
               catalogo[i].hp,
               catalogo[i].def,
               catalogo[i].atq,
               catalogo[i].ce);
    }
    
    printf("-----------------------------------------------------\n");
}
// Aqui creo un personaje nuevo con formulas matematicas
void crearPersonaje()
{
    if(totalPersonajes >= 20)
    {
        if(idioma == 1) printf("Catalogo lleno\n");
        else printf("Catalog full\n");
        return;
    }
    
    struct Personaje nuevoPersonaje;
    int opcionReino, nivel;
    
    if(idioma == 1) printf("Nombre: ");
    else printf("Name: ");
    scanf("%s", nuevoPersonaje.nombre);
    
    if(idioma == 1) printf("Reino (1.Ceniza 2.Sombra 3.Vacio 4.Luz): ");
    else printf("Kingdom (1.Ceniza 2.Sombra 3.Vacio 4.Luz): ");
    scanf("%d", &opcionReino);
    if(opcionReino == 1) strcpy(nuevoPersonaje.reino, "Ceniza");
    else if(opcionReino == 2) strcpy(nuevoPersonaje.reino, "Sombra");
    else if(opcionReino == 3) strcpy(nuevoPersonaje.reino, "Vacio");
    else strcpy(nuevoPersonaje.reino, "Luz");
    
    if(idioma == 1) printf("Nivel (1 a 5): ");
    else printf("Level (1 to 5): ");
    scanf("%d", &nivel);
    
    while(nivel < 1 || nivel > 5)
    {
        if(idioma == 1) printf("ERROR: El nivel debe ser entre 1 y 5.\n");
        else printf("ERROR: Level must be between 1 and 5.\n");
        if(idioma == 1) printf("Nivel (1 a 5): ");
        else printf("Level (1 to 5): ");
        scanf("%d", &nivel);
    }
    
    nuevoPersonaje.hp = 40 + (nivel * 4);
    nuevoPersonaje.hp_max = nuevoPersonaje.hp;
    nuevoPersonaje.atq = 20 + (nivel * 3) + (nivel * nivel * 0.3);
    nuevoPersonaje.def = 15 + (nivel * 2) + (nivel * 0.5);
    nuevoPersonaje.def_max = nuevoPersonaje.def;
    nuevoPersonaje.ce = 3 + (nivel / 2);
    nuevoPersonaje.id = totalPersonajes + 1;
    
    if(idioma == 1) printf("Personaje creado! HP:%d ATQ:%d DEF:%d\n", 
           nuevoPersonaje.hp, nuevoPersonaje.atq, nuevoPersonaje.def);
    else printf("Character created! HP:%d ATQ:%d DEF:%d\n", 
           nuevoPersonaje.hp, nuevoPersonaje.atq, nuevoPersonaje.def);
    
    catalogo[totalPersonajes] = nuevoPersonaje;
    totalPersonajes++;
}

// Esta funcion permite que el jugador elija sus 5 personajes
void formarEquipo(struct Personaje equipo[5], int numeroJugador)
{
    int idsElegidos[5];
    int idElegido;
    int contador = 0;
    
    mostrarCatalogo();
    
    while(contador < 5)
    {
        if(idioma == 1) printf("ID %d: ", contador + 1);
        else printf("ID %d: ", contador + 1);
        scanf("%d", &idElegido);
        
        int encontrado = 0;
        int repetido = 0;
        
        for(int i = 0; i < totalPersonajes; i++)
        {
            if(catalogo[i].id == idElegido)
            {
                for(int j = 0; j < contador; j++)
                {
                    if(idsElegidos[j] == idElegido) repetido = 1;
                }
                
                if(repetido == 0)
                {
                    equipo[contador] = catalogo[i];
                    idsElegidos[contador] = idElegido;
                    contador++;
                    encontrado = 1;
                }
                else
                {
                    if(idioma == 1) printf("Repetido\n");
                    else printf("Repeated\n");
                }
                break;
            }
        }
        
        if(encontrado == 0)
        {
            if(idioma == 1) printf("ID invalido\n");
            else printf("Invalid ID\n");
        }
    }
    if(idioma == 1) printf("Equipo %d listo\n", numeroJugador);
    else printf("Team %d ready\n", numeroJugador);
}

// Cartas de potenciacion (Buff y Nerf)
void menuCarta(struct Personaje equipo[5], int numeroJugador)
{
    int opcionCarta;
    char reinoCarta[10];
    float multiplicadorAtaque = 1;
    float multiplicadorVida = 1;
    float multiplicadorDefensa = 1;
    int alguienPotenciado = 0;
    
    if(idioma == 1) printf("Cartas:\n");
    else printf("Cards:\n");
    
    if(idioma == 1)
    {
        printf("1.LlamaEterna(Ceniza) +25 ATQ -15 DEF\n");
        printf("2.MantoOscuro(Sombra) +20 HP -10 ATQ\n");
        printf("3.AbismoInterior(Vacio) +30 DEF\n");
        printf("4.LuzDeVerdad(Luz) +25 ATQ -15 HP\n");
        printf("0.Ninguna\n");
    }
    else
    {
        printf("1.EternalFlame(Ceniza) +25 ATK -15 DEF\n");
        printf("2.DarkCloak(Sombra) +20 HP -10 ATK\n");
        printf("3.InnerAbyss(Vacio) +30 DEF\n");
        printf("4.TruthLight(Luz) +25 ATK -15 HP\n");
        printf("0.None\n");
    }
    
    printf("Opcion: ");
    scanf("%d", &opcionCarta);
    
    if(opcionCarta == 1) 
    { 
        strcpy(reinoCarta, "Ceniza"); 
        multiplicadorAtaque = 1.25; 
        multiplicadorDefensa = 0.85;
        if(idioma == 1) printf("\n--- Aplicando LlamaEterna a personajes de Ceniza ---\n");
        else printf("\n--- Applying EternalFlame to Ceniza characters ---\n");
    }
    else if(opcionCarta == 2) 
    { 
        strcpy(reinoCarta, "Sombra"); 
        multiplicadorVida = 1.20; 
        multiplicadorAtaque = 0.90;
        if(idioma == 1) printf("\n--- Aplicando MantoOscuro a personajes de Sombra ---\n");
        else printf("\n--- Applying DarkCloak to Sombra characters ---\n");
    }
    else if(opcionCarta == 3) 
    { 
        strcpy(reinoCarta, "Vacio"); 
        multiplicadorDefensa = 1.30;
        if(idioma == 1) printf("\n--- Aplicando AbismoInterior a personajes de Vacio ---\n");
        else printf("\n--- Applying InnerAbyss to Vacio characters ---\n");
    }
    else if(opcionCarta == 4) 
    { 
        strcpy(reinoCarta, "Luz"); 
        multiplicadorAtaque = 1.25; 
        multiplicadorVida = 0.85;
        if(idioma == 1) printf("\n--- Aplicando LuzDeVerdad a personajes de Luz ---\n");
        else printf("\n--- Applying TruthLight to Luz characters ---\n");
    }
    else 
    { 
        if(idioma == 1) printf("Sin carta\n"); 
        else printf("No card\n"); 
        return; 
    }
    
    for(int i = 0; i < 5; i++)
    {
        if(strcmp(equipo[i].reino, reinoCarta) == 0)
        {
            if(idioma == 1) printf("\n%s fue potenciado:\n", equipo[i].nombre);
            else printf("\n%s was powered up:\n", equipo[i].nombre);
            
            if(idioma == 1) printf("  Ataque: %d -> %d", equipo[i].atq, (int)(equipo[i].atq * multiplicadorAtaque));
            else printf("  Attack: %d -> %d", equipo[i].atq, (int)(equipo[i].atq * multiplicadorAtaque));
            equipo[i].atq = equipo[i].atq * multiplicadorAtaque;
            
            if(idioma == 1) printf("  Vida: %d -> %d", equipo[i].hp, (int)(equipo[i].hp * multiplicadorVida));
            else printf("  Health: %d -> %d", equipo[i].hp, (int)(equipo[i].hp * multiplicadorVida));
            equipo[i].hp = equipo[i].hp * multiplicadorVida;
            equipo[i].hp_max = equipo[i].hp_max * multiplicadorVida;
            
            if(idioma == 1) printf("  Defensa: %d -> %d", equipo[i].def, (int)(equipo[i].def * multiplicadorDefensa));
            else printf("  Defense: %d -> %d", equipo[i].def, (int)(equipo[i].def * multiplicadorDefensa));
            equipo[i].def = equipo[i].def * multiplicadorDefensa;
            equipo[i].def_max = equipo[i].def_max * multiplicadorDefensa;
            printf("\n");
            alguienPotenciado = 1;
        }
    }
    
    if(alguienPotenciado == 0)
    {
        if(idioma == 1) printf("\nNingun personaje de tu equipo es del reino %s. Carta sin efecto.\n", reinoCarta);
        else printf("\nNo character in your team belongs to the %s kingdom. Card has no effect.\n", reinoCarta);
    }
}

// Calcula la ventaja elemental entre dos reinos
float ventaja(char reinoAtacante[10], char reinoDefensor[10])
{
    // el ciclo es: Ceniza > Sombra > Vacio > Luz > Ceniza
    
    // CASOS FUERTES (x1.5)
    if(strcmp(reinoAtacante, "Ceniza") == 0 && strcmp(reinoDefensor, "Sombra") == 0) return 1.5;
    if(strcmp(reinoAtacante, "Sombra") == 0 && strcmp(reinoDefensor, "Vacio") == 0) return 1.5;
    if(strcmp(reinoAtacante, "Vacio") == 0 && strcmp(reinoDefensor, "Luz") == 0) return 1.5;
    if(strcmp(reinoAtacante, "Luz") == 0 && strcmp(reinoDefensor, "Ceniza") == 0) return 1.5;
    
    // CASOS DEBILES (x0.8)
    if(strcmp(reinoAtacante, "Ceniza") == 0 && strcmp(reinoDefensor, "Luz") == 0) return 0.8;
    if(strcmp(reinoAtacante, "Sombra") == 0 && strcmp(reinoDefensor, "Ceniza") == 0) return 0.8;
    if(strcmp(reinoAtacante, "Vacio") == 0 && strcmp(reinoDefensor, "Sombra") == 0) return 0.8;
    if(strcmp(reinoAtacante, "Luz") == 0 && strcmp(reinoDefensor, "Vacio") == 0) return 0.8;
    
    // SIN VENTAJA
    return 1.0;
}

// Calcula el daño usando polinomio y ventaja
float calcularDaño(struct Personaje atacante, struct Personaje defensor)
{
    float base, daño;
    
    // polinomio: 2*(ATQ/10)^2 + 3*(ATQ/10) + 5
    base = (2 * (atacante.atq / 10.0) * (atacante.atq / 10.0)) + (3 * (atacante.atq / 10.0)) + 5;
    
    // escalado por energia (esto simula el logaritmo)
    base = base / (atacante.ce + 1);
    
    // multiplico por 3 para que la batalla no sea eterna
    base = base * 3;
    
    // aplico la ventaja elemental
    daño = base * ventaja(atacante.reino, defensor.reino);
    
    // pongo limites para que el daño no sea ni muy bajo ni muy alto
    if(daño < 15) daño = 15;
    if(daño > 60) daño = 60;
    
    return daño;
}

// Simula toda la batalla
void batalla()
{
    int indiceEquipo1 = 0;
    int indiceEquipo2 = 0;
    int turno = 1;
    float dañoActual;
    int dañoRestante;
    
    for(int i = 0; i < 5; i++)
    {
        equipo1[i].hp = equipo1[i].hp_max;
        equipo1[i].def = equipo1[i].def_max;
        equipo2[i].hp = equipo2[i].hp_max;
        equipo2[i].def = equipo2[i].def_max;
    }
    
    if(idioma == 1) printf("\n========== BATALLA ==========\n");
    else printf("\n========== BATTLE ==========\n");
    
    while(indiceEquipo1 < 5 && indiceEquipo2 < 5)
    {
        printf("\n----------------------------------------\n");
        printf("%s vs %s\n", equipo1[indiceEquipo1].nombre, equipo2[indiceEquipo2].nombre);
        printf("[J1] %s V:%d D:%d | [J2] %s V:%d D:%d\n",
               equipo1[indiceEquipo1].nombre, equipo1[indiceEquipo1].hp, equipo1[indiceEquipo1].def,
               equipo2[indiceEquipo2].nombre, equipo2[indiceEquipo2].hp, equipo2[indiceEquipo2].def);
        
        if(turno == 1)
        {
            if(idioma == 1) printf("\n>>> JUGADOR 1 ATACA <<<\n");
            else printf("\n>>> PLAYER 1 ATTACKS <<<\n");
            dañoActual = calcularDaño(equipo1[indiceEquipo1], equipo2[indiceEquipo2]);
            danioTotal1 = danioTotal1 + dañoActual;
            if(idioma == 1) printf("Daño causado: %.0f\n", dañoActual);
            else printf("Damage caused: %.0f\n", dañoActual);
            
            if(dañoActual <= equipo2[indiceEquipo2].def)
            {
                equipo2[indiceEquipo2].def = equipo2[indiceEquipo2].def - dañoActual;
                if(idioma == 1) printf("El escudo absorbe. DEF restante: %d\n", equipo2[indiceEquipo2].def);
                else printf("Shield absorbs. DEF remaining: %d\n", equipo2[indiceEquipo2].def);
            }
            else
            {
                dañoRestante = dañoActual - equipo2[indiceEquipo2].def;
                equipo2[indiceEquipo2].def = 0;
                equipo2[indiceEquipo2].hp = equipo2[indiceEquipo2].hp - dañoRestante;
                if(idioma == 1) printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", dañoRestante, equipo2[indiceEquipo2].hp);
                else printf("Shield broken! Damage to health: %d. HEALTH remaining: %d\n", dañoRestante, equipo2[indiceEquipo2].hp);
            }
            turno = 2;
        }
        else
        {
            if(idioma == 1) printf("\n>>> JUGADOR 2 ATACA <<<\n");
            else printf("\n>>> PLAYER 2 ATTACKS <<<\n");
            dañoActual = calcularDaño(equipo2[indiceEquipo2], equipo1[indiceEquipo1]);
            danioTotal2 = danioTotal2 + dañoActual;
            if(idioma == 1) printf("Daño causado: %.0f\n", dañoActual);
            else printf("Damage caused: %.0f\n", dañoActual);
            
            if(dañoActual <= equipo1[indiceEquipo1].def)
            {
                equipo1[indiceEquipo1].def = equipo1[indiceEquipo1].def - dañoActual;
                if(idioma == 1) printf("El escudo absorbe. DEF restante: %d\n", equipo1[indiceEquipo1].def);
                else printf("Shield absorbs. DEF remaining: %d\n", equipo1[indiceEquipo1].def);
            }
            else
            {
                dañoRestante = dañoActual - equipo1[indiceEquipo1].def;
                equipo1[indiceEquipo1].def = 0;
                equipo1[indiceEquipo1].hp = equipo1[indiceEquipo1].hp - dañoRestante;
                if(idioma == 1) printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", dañoRestante, equipo1[indiceEquipo1].hp);
                else printf("Shield broken! Damage to health: %d. HEALTH remaining: %d\n", dañoRestante, equipo1[indiceEquipo1].hp);
            }
            turno = 1;
        }
        
        if(equipo2[indiceEquipo2].hp <= 0)
        {
            if(idioma == 1) printf("\n*** %s ha muerto! ***\n", equipo2[indiceEquipo2].nombre);
            else printf("\n*** %s has died! ***\n", equipo2[indiceEquipo2].nombre);
            indiceEquipo2 = indiceEquipo2 + 1;
            if(indiceEquipo2 < 5)
            {
                if(idioma == 1) printf("Entra al campo: %s\n", equipo2[indiceEquipo2].nombre);
                else printf("Enters the field: %s\n", equipo2[indiceEquipo2].nombre);
            }
        }
        if(equipo1[indiceEquipo1].hp <= 0)
        {
            if(idioma == 1) printf("\n*** %s ha muerto! ***\n", equipo1[indiceEquipo1].nombre);
            else printf("\n*** %s has died! ***\n", equipo1[indiceEquipo1].nombre);
            indiceEquipo1 = indiceEquipo1 + 1;
            if(indiceEquipo1 < 5)
            {
                if(idioma == 1) printf("Entra al campo: %s\n", equipo1[indiceEquipo1].nombre);
                else printf("Enters the field: %s\n", equipo1[indiceEquipo1].nombre);
            }
        }
        
        pausa();
    }
    
    if(idioma == 1) printf("\n========== RESULTADO FINAL ==========\n");
    else printf("\n========== FINAL RESULT ==========\n");
    if(indiceEquipo1 >= 5 && indiceEquipo2 >= 5)
    {
        if(idioma == 1) printf("EMPATE\n");
        else printf("DRAW\n");
    }
    else if(indiceEquipo1 >= 5)
    {
        if(idioma == 1) printf("JUGADOR 2 GANA LA BATALLA\n");
        else printf("PLAYER 2 WINS THE BATTLE\n");
    }
    else
    {
        if(idioma == 1) printf("JUGADOR 1 GANA LA BATALLA\n");
        else printf("PLAYER 1 WINS THE BATTLE\n");
    }
}

// Muestra el daño total que hizo cada jugador
void estadisticas()
{
    if(idioma == 1) printf("\n=== ESTADISTICAS DE DAÑO ===\n");
    else printf("\n=== DAMAGE STATISTICS ===\n");
    if(idioma == 1) printf("Daño Jugador 1: %d\n", danioTotal1);
    else printf("Player 1 Damage: %d\n", danioTotal1);
    if(idioma == 1) printf("Daño Jugador 2: %d\n", danioTotal2);
    else printf("Player 2 Damage: %d\n", danioTotal2);
    
    if(danioTotal1 > danioTotal2)
    {
        if(idioma == 1) printf("Mayor daño: Jugador 1\n");
        else printf("Most damage: Player 1\n");
    }
    else if(danioTotal2 > danioTotal1)
    {
        if(idioma == 1) printf("Mayor daño: Jugador 2\n");
        else printf("Most damage: Player 2\n");
    }
    else
    {
        if(idioma == 1) printf("Empate en daño\n");
        else printf("Damage tie\n");
    }
}

// Esta funcion explica las matematicas y la logica que use
void soporteAcademico()
{
    if(idioma == 1) printf("\n========== SOPORTE ACADEMICO ==========\n");
    else printf("\n========== ACADEMIC SUPPORT ==========\n");
    
    if(idioma == 1)
    {
        printf("MATEMATICAS USADAS:\n");
        printf("1. Polinomio: Daño = 2*(ATQ/10)^2 + 3*(ATQ/10) + 5\n");
        printf("2. Logaritmo: Daño_base / (CE + 1)\n");
        printf("3. Inecuacion: if(daño <= defensa) escudo; else daño a vida\n");
        printf("4. Valor Absoluto: La defensa nunca queda negativa\n");
        printf("\nLOGICA USADA:\n");
        printf("1. Conectivos AND (&&): if(reinoAtacante==Ceniza && reinoDefensor==Sombra)\n");
        printf("2. Cuantificadores: while(indiceEquipo1<5 && indiceEquipo2<5)\n");
        printf("3. Teoria de Conjuntos: Clasificacion por reinos\n");
        printf("\nVENTAJA ELEMENTAL:\n");
        printf("Ceniza > Sombra > Vacio > Luz > Ceniza\n");
        printf("Fuerte: x1.5  |  Debil: x0.8\n");
    }
    else
    {
        printf("MATHEMATICS USED:\n");
        printf("1. Polynomial: Damage = 2*(ATK/10)^2 + 3*(ATK/10) + 5\n");
        printf("2. Logarithm: Base_Damage / (EC + 1)\n");
        printf("3. Inequality: if(damage <= defense) shield; else damage to health\n");
        printf("4. Absolute Value: Defense never becomes negative\n");
        printf("\nLOGIC USED:\n");
        printf("1. AND connectives (&&): if(attackerKingdom==Ceniza && defenderKingdom==Sombra)\n");
        printf("2. Quantifiers: while(team1Index<5 && team2Index<5)\n");
        printf("3. Set Theory: Classification by kingdoms\n");
        printf("\nELEMENTAL ADVANTAGE:\n");
        printf("Ceniza > Sombra > Vacio > Luz > Ceniza\n");
        printf("Strong: x1.5  |  Weak: x0.8\n");
    }
    if(idioma == 1) printf("========================================\n");
    else printf("========================================\n");
}