[Compiler et lancer le programme]

make
./exec

=====================================================================================================================
[Localisation des constantes]

Tout les #define utilisés dans le code sont consultables dans le main.h


=====================================================================================================================
[Charger vos propres images dans le programme]

Dans le même réportoire que ce fichier readme, ouvrez le fichier  "images_directory_path.txt"
Remplacer le chemin indiqué "hall/hall%06d.pgm" par le chemin et le format adéquat.

Exemple 1 : 
Si vos images se trouvent dans "/home/images/"" et que vos images ont comme nom "photoXXX.pgm"
Alors écrivez dans le fichier "images_directory_path.txt" la chaine suivante telle quelle:
/home/images/photo%03d.pgm

Exemple 2 :
Si vos images se trouvent dans "/home/dessin/"" et que vos images ont comme nom "graphXXXXX.pgm"
Alors écrivez dans le fichier "images_directory_path.txt" la chaine suivante telle quelle:
/home/dessin/graph%05d.pgm

Important : pas d'espace ou de retour chariot ou de caractère superflu. Ecrivez seulement le path comme indiqué ci-dessus

Si votre répertoire contient moins de 300  images, il sera surement necessaire de changer le #define NB_IMAGE dans le main.h