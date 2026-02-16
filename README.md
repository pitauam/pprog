hola, esto son instrucciones para git:

A) Acabo de llegar a clase (PC reseteado)
El PC de clase no tiene nada. Tu misión es traer el código de la nube.

Ir a donde quieras trabajar (ej. Escritorio): cd ~/Desktop

Descargar tu proyecto de la nube: git clone https://github.com/pitauam/pprog.git

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

---INICIO---

git clone https://github.com/pitauam/pprog.git

cd pprog

git config user.name "tu_nombre_de_github"

git config user.email "tu_email@estudiante.uam.es"

code .

---GUARDAR CAMBIOS---

git status

git add (. si quieres subir todo o archivo.c si quieres subir solo alguno)

git commit -m "escribe los cambios que has hecho aqui"

git pull origin main

git push origin main

