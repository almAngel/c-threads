# 🧵 Proyecto de Hilos y Mutexes en C

Este es un micro proyecto educativo que demuestra el uso de hilos (threads) y mutexes en C para prevenir condiciones de carrera (race conditions).

## 📋 Descripción del Proyecto

El programa crea 4 hilos que incrementan un contador compartido 100,000 veces cada uno. Utiliza un mutex para sincronizar el acceso al contador y evitar race conditions.

### Características:
- **4 hilos** ejecutándose concurrentemente
- **Contador compartido** protegido por mutex
- **400,000 incrementos** totales (100,000 por hilo)
- **Sincronización** correcta usando `pthread_mutex`

## 🚀 Compilación y Ejecución

```bash
# Compilar
make

# Ejecutar
./threads_demo

# Limpiar archivos generados
make clean
```

## 📝 Conceptos Demostrados

- **Threads (hilos)**: Ejecución concurrente
- **Mutex**: Exclusión mutua para recursos compartidos
- **Race Conditions**: Prevención de condiciones de carrera
- **Sincronización**: Coordinación entre hilos

---

# 🧠 EXAMEN TEÓRICO - Hilos y Mutexes en C

## **PARTE 1: CONCEPTOS BÁSICOS** (20 puntos)

### 1.1 (5 pts) ¿Qué es un hilo (thread) y en qué se diferencia de un proceso?

**RESPUESTA:**
> Un thread es una abstracción que corresponde a un grupo de registros físicos del procesador. Se diferencia de un proceso en que comparte memoria con más hilos, lo que hace que sea fácil compartir información entre ellos. Tanto el hilo como el proceso tienen asignados su grupo de registros y su estado que se guarda mientras no están en funcionamiento.

**✅ EVALUACIÓN: 4.5/5 puntos**
- Excelente explicación sobre registros y memoria compartida
- Buena distinción con procesos
- Detalle menor: también comparten otros recursos como archivos abiertos

### 1.2 (5 pts) ¿Qué es una condición de carrera (race condition)? Da un ejemplo.

**RESPUESTA:**
> Una race condition es cuando dos hilos quieren acceder a un mismo valor y lo cambian a la vez, haciendo que el resultado sea indeterminado (puede cambiar correctamente o puede cambiar erróneamente)

**✅ EVALUACIÓN: 5/5 puntos**
- Definición perfecta: múltiples hilos, mismo recurso, resultado indeterminado
- Bien explicado el comportamiento impredecible

### 1.3 (5 pts) ¿Qué es un mutex y para qué se utiliza?

**RESPUESTA:**
> Un mutex es lo que se conoce como un lock. Lo que hace es prevenir las data race de los hilos, forzando a que el primero que acapara el recurso bloquee el acceso a los demás, y que cuando termine este hilo, desbloquee para que cualquier otro pueda obtenerlo.

**✅ EVALUACIÓN: 5/5 puntos**
- Perfecto: mutex = lock (mutual exclusion)
- Excelente descripción del mecanismo de bloqueo/desbloqueo
- Bien explicado el acceso exclusivo

### 1.4 (5 pts) ¿Qué significa que una sección de código sea "crítica"?

**RESPUESTA:**
> Una sección crítica es aquella que marcamos cuando estamos seguros de que se pueden producir race conditions. Es en la sección crítica donde tenemos que establecer nuestras locks para prevenir race conditions.

**✅ EVALUACIÓN: 5/5 puntos**
- Excelente definición: sección donde pueden ocurrir race conditions
- Perfecto: donde debemos usar locks/mutex

**PARTE 1 COMPLETADA: 19.5/20 puntos** 🎉

---

## **PARTE 2: ANÁLISIS DEL CÓDIGO** (30 puntos)

### 2.1 (10 pts) Explica línea por línea qué hace esta función:
```c
pthread_mutex_lock(&mutex);
counter++;
pthread_mutex_unlock(&mutex);
```

**RESPUESTA:**
> La primera línea bloquea el recurso, la segunda produce el incremento en la variable, y la tercera libera el recurso para los demás threads.

**✅ EVALUACIÓN: 10/10 puntos**
- Perfecto análisis línea por línea
- Correcto entendimiento del flujo de sincronización

### 2.2 (10 pts) ¿Qué pasaría si elimináramos las líneas de `pthread_mutex_lock()` y `pthread_mutex_unlock()`?

**RESPUESTA:**
> Lo que pasaría es que habría comportamiento indeterminado. La variable counter podría incrementarse correctamente o sobreescribirse con el valor anterior y nunca avanzar, por ejemplo.

**✅ EVALUACIÓN: 10/10 puntos**
- Correcto: comportamiento indeterminado
- Perfecto ejemplo: sobreescritura con valor anterior
- Bien entendido: perdida de incrementos

### 2.3 (10 pts) ¿Por qué usamos `pthread_join()` en el main? ¿Qué pasaría si no lo usáramos?

**RESPUESTA:**
> Lo que hace pthread_join es esperar a que todos los hilos finalicen, acabando así con su ciclo de vida.

