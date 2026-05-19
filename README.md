#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estructura para guardar los datos de cada personaje
struct Personaje {
    int id;              // numero del personaje
    char nombre[20];     // nombre del personaje
    char reino[10];      // Ceniza, Sombra, Vacio o Luz
    int hp;              // vida actual
    int hp_max;          // vida maxima
    int def;             // defensa actual (escudo)
    int def_max;         // defensa maxima
    int atq;             // ataque base
    int ce;              // costo de energia
};

// Variables globales (las usan todas las funciones)
struct Personaje catalogo[20];   // aqui guardo todos los personajes
int totalPersonajes = 12;        // empieza con 12 personajes base
struct Personaje equipo1[5];     // equipo del jugador 1
struct Personaje equipo2[5];     // equipo del jugador 2
int danioTotal1 = 0;             // daño total que hizo el jugador 1
int danioTotal2 = 0;             // daño total que hizo el jugador 2

// Prototipos de funciones (aviso de que existen)
void cargarCatalogoBase();
void mostrarCatalogo();
void crearPersonaje();
void formarEquipo(struct Personaje equipo[5], int num);
void menuCarta(struct Personaje equipo[5], int num);
float calcularDaño(struct Personaje at, struct Personaje df);
float ventaja(char a[10], char d[10]);
void batalla();
void estadisticas();
int menu();

