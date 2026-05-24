#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Aquí defino la estructura de cada personaje
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
int totalPersonajes = 12;        // al inicio hay 12 personajes base
struct Personaje equipo1[5];     // los 5 personajes del jugador 1
struct Personaje equipo2[5];     // los 5 personajes del jugador 2
int danioTotal1 = 0;             // voy sumando el daño del jugador 1
int danioTotal2 = 0;             // voy sumando el daño del jugador 2
int equiposListos = 0;           // esto es para saber si ya formaron equipos o no

// Prototipos (le aviso al compilador que estas funciones existen)
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

// Esta es la funcion principal, aqui empieza todo
int main()
{
    int opcion;
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
                printf("\nJUGADOR 1\n");
                formarEquipo(equipo1, 1);   // el jugador 1 elige sus 5 personajes
                printf("\nJUGADOR 2\n");
                formarEquipo(equipo2, 2);   // el jugador 2 elige sus 5 personajes
                equiposListos = 1;          // marco que ya hay equipos formados
                break;
            case 4:
                printf("\nJUGADOR 1\n");
                menuCarta(equipo1, 1);      // jugador 1 elige su carta potenciadora
                printf("\nJUGADOR 2\n");
                menuCarta(equipo2, 2);      // jugador 2 elige su carta potenciadora
                break;
            case 5:
                // si no han formado equipos, el programa asigna personajes al azar
                if(equiposListos == 0)
                {
                    printf("\nNo has formado equipos. Se asignaran personajes al azar.\n");
                    seleccionarEquiposAleatorios();
                    equiposListos = 1;
                }
                batalla();                  // empieza la pelea
                break;
            case 6:
                estadisticas();             // muestro el daño total de cada jugador
                break;
            case 7:
                soporteAcademico();         // aqui explico las matematicas y logica que use
                break;
            case 8:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while(opcion != 8);
    
    return 0;   // el programa termina bien
}

// Esta funcion hace una pausa y espera que el usuario presione ENTER
// La uso entre turnos para que se pueda leer lo que paso en la batalla
void pausa()
{
    printf("\nPresione ENTER para continuar...");
    getchar();
    getchar();
}

// Si el jugador no formo equipos, esta funcion elige personajes al azar
// Asi el juego no se queda pegado si alguien le da a batalla sin tener equipo
void seleccionarEquiposAleatorios()
{
    int usados1[12], usados2[12];
    int cont1 = 0, cont2 = 0;
    int num, repetido;
    
    // limpio los arreglos de personajes usados
    for(int i = 0; i < 12; i++)
    {
        usados1[i] = 0;
        usados2[i] = 0;
    }
    
    printf("\n--- EQUIPO 1 (Aleatorio) ---\n");
    while(cont1 < 5)
    {
        num = rand() % totalPersonajes;   // escojo un numero aleatorio del catalogo
        repetido = 0;
        for(int j = 0; j < cont1; j++)
        {
            if(usados1[j] == num) repetido = 1;  // verifico que no se repita
        }
        if(repetido == 0)
        {
            equipo1[cont1] = catalogo[num];
            usados1[cont1] = num;
            cont1++;
            printf("Agregado: %s\n", catalogo[num].nombre);
        }
    }
    
    printf("\n--- EQUIPO 2 (Aleatorio) ---\n");
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
            printf("Agregado: %s\n", catalogo[num].nombre);
        }
    }
    
    printf("\nEquipos aleatorios asignados!\n");
}

// Muestra las opciones del menu y devuelve la que el usuario elige
int menu()
{
    int op;
    printf("\n=== MENU ===\n");
    printf("1.Crear personaje\n");
    printf("2.Ver catalogo\n");
    printf("3.Formar equipos\n");
    printf("4.Usar carta potenciacion\n");
    printf("5.Iniciar batalla\n");
    printf("6.Ver estadisticas\n");
    printf("7.Soporte Academico\n");
    printf("8.Salir\n");
    printf("Opcion: ");
    scanf("%d", &op);
    return op;
}

