#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//La estructura de datos, lo que llevan los personajes 
// Estructura para guardar los datos de cada personaje
struct Personaje {
    int id;
    char nombre[20];
    char reino[10];
    int hp;
    int hp_max;
    int def;
    int def_max;
    int atq;
    int ce;
};

// Variables globales 
//struct personaje es una estructura que le caben 20 personajes, en teoría nuestro catálogo es de 12, así que el usuario puede crear hasta 8 personajes si gusta
struct Personaje catalogo[20];
int totalPersonajes = 12;
struct Personaje equipo1[5];
struct Personaje equipo2[5];
int danioTotal1 = 0;
int danioTotal2 = 0;
int equiposListos = 0;

// Prototipos de funciones las que use 
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

//el corazón de este código, use el switch para los casos posibles, más un ciclo while que hace que usuario o jugador en este caso, elija un número del 1 al 8 
int main()
{
    int opcion;
    srand(time(NULL));
    cargarCatalogoBase();
    
    do
    {
        opcion = menu();
        
        switch(opcion)
        {
            case 1:
                crearPersonaje();
                break;
            case 2:
                mostrarCatalogo();
                break;
            case 3:
                printf("\nJUGADOR 1\n");
                formarEquipo(equipo1, 1);
                printf("\nJUGADOR 2\n");
                formarEquipo(equipo2, 2);
                equiposListos = 1;
                break;
            case 4:
                printf("\nJUGADOR 1\n");
                menuCarta(equipo1, 1);
                printf("\nJUGADOR 2\n");
                menuCarta(equipo2, 2);
                break;
            case 5:
                if(equiposListos == 0)
                {
                    printf("\nNo has formado equipos. Se asignaran personajes al azar.\n");
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
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while(opcion != 8);
    
    return 0;
}

void pausa()
{
    printf("\nPresione ENTER para continuar...");
    getchar();
    getchar();
}

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
    
    printf("\n--- EQUIPO 1 (Aleatorio) ---\n");
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

void crearPersonaje()
{
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
    
    // Validacion del nivel (1 a 5)
    printf("Nivel (1 a 5): ");
    scanf("%d", &nivel);
    
    while(nivel < 1 || nivel > 5)
    {
        printf("ERROR: El nivel debe ser entre 1 y 5.\n");
        printf("Nivel (1 a 5): ");
        scanf("%d", &nivel);
    }
    
    // Formulas polinomiales
    nuevo.hp = 40 + (nivel * 4);
    nuevo.hp_max = nuevo.hp;
    nuevo.atq = 20 + (nivel * 3) + (nivel * nivel * 0.3);
    nuevo.def = 15 + (nivel * 2) + (nivel * 0.5);
    nuevo.def_max = nuevo.def;
    nuevo.ce = 3 + (nivel / 2);
    nuevo.id = totalPersonajes + 1;
    
    printf("Personaje creado! HP:%d ATQ:%d DEF:%d\n",
           nuevo.hp, nuevo.atq, nuevo.def);
    
    catalogo[totalPersonajes] = nuevo;
    totalPersonajes++;
}

void formarEquipo(struct Personaje equipo[5], int num)
{
    int ids[5];
    int id;
    int cont = 0;
    
    mostrarCatalogo();
    
    while(cont < 5)
    {
        printf("ID %d: ", cont + 1);
        scanf("%d", &id);
        
        int encontrado = 0;
        int repetido = 0;
        
        for(int i = 0; i < totalPersonajes; i++)
        {
            if(catalogo[i].id == id)
            {
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

void batalla()
{
    int i1 = 0;
    int i2 = 0;
    int turno = 1;
    float d;
    int resto;
    
    for(int i = 0; i < 5; i++)
    {
        equipo1[i].hp = equipo1[i].hp_max;
        equipo1[i].def = equipo1[i].def_max;
        equipo2[i].hp = equipo2[i].hp_max;
        equipo2[i].def = equipo2[i].def_max;
    }
    
    printf("\n========== BATALLA ==========\n");
    
    while(i1 < 5 && i2 < 5)
    {
        printf("\n----------------------------------------\n");
        printf("%s vs %s\n", equipo1[i1].nombre, equipo2[i2].nombre);
        printf("[J1] %s V:%d D:%d | [J2] %s V:%d D:%d\n",
               equipo1[i1].nombre, equipo1[i1].hp, equipo1[i1].def,
               equipo2[i2].nombre, equipo2[i2].hp, equipo2[i2].def);
        
        if(turno == 1)
        {
            printf("\n>>> JUGADOR 1 ATACA <<<\n");
            d = calcularDaño(equipo1[i1], equipo2[i2]);
            danioTotal1 = danioTotal1 + d;
            printf("Daño causado: %.0f\n", d);
            
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
        else
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
        
        pausa();
    }
    
    printf("\n========== RESULTADO FINAL ==========\n");
    if(i1 >= 5 && i2 >= 5) printf("EMPATE\n");
    else if(i1 >= 5) printf("JUGADOR 2 GANA LA BATALLA\n");
    else printf("JUGADOR 1 GANA LA BATALLA\n");
}

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