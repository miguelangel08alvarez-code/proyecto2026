# Simulador de Batallas - La Gran Carpa de Ceniza

## Descripción
Proyecto final de Introducción a la Informática. Un simulador de batallas por turnos en C donde dos jugadores eligen 5 personajes y se enfrentan.

¿Cómo jugar?
1. Crear personaje (nombre, reino, nivel 1 a 5)
2. Ver catálogo (12 personajes base + los que crees)
3. Formar equipos (5 por jugador, no se pueden repetir)
4. Usar carta potenciadora (Buff o Nerf según el reino)
5. Iniciar batalla (automática, con pausa entre turnos)
6. Ver estadísticas (daño total de cada jugador)
7. Soporte académico (explicación de matemáticas y lógica)
8. Salir

¿Matemáticas usadas?
- **Polinomio**: Daño = 2×(ATQ/10)² + 3×(ATQ/10) + 5
- **Logaritmo**: Daño_base / (CE + 1)
- **Inecuación**: if(daño ≤ defensa) → el escudo absorbe; si no → daño a la vida
- **Valor Absoluto**: La defensa nunca queda negativa

¿Lógica usada?
- **Conectivos AND (&&)** : Para comparar reinos en la ventaja elemental
- **Cuantificadores**: while(i1<5 && i2<5) para ver si hay personajes vivos
- **Teoría de conjuntos**: Clasificación por reinos (Ceniza, Sombra, Vacio, Luz)

Ventaja elemental:
El ciclo es: Ceniza > Sombra > Vacio > Luz > Ceniza
- Si es FUERTE: el daño se multiplica por 1.5
- Si es DÉBIL: el daño se multiplica por 0.8
- Si no hay ventaja: el daño se queda igual

Convenciones de nomenclatura:
- **Variables**: usé español (equipo1, danioTotal1, catalogo)
- **Funciones**: verbos en infinitivo (crearPersonaje, mostrarCatalogo)
- **Estructuras**: con mayúscula inicial (Personaje)
- **Constantes**: números directos

 Indentación usada:
- Usé 4 espacios por nivel
- Las llaves van en la misma línea que la función
- El switch lo puse vertical (cada case en su propia línea)

Estructuras de datos:
- `struct Personaje`: tiene id, nombre, reino, hp, hp_max, def, def_max, atq, ce
- Arreglos: `catalogo[20]` (todos los personajes), `equipo1[5]` y `equipo2[5]` (los equipos)

 Ciclos usados:
- `do-while`: para el menú principal (se repite hasta que elija salir)
- `while`: para la batalla (se repite mientras haya personajes vivos)
- `for`: para recorrer arreglos (mostrar catálogo, buscar personajes)

Fórmulas para crear personajes:
- HP = 40 + nivel × 4
- ATQ = 20 + nivel × 3 + nivel² × 0.3
- DEF = 15 + nivel × 2 + nivel × 0.5
- CE = 3 + nivel ÷ 2

Autores: 
Miguel Álvarez, Richard Arrieta, Ángel Suárez,- Estudiante de Informática - IUJO

## Fecha
Mayo 2026