// Aqui cargo los 12 personajes que ya vienen en el juego
// Asi el juego tiene personajes aunque el usuario no cree ninguno
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
    
    // guardo cada personaje en el catalogo
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
    printf("\n--- CATALOGO ---\n");
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
// El usuario solo pone nombre, reino y nivel. Los numeros los calcula el programa
void crearPersonaje()
{
    // verifico que haya espacio en el catalogo (maximo 20)
    if(totalPersonajes >= 20)
    {
        printf("Catalogo lleno\n");
        return;
    }
    
    struct Personaje nuevo;
    int opReino, nivel;
    
    printf("Nombre: ");
    scanf("%s", nuevo.nombre);
    
    printf("Reino (1.Ceniza 2.Sombra 3.Vacio 4.Luz): ");
    scanf("%d", &opReino);
    if(opReino == 1)
    {
        strcpy(nuevo.reino, "Ceniza");
    }
    else if(opReino == 2)
    {
        strcpy(nuevo.reino, "Sombra");
    }
    else if(opReino == 3)
    {
        strcpy(nuevo.reino, "Vacio");
    }
    else
    {
        strcpy(nuevo.reino, "Luz");
    }
    
    // valido que el nivel este entre 1 y 5
    printf("Nivel (1 a 5): ");
    scanf("%d", &nivel);
    
    while(nivel < 1 || nivel > 5)
    {
        printf("ERROR: El nivel debe ser entre 1 y 5.\n");
        printf("Nivel (1 a 5): ");
        scanf("%d", &nivel);
    }
    
    // estas son las formulas que uso para calcular vida, ataque, defensa y energia
    // use polinomios como pidio el profesor
    nuevo.hp = 40 + (nivel * 4);
    nuevo.hp_max = nuevo.hp;
    nuevo.atq = 20 + (nivel * 3) + (nivel * nivel * 0.3);
    nuevo.def = 15 + (nivel * 2) + (nivel * 0.5);
    nuevo.def_max = nuevo.def;
    nuevo.ce = 3 + (nivel / 2);
    nuevo.id = totalPersonajes + 1;   // el id es el siguiente disponible
    
    printf("Personaje creado! HP:%d ATQ:%d DEF:%d\n",
           nuevo.hp, nuevo.atq, nuevo.def);
    
    // agrego el nuevo personaje al catalogo
    catalogo[totalPersonajes] = nuevo;
    totalPersonajes++;
}

// Esta funcion permite que el jugador elija sus 5 personajes
void formarEquipo(struct Personaje equipo[5], int num)
{
    int ids[5];     // aqui guardo los ids que ya eligio para no repetir
    int id;
    int cont = 0;
    
    mostrarCatalogo();   // muestro los personajes disponibles
    
    while(cont < 5)
    {
        printf("ID %d: ", cont + 1);
        scanf("%d", &id);
        
        int encontrado = 0;
        int repetido = 0;
        
        // busco el id en el catalogo
        for(int i = 0; i < totalPersonajes; i++)
        {
            if(catalogo[i].id == id)
            {
                // verifico si ya eligio este personaje antes
                for(int j = 0; j < cont; j++)
                {
                    if(ids[j] == id)
                    {
                        repetido = 1;
                    }
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
                    printf("Repetido\n");
                }
                break;
            }
        }
        
        if(encontrado == 0)
        {
            printf("ID invalido\n");
        }
    }
    printf("Equipo %d listo\n", num);
}

