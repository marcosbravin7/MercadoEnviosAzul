# HubFlow — Sistema de gestión de envíos de última milla

Prototipo de consola en C++ para administrar los envíos de un centro de distribución: registro, cola de prioridad, historial de movimientos y resumen recursivo por zona. Trabajo Práctico Integrador — Estructuras de Datos y POO.

> Este documento reemplaza/concilia lo que había repartido entre el Google Docs del equipo y el repo de GitHub (`marcosbravin7/MercadoEnviosAzul`), que estaban desincronizados. El detalle de qué se resolvió y cómo está más abajo.

## Compilar y ejecutar

```bash
# Programa principal
g++ -std=c++17 -Wall -Wextra -o HubFlow main.cpp
./HubFlow

# Tests
g++ -std=c++17 -Wall -Wextra -I. -o HubFlowTests tests/test_main.cpp
./HubFlowTests
```

También se puede abrir con CMake (`CMakeLists.txt` ya define ambos targets: `HubFlow` y `HubFlowTests`).

## Estructura

| Archivo | Responsabilidad |
|---|---|
| `Estados.h` | `enum class Estado`, `enum class NivelServicio` y helpers de conversión |
| `Movimiento.h` | Evento individual del historial de un envío |
| `HistorialDeMovimientos.h` | Lista doblemente enlazada del historial de un envío |
| `Envio.h` | Paquete (código, destinatario, zona, peso, nivel, estado, historial) |
| `ListaDeEnvios.h` | Lista simplemente enlazada — **dueña única** de todos los `Envio*` (pendientes y despachados) |
| `ListaPendientes.h` | Cola de prioridad estable (lista simplemente enlazada, no dueña) — ordena por nivel de servicio |
| `CentroDeDistribucion.h` | Controlador principal, coordina `ListaDeEnvios` + `ListaPendientes` |
| `main.cpp` | Menú de consola |
| `tests/test_main.cpp` | Tests de los 7 casos obligatorios de la consigna |

## Qué se concilió

- **Conflicto de diseño**: el boceto (`docx/image.webp`) y la tabla de clases del Google Docs decían que `ListaDeEnvios` debía ser la dueña de los `Envio*`, pero las respuestas de "Ownership y memoria" del mismo documento decían que `CentroDeDistribucion` los administraba con un array crudo. Se adoptó `ListaDeEnvios` (coincide con el boceto y con lo que ya se había empezado en GitHub).
- El repo de GitHub no compilaba (tipos inexistentes, un método con 3 nombres distintos en 3 archivos, `main.cpp` con una variable sin declarar, cuerpos de función vacíos). Se reescribió `CentroDeDistribucion` y `main.cpp` desde cero, tomando el resto de las clases (`Envio`, `HistorialDeMovimientos`, `ListaDeEnvios`, la recursividad) de esa base porque estaban mejor encapsuladas.
- `ListaPendientes::despachar` en GitHub aceptaba un código (dejaba despachar cualquier ítem, no solo el primero), lo cual contradice la consigna (RF05). Se volvió a la versión sin parámetro.
- Se unificó la nomenclatura: `enum class Estado` (antes `Estado` en local vs `Estados` en GitHub), getters en `Envio` en vez de campos públicos.
- El borrador viejo en la sección "10. Código Fuente" del PDF del equipo (`NodoSimple`/`ListaDoble` con variables mezcladas `head`/`head2`/`cabeza`) quedó afuera: es trabajo exploratorio ya superado.
- **`despachar`/`reprogramar` (lo que preguntaba el equipo)**: la lógica de la cola de prioridad (`ListaPendientes::despachar`/`reprogramar`) la escribió Marcos Bravin sobre la base de Lisandro Menendez, y está bien. Lo que faltaba era el cableado: `CentroDeDistribucion::despacharProximoEnvio()` y `reprogramarEnvio()` los había creado Zoe Corral pero los dejó vacíos (`{}`), nunca llamaban a `ListaPendientes`. Ya está resuelto — son los métodos `despacharProximo()`/`reprogramarEnvio()` de `CentroDeDistribucion.h`, cubiertos por los Casos 3 y 4 de los tests.
- Se agregó `= delete` al constructor de copia de `Envio`, `HistorialDeMovimientos` y `ListaPendientes` (regla de los tres): manejan punteros crudos con destructor propio, y sin esto una copia accidental terminaría en doble `delete`.
- RF07: si se marca `ENTREGADO` con "cambiar estado" sin pasar por "despachar", ahora se saca automáticamente de la lista de pendientes (antes quedaba colgado ahí).