**✅ EVALUACIÓN: 8/10 puntos**
- Correcto: espera a que terminen los hilos
- Faltó mencionar: sin pthread_join() el programa terminaría antes de que los hilos completen su trabajo

**PARTE 2 COMPLETADA: 28/30 puntos** 🎉

---

## **PARTE 3: PREDICCIONES** (25 puntos)

### 3.1 (10 pts) Con el código actual, ¿cuál será el valor final de `counter`? ¿Por qué?

**RESPUESTA:**
> 400.000 sería el valor final, porque tenemos correctamente bloqueado el recurso global counter, tenemos pthread_join al final para esperar a que cada hilo termine su rutina, y tenemos 4 hilos ejecutando una rutina de 100.000 iteraciones. Por eso el valor esperado es 400.000.

**✅ EVALUACIÓN: 10/10 puntos**
- Perfecto: 400,000 (4 hilos × 100,000 incrementos)
- Excelente razonamiento sobre mutex y sincronización
- Bien identificado el papel de pthread_join()

### 3.2 (15 pts) Si cambiáramos el número de incrementos de 100,000 a 10 y ejecutáramos el programa varias veces, ¿obtendríamos siempre el mismo resultado? Justifica.

**RESPUESTA:**
> El mutex sigue funcionando igual con menos iteraciones, solo que el resultado en este caso sería 40, ya que hay 4 hilos ejecutando un incremento 10 veces cada uno. Pero si la pregunta es si cambia algo: no, no cambia nada por modificar las iteraciones en la rutina.

**✅ EVALUACIÓN: 15/15 puntos**
- Correcto: resultado sería 40 (4 hilos × 10 incrementos)
- Perfecto: el mutex funciona igual independientemente del número de iteraciones
- Excelente conclusión: comportamiento determinístico se mantiene

**PARTE 3 COMPLETADA: 25/25 puntos** 🎉

---

## **PARTE 4: MODIFICACIONES** (25 puntos)

### 4.1 (10 pts) ¿Cómo modificarías el código para que cada hilo imprima cuántas veces ha incrementado el contador cada 25,000 iteraciones?

**RESPUESTA:**
> Se podría poner dentro de la zona crítica un printf que indicara el id del thread y el número de veces que cabe 25000 en counter, haciendo uso del operador división, pero tenemos que asegurarnos también que el resto de la división sea cero con un if y con el operador modulo:
> 
> ```c
> if ((counter % 25000) == 0)
>     printf(%d ha incrementado %d en 25000, thread_id, counter / 25000);
> ```

**✅ EVALUACIÓN: 8/10 puntos**
- Excelente enfoque: usar `counter % 25000 == 0`
- Bien pensado: mostrar progreso con división
- Correcto: poner printf en sección crítica
- Detalle menor: faltaron comillas y especificadores en printf

### 4.2 (15 pts) Diseña una versión del programa que demuestre una race condition (sin mutex). ¿Qué cambios harías y qué resultados esperarías?

**RESPUESTA:**
> Quitaría las locks de la zona crítica y el resultado esperado es indeterminado en cada ejecución. No es algo determinista.

**✅ EVALUACIÓN: 15/15 puntos**
- Perfecto: eliminar pthread_mutex_lock() y pthread_mutex_unlock()
- Correcto: resultado indeterminado en cada ejecución
- Bien entendido: comportamiento no determinista

**PARTE 4 COMPLETADA: 23/25 puntos** 🎉

---

# 🏆 **RESULTADO FINAL DEL EXAMEN**

## **PUNTUACIÓN TOTAL: 95.5/100 puntos**

### **Desglose por Partes:**
- **Parte 1 - Conceptos Básicos:** 19.5/20 ✅
- **Parte 2 - Análisis del Código:** 28/30 ✅  
- **Parte 3 - Predicciones:** 25/25 ✅
- **Parte 4 - Modificaciones:** 23/25 ✅

## **CALIFICACIÓN: SOBRESALIENTE** 🎖️

### **Fortalezas Demostradas:**
- ✅ Excelente comprensión de conceptos fundamentales
- ✅ Perfecto entendimiento de race conditions y mutexes
- ✅ Análisis correcto del comportamiento del código
- ✅ Capacidad para predecir resultados y comportamientos
- ✅ Pensamiento crítico para modificaciones del código

### **Áreas de Mejora:**
- Profundizar en detalles de sincronización (pthread_join)
- Práctica con sintaxis de printf y especificadores de formato

**¡Excelente dominio de hilos y mutexes en C!** 👏

---

## 📚 Recursos Adicionales

### Conceptos Clave:
- **Thread**: Unidad básica de ejecución que comparte memoria
- **Mutex**: Mecanismo de exclusión mutua
- **Race Condition**: Comportamiento indeterminado por acceso concurrente
- **Sección Crítica**: Código que debe ejecutarse de forma atómica

### Funciones Importantes:
- `pthread_create()`: Crear un nuevo hilo
- `pthread_join()`: Esperar a que termine un hilo
- `pthread_mutex_lock()`: Bloquear mutex
- `pthread_mutex_unlock()`: Desbloquear mutex

---

*Proyecto realizado como práctica educativa de programación concurrente en C*