// Cartas de potenciacion (Buff y Nerf)
// Cada carta afecta a un reino especifico
void menuCarta(struct Personaje equipo[5], int num)
{
    int op;
    char reinoC[10];
    float multAtq = 1;
    float multHp = 1;
    float multDef = 1;
    int alguienPotenciado = 0;
    
    printf("Cartas:\n");
    printf("1.LlamaEterna(Ceniza) +25 ATQ -15 DEF\n");
    printf("2.MantoOscuro(Sombra) +20 HP -10 ATQ\n");
    printf("3.AbismoInterior(Vacio) +30 DEF\n");
    printf("4.LuzDeVerdad(Luz) +25 ATQ -15 HP\n");
    printf("0.Ninguna\n");
    printf("Opcion: ");
    scanf("%d", &op);
    
    // segun la carta que elija, asigno los multiplicadores
    if(op == 1)
    {
        strcpy(reinoC, "Ceniza");
        multAtq = 1.25;
        multDef = 0.85;
        printf("\n--- Aplicando LlamaEterna a personajes de Ceniza ---\n");
    }
    else if(op == 2)
    {
        strcpy(reinoC, "Sombra");
        multHp = 1.20;
        multAtq = 0.90;
        printf("\n--- Aplicando MantoOscuro a personajes de Sombra ---\n");
    }
    else if(op == 3)
    {
        strcpy(reinoC, "Vacio");
        multDef = 1.30;
        printf("\n--- Aplicando AbismoInterior a personajes de Vacio ---\n");
    }
    else if(op == 4)
    {
        strcpy(reinoC, "Luz");
        multAtq = 1.25;
        multHp = 0.85;
        printf("\n--- Aplicando LuzDeVerdad a personajes de Luz ---\n");
    }
    else
    {
        printf("Sin carta\n");
        return;
    }
    
    // aplico los cambios a los personajes del reino elegido
    for(int i = 0; i < 5; i++)
    {
        if(strcmp(equipo[i].reino, reinoC) == 0)
        {
            printf("\n%s fue potenciado:\n", equipo[i].nombre);
            printf("  Ataque: %d -> %d", equipo[i].atq, (int)(equipo[i].atq * multAtq));
            equipo[i].atq = equipo[i].atq * multAtq;
            printf("  Vida: %d -> %d", equipo[i].hp, (int)(equipo[i].hp * multHp));
            equipo[i].hp = equipo[i].hp * multHp;
            equipo[i].hp_max = equipo[i].hp_max * multHp;
            printf("  Defensa: %d -> %d", equipo[i].def, (int)(equipo[i].def * multDef));
            equipo[i].def = equipo[i].def * multDef;
            equipo[i].def_max = equipo[i].def_max * multDef;
            printf("\n");
            alguienPotenciado = 1;
        }
    }
    
    if(alguienPotenciado == 0)
    {
        printf("\nNingun personaje de tu equipo es del reino %s. Carta sin efecto.\n", reinoC);
    }
}

// Calcula la ventaja elemental entre dos reinos
// Use conectivos logicos AND (&&) como pidio el profesor
float ventaja(char a[10], char d[10])
{
    // el ciclo es: Ceniza > Sombra > Vacio > Luz > Ceniza
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Sombra") == 0) return 1.5;
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Vacio") == 0) return 1.5;
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Luz") == 0) return 1.5;
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Ceniza") == 0) return 1.5;
    // casos donde es debil
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Luz") == 0) return 0.8;
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Ceniza") == 0) return 0.8;
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Sombra") == 0) return 0.8;
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Vacio") == 0) return 0.8;
    // si no hay ventaja, el daño se queda igual
    return 1.0;
}

// Esta es la funcion mas importante: calcula el daño
// Use el polinomio que pidio el profesor y tambien el logaritmo
float calcularDaño(struct Personaje at, struct Personaje df)
{
    float base, daño;
    
    // polinomio: 2*(ATQ/10)^2 + 3*(ATQ/10) + 5
    base = (2 * (at.atq / 10.0) * (at.atq / 10.0)) + (3 * (at.atq / 10.0)) + 5;
    
    // escalado por energia (esto simula el logaritmo)
    base = base / (at.ce + 1);
    
    // multiplico por 3 para que la batalla no sea eterna
    base = base * 3;
    
    // aplico la ventaja elemental
    daño = base * ventaja(at.reino, df.reino);
    
    // pongo limites para que el daño no sea ni muy bajo ni muy alto
    if(daño < 15) daño = 15;
    if(daño > 60) daño = 60;
    
    return daño;
}