## To-do

### Código
- [ ] Decidir si suben esta versión reconciliada al repo de GitHub (el que está ahí actualmente no compila)
- [ ] Correr `HubFlowTests` y pegar la salida como evidencia en el documento de entrega

### Documento de entrega (Google Docs)
- [ ] Completar roles/responsabilidades de María Emilia, Marcos, Pedro y Mateo en la tabla de integrantes (solo Zoe, Ángela y Santiago la completaron)
- [ ] "Organización del equipo" — está vacío
- [ ] Corregir las respuestas de "Ownership y memoria" (sección 3): decir que `ListaDeEnvios` es la dueña de los `Envio*`, no `CentroDeDistribucion`
- [ ] Completar 3 filas vacías de la tabla de Análisis Big O: **Insertar un nuevo envío**, **Despachar primer envío**, **Reinsertar reprogramado**
- [ ] Pegar la tabla de "Casos de prueba" de más abajo
- [ ] "Conclusiones" (dificultad principal, decisión de diseño, error de punteros, cómo escalarían) — sin responder
- [ ] Borrar el borrador viejo de la sección "10. Código Fuente" del doc y reemplazarlo por el código final
- [ ] Decidir si el boceto a mano (`image.webp`) es el diagrama final de la sección 2.2/9.2 o si quieren uno más prolijo

## Tabla de casos de prueba

Resultados obtenidos corriendo `HubFlowTests` (25/25 checks OK, verificado también con AddressSanitizer/UBSan sin fugas de memoria). Lista para pegar en la tabla del documento de entrega.

| Caso | Operación realizada | Resultado esperado | Resultado obtenido |
|---|---|---|---|
| 1 — Prioridades | Registrar envíos ESTANDAR, EXPRESS y PRIORITARIO y mostrar pendientes | La lista queda ordenada EXPRESS > PRIORITARIO > ESTANDAR | OK — orden correcto |
| 2 — Prioridad estable | Registrar 3 envíos con el mismo nivel de servicio y mostrar pendientes | Se conserva el orden de llegada entre elementos de igual prioridad | OK — orden de llegada conservado |
| 3 — Despacho | Despachar el primer envío pendiente | Cambia a EN_REPARTO, se crea el movimiento en el historial, se elimina el nodo de pendientes, el objeto Envío se conserva y sigue siendo consultable | OK — las 4 condiciones se cumplen |
| 4 — Reprogramación | Despachar un envío y luego reprogramarlo | Aumenta `intentos`, se registra el movimiento REPROGRAMADO con la observación, vuelve a pendientes respetando su prioridad | OK — las 4 condiciones se cumplen |
| 5 — Historial directo | Mostrar historial de un envío con varios movimientos | Recorrido del más antiguo al más reciente (RECIBIDO → CLASIFICADO → EN_REPARTO) | OK — orden cronológico correcto |
| 5 — Historial inverso | Mostrar historial de un envío con varios movimientos | Recorrido del más reciente al más antiguo, usando los punteros `anterior` | OK — orden inverso correcto |
| 6 — Recursividad | Resumen recursivo por zona con paquetes de distintas zonas y niveles | Cuenta solo los paquetes de la zona pedida, suma el peso correcto, cuenta los EXPRESS de esa zona | OK — cantidad, peso (6kg) y EXPRESS (1) correctos |
| 6 — Desafío opcional | Envío de mayor peso de una zona (recursivo) | Identifica correctamente el envío más pesado de la zona consultada | OK |
| 7 — Lista vacía | Mostrar pendientes / despachar con el centro recién creado | Se informa "no hay envíos pendientes" sin romper el programa | OK |
| 7 — Búsqueda inexistente | Buscar un código que no existe | Se informa "Envío no encontrado" | OK |
| 7 — Código duplicado | Registrar dos veces el mismo código | El segundo registro es rechazado con un mensaje de error | OK |
| 7 — Historial con un único nodo | Mostrar historial de un envío recién creado (sin otros movimientos) | Se muestra un solo movimiento (RECIBIDO) en ambos sentidos | OK |
| 7 — Eliminación del único elemento | Despachar cuando pendientes tiene un solo envío | La lista de pendientes vuelve a quedar vacía | OK |
| 7 — Inserción luego de vaciar la lista | Registrar un nuevo envío después de vaciar pendientes | El nuevo envío se inserta correctamente | OK |