// Programa principal
int main()
{
    int opcion;
    srand(time(NULL));          // para que los numeros random sean diferentes cada vez
    cargarCatalogoBase();       // cargo los 12 personajes del juego
    
    do
    {
        opcion = menu();        // muestro el menu y pido opcion
        
        switch(opcion)
        {
            case 1:
                crearPersonaje();    // crea un personaje nuevo
                break;
            case 2:
                mostrarCatalogo();   // muestra todos los personajes
                break;
            case 3:
                printf("\nJUGADOR 1\n");
                formarEquipo(equipo1, 1);   // jugador 1 elige sus 5
                printf("\nJUGADOR 2\n");
                formarEquipo(equipo2, 2);   // jugador 2 elige sus 5
                break;
            case 4:
                printf("\nJUGADOR 1\n");
                menuCarta(equipo1, 1);      // jugador 1 usa carta
                printf("\nJUGADOR 2\n");
                menuCarta(equipo2, 2);      // jugador 2 usa carta
                break;
            case 5:
                batalla();                  // empieza la pelea
                break;
            case 6:
                estadisticas();             // muestra los resultados
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while(opcion != 7);   // repite hasta que elija salir
    
    return 0;   // el programa termino bien
}

// Muestra el menu y devuelve la opcion elegida
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
    printf("7.Salir\n");
    printf("Opcion: ");
    scanf("%d", &op);
    return op;
}

// Carga los 12 personajes que ya vienen en el juego
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

// Muestra todos los personajes del catalogo en pantalla
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

// Crea un personaje nuevo con formulas matematicas
void crearPersonaje()
{
    // verifico que haya espacio en el catalogo
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
    
    printf("Nivel (1 a 10): ");
    scanf("%d", &nivel);
    if(nivel < 1) nivel = 1;
    if(nivel > 10) nivel = 10;
    
    // formulas para calcular los atributos (polinomios)
    nuevo.hp = 40 + (nivel * 4);
    nuevo.hp_max = nuevo.hp;
    nuevo.atq = 20 + (nivel * 3) + (nivel * nivel * 0.3);
    nuevo.def = 15 + (nivel * 2) + (nivel * 0.5);
    nuevo.def_max = nuevo.def;
    nuevo.ce = 3 + (nivel / 2);
    nuevo.id = totalPersonajes + 1;
    
    printf("Personaje creado! HP:%d ATQ:%d DEF:%d\n",
           nuevo.hp, nuevo.atq, nuevo.def);
    
    // lo agrego al catalogo
    catalogo[totalPersonajes] = nuevo;
    totalPersonajes++;
}

// Cada jugador elige sus 5 personajes
void formarEquipo(struct Personaje equipo[5], int num)
{
    int ids[5];     // guardo los ids para no repetir
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
                // verifico si ya lo eligio antes
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

// Cartas de potenciacion (se usan antes de la batalla)
void menuCarta(struct Personaje equipo[5], int num)
{
    int op;
    char reinoC[10];
    float a = 1;   // multiplicador de ataque
    float h = 1;   // multiplicador de vida
    float d = 1;   // multiplicador de defensa
    
    printf("Cartas:\n");
    printf("1.LlamaEterna(Ceniza) +25 ATQ -15 DEF\n");
    printf("2.MantoOscuro(Sombra) +20 HP -10 ATQ\n");
    printf("3.AbismoInterior(Vacio) +30 DEF\n");
    printf("4.LuzDeVerdad(Luz) +25 ATQ -15 HP\n");
    printf("0.Ninguna\n");
    printf("Opcion: ");
    scanf("%d", &op);
    
    // elijo la carta y sus efectos
    if(op == 1)
    {
        strcpy(reinoC, "Ceniza");
        a = 1.25;   // +25% ataque
        d = 0.85;   // -15% defensa
    }
    else if(op == 2)
    {
        strcpy(reinoC, "Sombra");
        h = 1.20;   // +20% vida
        a = 0.90;   // -10% ataque
    }
    else if(op == 3)
    {
        strcpy(reinoC, "Vacio");
        d = 1.30;   // +30% defensa
    }
    else if(op == 4)
    {
        strcpy(reinoC, "Luz");
        a = 1.25;   // +25% ataque
        h = 0.85;   // -15% vida
    }
    else
    {
        printf("Sin carta\n");
        return;
    }
    
    // aplico la carta a los personajes del reino elegido
    for(int i = 0; i < 5; i++)
    {
        if(strcmp(equipo[i].reino, reinoC) == 0)
        {
            equipo[i].atq = equipo[i].atq * a;
            equipo[i].hp = equipo[i].hp * h;
            equipo[i].hp_max = equipo[i].hp_max * h;
            equipo[i].def = equipo[i].def * d;
            equipo[i].def_max = equipo[i].def_max * d;
            printf("%s potenciado\n", equipo[i].nombre);
        }
    }
}

// Calcula la ventaja elemental entre reinos
float ventaja(char a[10], char d[10])
{
    // ciclo: Ceniza > Sombra > Vacio > Luz > Ceniza
    
    // casos donde es fuerte (multiplica x1.5)
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Sombra") == 0)
    {
        return 1.5;
    }
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Vacio") == 0)
    {
        return 1.5;
    }
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Luz") == 0)
    {
        return 1.5;
    }
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Ceniza") == 0)
    {
        return 1.5;
    }
    
    // casos donde es debil (multiplica x0.8)
    if(strcmp(a, "Ceniza") == 0 && strcmp(d, "Luz") == 0)
    {
        return 0.8;
    }
    if(strcmp(a, "Sombra") == 0 && strcmp(d, "Ceniza") == 0)
    {
        return 0.8;
    }
    if(strcmp(a, "Vacio") == 0 && strcmp(d, "Sombra") == 0)
    {
        return 0.8;
    }
    if(strcmp(a, "Luz") == 0 && strcmp(d, "Vacio") == 0)
    {
        return 0.8;
    }
    
    // sin ventaja
    return 1.0;
}

// Calcula el daño usando el polinomio que pidio el profesor
float calcularDaño(struct Personaje at, struct Personaje df)
{
    float base, daño;
    
    // polinomio: 2*(ATQ/10)^2 + 3*(ATQ/10) + 5
    base = (2 * (at.atq / 10.0) * (at.atq / 10.0)) + (3 * (at.atq / 10.0)) + 5;
    
    // escalado por energia (simula el logaritmo)
    base = base / (at.ce + 1);
    
    // multiplico para que la batalla no sea tan larga
    base = base * 3;
    
    // aplico la ventaja elemental
    daño = base * ventaja(at.reino, df.reino);
    
    // limites: minimo 15, maximo 60
    if(daño < 15)
    {
        daño = 15;
    }
    if(daño > 60)
    {
        daño = 60;
    }
    return daño;
}

// Simula la batalla completa
void batalla()
{
    int i1 = 0;     // indice del personaje actual del equipo1
    int i2 = 0;     // indice del personaje actual del equipo2
    int turno = 1;  // 1 = ataca jugador1, 2 = ataca jugador2
    float d;        // daño calculado
    int resto;      // daño que pasa a la vida despues de romper el escudo
    
    // restauro la vida y defensa de todos los personajes
    for(int i = 0; i < 5; i++)
    {
        equipo1[i].hp = equipo1[i].hp_max;
        equipo1[i].def = equipo1[i].def_max;
        equipo2[i].hp = equipo2[i].hp_max;
        equipo2[i].def = equipo2[i].def_max;
    }
    
    printf("\n--- BATALLA ---\n");
    
    // mientras ambos equipos tengan personajes vivos
    while(i1 < 5 && i2 < 5)
    {
        printf("\n%s[V:%d D:%d] vs %s[V:%d D:%d]\n",
               equipo1[i1].nombre, equipo1[i1].hp, equipo1[i1].def,
               equipo2[i2].nombre, equipo2[i2].hp, equipo2[i2].def);
        
        if(turno == 1)   // ataca el jugador 1
        {
            d = calcularDaño(equipo1[i1], equipo2[i2]);
            danioTotal1 = danioTotal1 + d;
            printf("J1 ataca: %.0f\n", d);
            
            // defensa activa: primero daño al escudo, luego a la vida
            if(d <= equipo2[i2].def)
            {
                equipo2[i2].def = equipo2[i2].def - d;   // solo daño al escudo
            }
            else
            {
                resto = d - equipo2[i2].def;
                equipo2[i2].def = 0;
                equipo2[i2].hp = equipo2[i2].hp - resto;   // daño a la vida
            }
            turno = 2;   // cambia el turno
        }
        else   // ataca el jugador 2
        {
            d = calcularDaño(equipo2[i2], equipo1[i1]);
            danioTotal2 = danioTotal2 + d;
            printf("J2 ataca: %.0f\n", d);
            
            if(d <= equipo1[i1].def)
            {
                equipo1[i1].def = equipo1[i1].def - d;
            }
            else
            {
                resto = d - equipo1[i1].def;
                equipo1[i1].def = 0;
                equipo1[i1].hp = equipo1[i1].hp - resto;
            }
            turno = 1;
        }
        
        // verifico si alguien murio
        if(equipo2[i2].hp <= 0)
        {
            printf("%s muere\n", equipo2[i2].nombre);
            i2 = i2 + 1;   // pasa al siguiente personaje
        }
        if(equipo1[i1].hp <= 0)
        {
            printf("%s muere\n", equipo1[i1].nombre);
            i1 = i1 + 1;
        }
    }
    
    // muestro el resultado final
    printf("\n--- RESULTADO BATALLA ---\n");
    if(i1 >= 5 && i2 >= 5)
    {
        printf("EMPATE\n");
    }
    else if(i1 >= 5)
    {
        printf("JUGADOR 2 GANA\n");
    }
    else
    {
        printf("JUGADOR 1 GANA\n");
    }
}

// Muestra las estadisticas finales
void estadisticas()
{
    printf("\n--- ESTADISTICAS DE DAÑO ---\n");
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