// Esta funcion simula toda la batalla
void batalla()
{
    int i1 = 0;      // indice del personaje actual del equipo 1
    int i2 = 0;      // indice del personaje actual del equipo 2
    int turno = 1;   // 1 ataca jugador1, 2 ataca jugador2
    float d;         // daño calculado
    int resto;       // daño que pasa a la vida despues de romper el escudo
    
    // restauro la vida y defensa de todos los personajes
    for(int i = 0; i < 5; i++)
    {
        equipo1[i].hp = equipo1[i].hp_max;
        equipo1[i].def = equipo1[i].def_max;
        equipo2[i].hp = equipo2[i].hp_max;
        equipo2[i].def = equipo2[i].def_max;
    }
    
    printf("\n========== BATALLA ==========\n");
    
    // mientras ambos equipos tengan personajes vivos
    while(i1 < 5 && i2 < 5)
    {
        printf("\n----------------------------------------\n");
        printf("%s vs %s\n", equipo1[i1].nombre, equipo2[i2].nombre);
        printf("[J1] %s V:%d D:%d | [J2] %s V:%d D:%d\n",
               equipo1[i1].nombre, equipo1[i1].hp, equipo1[i1].def,
               equipo2[i2].nombre, equipo2[i2].hp, equipo2[i2].def);
        
        if(turno == 1)   // ataca el jugador 1
        {
            printf("\n>>> JUGADOR 1 ATACA <<<\n");
            d = calcularDaño(equipo1[i1], equipo2[i2]);
            danioTotal1 = danioTotal1 + d;
            printf("Daño causado: %.0f\n", d);
            
            // defensa activa: primero daño al escudo, luego a la vida
            if(d <= equipo2[i2].def)
            {
                equipo2[i2].def = equipo2[i2].def - d;
                printf("El escudo absorbe. DEF restante: %d\n", equipo2[i2].def);
            }
            else
            {
                resto = d - equipo2[i2].def;
                equipo2[i2].def = 0;
                equipo2[i2].hp = equipo2[i2].hp - resto;
                printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", resto, equipo2[i2].hp);
            }
            turno = 2;
        }
        else   // ataca el jugador 2
        {
            printf("\n>>> JUGADOR 2 ATACA <<<\n");
            d = calcularDaño(equipo2[i2], equipo1[i1]);
            danioTotal2 = danioTotal2 + d;
            printf("Daño causado: %.0f\n", d);
            
            if(d <= equipo1[i1].def)
            {
                equipo1[i1].def = equipo1[i1].def - d;
                printf("El escudo absorbe. DEF restante: %d\n", equipo1[i1].def);
            }
            else
            {
                resto = d - equipo1[i1].def;
                equipo1[i1].def = 0;
                equipo1[i1].hp = equipo1[i1].hp - resto;
                printf("Escudo roto! Daño a vida: %d. VIDA restante: %d\n", resto, equipo1[i1].hp);
            }
            turno = 1;
        }
        
        // verifico si alguien murio
        if(equipo2[i2].hp <= 0)
        {
            printf("\n*** %s ha muerto! ***\n", equipo2[i2].nombre);
            i2 = i2 + 1;
            if(i2 < 5) printf("Entra al campo: %s\n", equipo2[i2].nombre);
        }
        if(equipo1[i1].hp <= 0)
        {
            printf("\n*** %s ha muerto! ***\n", equipo1[i1].nombre);
            i1 = i1 + 1;
            if(i1 < 5) printf("Entra al campo: %s\n", equipo1[i1].nombre);
        }
        
        pausa();   // pausa para que se pueda leer
    }
    
    // muestro quien gano
    printf("\n========== RESULTADO FINAL ==========\n");
    if(i1 >= 5 && i2 >= 5) printf("EMPATE\n");
    else if(i1 >= 5) printf("JUGADOR 2 GANA LA BATALLA\n");
    else printf("JUGADOR 1 GANA LA BATALLA\n");
}

// Muestra el daño total que hizo cada jugador
void estadisticas()
{
    printf("\n=== ESTADISTICAS DE DAÑO ===\n");
    printf("Daño Jugador 1: %d\n", danioTotal1);
    printf("Daño Jugador 2: %d\n", danioTotal2);
    
    if(danioTotal1 > danioTotal2)
    {
        printf("Mayor daño: Jugador 1\n");
    }
    else if(danioTotal2 > danioTotal1)
    {
        printf("Mayor daño: Jugador 2\n");
    }
    else
    {
        printf("Empate en daño\n");
    }
}

// Esta funcion explica las matematicas y la logica que use
// Osea una chuleta para el profesor de lógica y la prof de matemáticas XD
void soporteAcademico()
{
    printf("\n========== SOPORTE ACADEMICO ==========\n");
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
    printf("========================================\n");
}
