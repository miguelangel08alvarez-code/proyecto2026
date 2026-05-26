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
void formarEquipo(struct Personaje equipo[5], int num);
void menuCarta(struct Personaje equipo[5], int num);
float calcularDaño(struct Personaje at, struct Personaje df);
float ventaja(char a[10], char d[10]);
void batalla();
void estadisticas();
void soporteAcademico();
void seleccionarEquiposAleatorios();
int menu();
void pausa();

// Esta funcion es para que el jugador elija el idioma al empezar
void seleccionarIdioma()
{
    int op;
    printf("\n1. Español\n");
    printf("2. English\n");
    printf("Opcion: ");
    scanf("%d", &op);
    if(op == 2) idioma = 2;
    else idioma = 1;
}

// Esta es la funcion principal, aqui empieza todo está belleza xd
int main()
{
    int opcion;
    seleccionarIdioma();
    srand(time(NULL));          // esto es para que los numeros aleatorios salgan diferentes cada vez
    cargarCatalogoBase();       // cargo los 12 personajes que ya vienen en el juego
    
    do
    {
        opcion = menu();        // muestro el menu y pregunto que quiere hacer el jugador 
        
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
    int usados1[12], usados2[12];
    int cont1 = 0, cont2 = 0;
    int num, repetido;
    
    for(int i = 0; i < 12; i++)
    {
        usados1[i] = 0;
        usados2[i] = 0;
    }
    
    if(idioma == 1) printf("\n--- EQUIPO 1 (Aleatorio) ---\n");
    else printf("\n--- TEAM 1 (Random) ---\n");
    while(cont1 < 5)
    {
        num = rand() % totalPersonajes;
        repetido = 0;
        for(int j = 0; j < cont1; j++)
        {
            if(usados1[j] == num) repetido = 1;
        }
        if(repetido == 0)
        {
            equipo1[cont1] = catalogo[num];
            usados1[cont1] = num;
            cont1++;
            if(idioma == 1) printf("Agregado: %s\n", catalogo[num].nombre);
            else printf("Added: %s\n", catalogo[num].nombre);
        }
    }
    
    if(idioma == 1) printf("\n--- EQUIPO 2 (Aleatorio) ---\n");
    else printf("\n--- TEAM 2 (Random) ---\n");
    while(cont2 < 5)
    {
        num = rand() % totalPersonajes;
        repetido = 0;
        for(int j = 0; j < cont2; j++)
        {
            if(usados2[j] == num) repetido = 1;
        }
        if(repetido == 0)
        {
            equipo2[cont2] = catalogo[num];
            usados2[cont2] = num;
            cont2++;
            if(idioma == 1) printf("Agregado: %s\n", catalogo[num].nombre);
            else printf("Added: %s\n", catalogo[num].nombre);
        }
    }
    
    if(idioma == 1) printf("\nEquipos aleatorios asignados!\n");
    else printf("\nRandom teams assigned!\n");
}

// Muestra las opciones del menu
int menu()
{
    int op;
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
    scanf("%d", &op);
    return op;
}

// Aqui cargo los 12 personajes que ya vienen en el juego
void cargarCatalogoBase()
{
    struct Personaje p1 = {1,"Hisoka","Ceniza",40,40,25,25,35,5};
    struct Personaje p2 = {2,"Mikhail","Ceniza",50,50,25,25,25,4};
    struct Personaje p3 = {3,"Castiel","Ceniza",35,35,20,20,45,5};
    struct Personaje p4 = {4,"Lysander","Sombra",45,45,25,25,30,4};
    struct Personaje p5 = {5,"Espectador","Sombra",50,50,30,30,20,2};
    struct Personaje p6 = {6,"SombraFugitiva","Sombra",35,35,25,25,40,3};
    struct Personaje p7 = {7,"Ciel","Vacio",40,40,25,25,35,4};
    struct Personaje p8 = {8,"ActorEnFuga","Vacio",50,50,25,25,25,3};
    struct Personaje p9 = {9,"CuerpoSinSombra","Vacio",35,35,25,25,40,4};
    struct Personaje p10 = {10,"AgenteDelVacio","Luz",45,45,25,25,30,3};
    struct Personaje p11 = {11,"PortadorDelReloj","Luz",50,50,25,25,25,4};
    struct Personaje p12 = {12,"Instructor","Luz",55,55,25,25,20,2};
    
    catalogo[0] = p1;
    catalogo[1] = p2;
    catalogo[2] = p3;
    catalogo[3] = p4;
    catalogo[4] = p5;
    catalogo[5] = p6;
    catalogo[6] = p7;
    catalogo[7] = p8;
    catalogo[8] = p9;
    catalogo[9] = p10;
    catalogo[10] = p11;
    catalogo[11] = p12;
}

// Muestra todos los personajes que hay en el catalogo
void mostrarCatalogo()
{
    if(idioma == 1) printf("\n--- CATALOGO ---\n");
    else printf("\n--- CATALOG ---\n");
    for(int i = 0; i < totalPersonajes; i++)
    {
        printf("%d.%s[%s] V:%d D:%d A:%d E:%d\n",
               catalogo[i].id,
               catalogo[i].nombre,
               catalogo[i].reino,
               catalogo[i].hp,
               catalogo[i].def,
               catalogo[i].atq,
               catalogo[i].ce);
    }
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
    
    struct Personaje nuevo;
    int opReino, nivel;
    
    if(idioma == 1) printf("Nombre: ");
    else printf("Name: ");
    scanf("%s", nuevo.nombre);
    
    if(idioma == 1) printf("Reino (1.Ceniza 2.Sombra 3.Vacio 4.Luz): ");
    else printf("Kingdom (1.Ceniza 2.Sombra 3.Vacio 4.Luz): ");
    scanf("%d", &opReino);
    if(opReino == 1) strcpy(nuevo.reino, "Ceniza");
    else if(opReino == 2) strcpy(nuevo.reino, "Sombra");
    else if(opReino == 3) strcpy(nuevo.reino, "Vacio");
    else strcpy(nuevo.reino, "Luz");
    
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
    
    nuevo.hp = 40 + (nivel * 4);
    nuevo.hp_max = nuevo.hp;
    nuevo.atq = 20 + (nivel * 3) + (nivel * nivel * 0.3);
    nuevo.def = 15 + (nivel * 2) + (nivel * 0.5);
    nuevo.def_max = nuevo.def;
    nuevo.ce = 3 + (nivel / 2);
    nuevo.id = totalPersonajes + 1;
    
    if(idioma == 1) printf("Personaje creado! HP:%d ATQ:%d DEF:%d\n", nuevo.hp, nuevo.atq, nuevo.def);
    else printf("Character created! HP:%d ATQ:%d DEF:%d\n", nuevo.hp, nuevo.atq, nuevo.def);
    
    catalogo[totalPersonajes] = nuevo;
    totalPersonajes++;
}

// Esta funcion permite que el jugador elija sus 5 personajes
void formarEquipo(struct Personaje equipo[5], int num)
{
    int ids[5];
    int id;
    int cont = 0;
    
    mostrarCatalogo();
    
    while(cont < 5)
    {
        if(idioma == 1) printf("ID %d: ", cont + 1);
        else printf("ID %d: ", cont + 1);
        scanf("%d", &id);
        
        int encontrado = 0;
        int repetido = 0;
        
        for(int i = 0; i < totalPersonajes; i++)
        {
            if(catalogo[i].id == id)
            {
                for(int j = 0; j < cont; j++)
                {
                    if(ids[j] == id) repetido = 1;
                }
                
                if(repetido == 0)
                {
                    equipo[cont] = catalogo[i];
                    ids[cont] = id;
                    cont++;
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
    if(idioma == 1) printf("Equipo %d listo\n", num);
    else printf("Team %d ready\n", num);
}

// Cartas de potenciacion (Buff y Nerf)
void menuCarta(struct Personaje equipo[5], int num)
{
    int op;
    char reinoC[10];
    float multAtq = 1;
    float multHp = 1;
    float multDef = 1;
    int alguienPotenciado = 0;
    
    if(idioma == 1) printf("Cartas:\n");
    else printf("Cards:\n");
    printf("1.LlamaEterna(Ceniza) +25 ATQ -15 DEF\n");
    printf("2.MantoOscuro(Sombra) +20 HP -10 ATQ\n");
    printf("3.AbismoInterior(Vacio) +30 DEF\n");
    printf("4.LuzDeVerdad(Luz) +25 ATQ -15 HP\n");
    if(idioma == 1) printf("0.Ninguna\n");
    else printf("0.None\n");
    printf("Opcion: ");
    scanf("%d", &op);
    
    if(op == 1) { strcpy(reinoC, "Ceniza"); multAtq = 1.25; multDef = 0.85; }
    else if(op == 2) { strcpy(reinoC, "Sombra"); multHp = 1.20; multAtq = 0.90; }
    else if(op == 3) { strcpy(reinoC, "Vacio"); multDef = 1.30; }
    else if(op == 4) { strcpy(reinoC, "Luz"); multAtq = 1.25; multHp = 0.85; }
    else { if(idioma == 1) printf("Sin carta\n"); else printf("No card\n"); return; }
    
    for(int i = 0; i < 5; i++)
    {
        if(strcmp(equipo[i].reino, reinoC) == 0)
        {
            if(idioma == 1) printf("\n%s fue potenciado:\n", equipo[i].nombre);
            else printf("\n%s was powered up:\n", equipo[i].nombre);
            if(idioma == 1) printf("  Ataque: %d -> %d", equipo[i].atq, (int)(equipo[i].atq * multAtq));
            else printf("  Attack: %d -> %d", equipo[i].atq, (int)(equipo[i].atq * multAtq));
            equipo[i].atq = equipo[i].atq * multAtq;
            if(idioma == 1) printf("  Vida: %d -> %d", equipo[i].hp, (int)(equipo[i].hp * multHp));
            else printf("  Health: %d -> %d", equipo[i].hp, (int)(equipo[i].hp * multHp));
            equipo[i].hp = equipo[i].hp * multHp;
            equipo[i].hp_max = equipo[i].hp_max * multHp;
            if(idioma == 1) printf("  Defensa: %d -> %d", equipo[i].def, (int)(equipo[i].def * multDef));
            else printf("  Defense: %d -> %d", equipo[i].def, (int)(equipo[i].def * multDef));
            equipo[i].def = equipo[i].def * multDef;
            equipo[i].def_max = equipo[i].def_max * multDef;
            printf("\n");
            alguienPotenciado = 1;
        }
    }
    
    if(alguienPotenciado == 0)
    {
        if(idioma == 1) printf("\nNingun personaje de tu equipo es del reino %s. Carta sin efecto.\n", reinoC);
        else printf("\nNo character in your team belongs to the %s kingdom. Card has no effect.\n", reinoC);
    }
}

// Calcula la ventaja elemental entre dos reinos
float ventaja(char a[10], char d[10])
{
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Sombra") == 0) return 1.5;
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Vacio") == 0) return 1.5;
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Luz") == 0) return 1.5;
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Ceniza") == 0) return 1.5;
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Luz") == 0) return 0.8;
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Ceniza") == 0) return 0.8;
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Sombra") == 0) return 0.8;
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Vacio") == 0) return 0.8;
    return 1.0;
}

// Calcula el daño usando polinomio y ventaja
float calcularDaño(struct Personaje at, struct Personaje df)
{
    float base, daño;
    
    base = (2 * (at.atq / 10.0) * (at.atq / 10.0)) + (3 * (at.atq / 10.0)) + 5;
    base = base / (at.ce + 1);
    base = base * 3;
    daño = base * ventaja(at.reino, df.reino);
    
    if(daño < 15) daño = 15;
    if(daño > 60) daño = 60;
    
    return daño;
}

// Simula toda la batalla
void batalla()
{
    int i1 = 0, i2 = 0, turno = 1;
    float d;
    int resto;
    
    for(int i = 0; i < 5; i++)
    {
        equipo1[i].hp = equipo1[i].hp_max;
        equipo1[i].def = equipo1[i].def_max;
        equipo2[i].hp = equipo2[i].hp_max;
        equipo2[i].def = equipo2[i].def_max;
    }
    
    if(idioma == 1) printf("\n========== BATALLA ==========\n");
    else printf("\n========== BATTLE ==========\n");
    
    while(i1 < 5 && i2 < 5)
    {
        printf("\n----------------------------------------\n");
        printf("%s vs %s\n", equipo1[i1].nombre, equipo2[i2].nombre);
        printf("[J1] %s V:%d D:%d | [J2] %s V:%d D:%d\n",
               equipo1[i1].nombre, equipo1[i1].hp, equipo1[i1].def,
               equipo2[i2].nombre, equipo2[i2].hp, equipo2[i2].def);
        
        if(turno == 1)
        {
            if(idioma == 1) printf("\n>>> JUGADOR 1 ATACA <<<\n");
            else printf("\n>>> PLAYER 1 ATTACKS <<<\n");
            d = calcularDaño(equipo1[i1], equipo2[i2]);
            danioTotal1 = danioTotal1 + d;
            if(idioma == 1) printf("Daño causado: %.0f\n", d);
            else printf("Damage caused: %.0f\n", d);
            
            if(d <= equipo2[i2].def)
            {
                equipo2[i2].def = equipo2[i2].def - d;
                if(idioma == 1) printf("El escudo absorbe. DEF restante: %d\n", equipo2[i2].def);
                else printf("Shield absorbs. DEF remaining: %d\n", equipo2[i2].def);
            }
            else
            {
                resto = d - equipo2[i2].def;
                equipo2[i2].def = 0;
                equipo2[i2].hp = equipo2[i2].hp - resto;
                if(idioma == 1) printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", resto, equipo2[i2].hp);
                else printf("Shield broken! Damage to health: %d. HEALTH remaining: %d\n", resto, equipo2[i2].hp);
            }
            turno = 2;
        }
        else
        {
            if(idioma == 1) printf("\n>>> JUGADOR 2 ATACA <<<\n");
            else printf("\n>>> PLAYER 2 ATTACKS <<<\n");
            d = calcularDaño(equipo2[i2], equipo1[i1]);
            danioTotal2 = danioTotal2 + d;
            if(idioma == 1) printf("Daño causado: %.0f\n", d);
            else printf("Damage caused: %.0f\n", d);
            
            if(d <= equipo1[i1].def)
            {
                equipo1[i1].def = equipo1[i1].def - d;
                if(idioma == 1) printf("El escudo absorbe. DEF restante: %d\n", equipo1[i1].def);
                else printf("Shield absorbs. DEF remaining: %d\n", equipo1[i1].def);
            }
            else
            {
                resto = d - equipo1[i1].def;
                equipo1[i1].def = 0;
                equipo1[i1].hp = equipo1[i1].hp - resto;
                if(idioma == 1) printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", resto, equipo1[i1].hp);
                else printf("Shield broken! Damage to health: %d. HEALTH remaining: %d\n", resto, equipo1[i1].hp);
            }
            turno = 1;
        }
        
        if(equipo2[i2].hp <= 0)
        {
            if(idioma == 1) printf("\n*** %s ha muerto! ***\n", equipo2[i2].nombre);
            else printf("\n*** %s has died! ***\n", equipo2[i2].nombre);
            i2 = i2 + 1;
            if(i2 < 5)
            {
                if(idioma == 1) printf("Entra al campo: %s\n", equipo2[i2].nombre);
                else printf("Enters the field: %s\n", equipo2[i2].nombre);
            }
        }
        if(equipo1[i1].hp <= 0)
        {
            if(idioma == 1) printf("\n*** %s ha muerto! ***\n", equipo1[i1].nombre);
            else printf("\n*** %s has died! ***\n", equipo1[i1].nombre);
            i1 = i1 + 1;
            if(i1 < 5)
            {
                if(idioma == 1) printf("Entra al campo: %s\n", equipo1[i1].nombre);
                else printf("Enters the field: %s\n", equipo1[i1].nombre);
            }
        }
        
        pausa();
    }
    
     if(idioma == 1) printf("\n========== RESULTADO FINAL ==========\n");
    else printf("\n========== FINAL RESULT ==========\n");
    if(i1 >= 5 && i2 >= 5)
    {
        if(idioma == 1) printf("EMPATE\n");
        else printf("DRAW\n");
    }
    else if(i1 >= 5)
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
//Una chuleta xd de lo que se le agrego 
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
        printf("1. Conectivos AND (&&): if(reinoA==Ceniza && reinoD==Sombra)\n");
        printf("2. Cuantificadores: while(i1<5 && i2<5)\n");
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
        printf("1. AND connectives (&&): if(kingdomA==Ceniza && kingdomD==Sombra)\n");
        printf("2. Quantifiers: while(i1<5 && i2<5)\n");
        printf("3. Set Theory: Classification by kingdoms\n");
        printf("\nELEMENTAL ADVANTAGE:\n");
        printf("Ceniza > Sombra > Vacio > Luz > Ceniza\n");
        printf("Strong: x1.5  |  Weak: x0.8\n");
    }
    if(idioma == 1) printf("========================================\n");
    else printf("========================================\n");
}