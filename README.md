**[Haz clic aquí para ver la Documentación Completa del proyecto (Doxygen)](https://pitauam.github.io/pprog/)**

----------------------------COMO JUGAR AL JUEGO:----------------------------

1) usar 'git clone https://github.com/pitauam/pprog.git' para descargarse el juego

2) navegar a la carpeta 'pprog' en una terminal

3) make

4) make run

5) moverse con 'move next' o 'm n', move right o 'm r'...

6) take nombre_del_objeto (take Sword o drop Sword) (las mayusculas son importantes)

nota: el juego funciona por turnos y por defecto hay 2 jugadores


































----------------------------INSTRUCCIONES PARA DESCARGAR EL REPOSITORIO:----------------------------

A) Acabo de llegar a clase (PC reseteado)
El PC de clase no tiene nada. Tu misión es traer el código de la nube.

Ir a donde quieras trabajar (ej. Escritorio): cd ~/Desktop

Descargar tu proyecto de la nube: git clone https://github.com/pitauam/pprog

Entrar en la carpeta que se acaba de crear: cd pprog

Configurar quién eres (necesario cada vez que el PC se reinicie): git config user.name "el_tuyo" git config user.email "email@estudiante.uam.es"

Abrir el código para empezar a trabajar: code .


B) Ya estoy trabajando y quiero subir mis cambios
Imagina que has modificado game.c y creado object.c. Quieres enviar tus "paquetes" a la cola.

Ver qué archivos has "ensuciado" o creado: git status (Verás los archivos en rojo).

Meter los cambios en la caja (Preparar): git add . (Si haces git status ahora, verás los archivos en verde. Están listos para ser empaquetados).

Cerrar la caja y ponerle etiqueta (El "paquete"): git commit -m "Añadida la lógica de los objetos y arreglado bug en game"

Enviar todos los paquetes acumulados a GitHub (El camión): git push origin main

Username: el_tuyo

Password: [PEGA AQUÍ TU TOKEN ghp_...]

Si tu compañero ha subido algo mientras tú trabajas: Antes de hacer el push, haz siempre un: git pull origin main Esto trae sus paquetes y los junta con los tuyos para que la cola esté al día.

Nota: poner origin main es buena costumbre porque le dice a git donde enviarlo exactamente evita sustos

COMANDOS:

------------------------------INICIO------------------------------

git clone https://github.com/pitauam/pprog  
cd pprog

git config user.name "tu_nombre_de_github"
git config user.email "tu_email@estudiante.uam.es"

code .

------------------------------GUARDAR CAMBIOS------------------------------

git status
git add .   (o archivo.c si quieres subir solo uno)
git commit -m "describe tus cambios"
git pull origin main
git push origin main

------------------------------MERGE CONFLICTS------------------------------

Si aparece un error amarillo (merge conflict):

git config --global pull.rebase false
git pull

Revisa los archivos marcados con M, elige qué cambios conservar y guarda.
(ctrl+x para salir del editor si aparece)

------------------------------RAMAS------------------------------

Ver ramas:
git branch -a

Cambiar de rama:
git switch nombre_rama

Crear rama nueva:
git switch -c nombre_rama

Subir rama nueva:
git push --set-upstream origin nombre_rama

Traer cambios de main a tu rama (sin fusionar):  
git fetch origin
git rebase origin/main

(Si hay conflictos, arréglalos y continúa con: git rebase --continue)

------------------------------JUNTAR RAMA SECUNDARIA CON MAIN------------------------------

---Paso 1: Guarda tus cambios en tu rama
git add game.c game_actions.c
git commit -m "Fix: errores corregidos e integración It3"

---Paso 2: Cambia a main
git switch main

---Paso 3: Actualiza main
git pull origin main

---Paso 4: Fusiona
git merge ej1
(Si aparece un editor, ctrl+x y Enter)

---Paso 5: Sube la fusión
git push origin main

------------------------------DESTRUIR RAMA------------------------------

Desde main, elimina la rama local:
git branch -d ej1

------------------------------ERRORES------------------------------

"error: failed to push some refs"
Tu rama no tiene upstream:
git push --set-upstream origin nombre_rama