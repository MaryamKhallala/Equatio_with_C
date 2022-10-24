#include<stdio.h>
#include<stdlib.h>
#define MAX(a, b) a < b ? b : a

/*
Définition :
	l'Union adoptée pour representer
l'information de l'arbre utiliser.
*/
typedef union
{
	float nombre;    // champs qui represente les operandes
	char opperation; // champs qui represente les operations
}valeur;			// le nom de l'union

/*
Definition:
	La structure adoptée pour representer un Noeud
  de l'arbre.

Description:
	Chaque nœud de l'arbre est un objet constitué :
  * d'un champ de données.
  * d'un pointeur vers le fils gauche
  * d'un pointeur vers le fils droit
*/
typedef struct arb
{
	valeur info;	// l'information a inserer de type valeur
	struct arb *fg;	// fils gauch
	struct arb *fd;	// fils droit

}ARBRE;				// le noms de l'arbre

/****************  int est_chiffre(char )  *****************
Entrées:  caractere
Sorties: entier
principe:
	Tester si le caractere passer en parametre , est dans
  l'intervale [0,9] et retourner 1, sinon retourner 0.
**********************************************************/


int est_chiffre(char c)
{
	// test sur le caractere passer en parametre
	// retourne 1 si le test est VRAI
	if( (48 <= c) && (c <= 57)) return((int)1);
	// retourne 0 si le test est FAUX
	return ((int)0);
}

/**************** int est_opperation(char ) **************
Entrées: caractere
Sorties: entier
Fonctionnement:
	tester si le caractere passer en parametre est une
 operation arrithmetique , retourner 1 si vrai , sinon
 retourner 0.
**********************************************************/

int est_opperation(char c)
{
	// tester le caractere saisie s'il est une operation
	// retourner 1 si vrai
	if(c=='*' ||c=='+' || c=='-' || c=='/') return ((int)1);
	//sinon retourner 0
	return((int)0);
}

/***************int val_number(char )*****************
Entrées: caractere
Sorties: entier
**********************************************************/

int val_number(char c)
{
	return ((int) c -48);
}

/********* int calcule_partie_decimale(int ,char )**********
Entrées: entier et caractere
Sorties: entier represente le resultas obtenue
Exemple:
 	int N;
 	int nombre=123;
 	char c= '4';
 	N=calcule_partie_decimale(nombre,c);
 	demarche:
 		N = nombre*10 + val_number(c);
 	output:
 		N= 1234
**********************************************************/

int calcule_partie_decimale(int nombre,char c)
{
	return ((int)nombre*10+val_number(c));
}

/***** float calcule_partie_entiere(float ,char ,float )********
Entrées: 2 reel et un caractere
		float nombre :reel represente le nombre intiale
		float coef : le coefition de multiplication a fais
		char c : le caractere a ajouter au nombre initiale

Sorties: reel represente le resultas obtenue
 exemple:
 	float N;
 	float nombre=123.0;
 	char c= '4';
 	float coef=0.1;
 	N=calcule_partie_entiere(nombre,c,coef);
 	demarche:
 		N = nombre+ coef*val_number(c);
 	output:
 		N= 123.4
**********************************************************/

float calcule_partie_entiere(float nombre,char c,float coef)
{
		return((float) (nombre+(coef*val_number(c))));
}

/****** int calcule_nombre_float(float *,char ,char *)******
Entrées: -pointeur de reel :(float*) dans le quel on met le resultas
         -caractere: le caractere qui nous fait entrer a la fonction
		 -pointeur de caracter : le caratere avec le quel en sort d'elle

Sorties: -entier qui designe le fonctionnement de la fonction
	 		1 si tous ca ce passe bien
		    0 sinon
	 	 -resultas de la fonction est mis dans une variable
	 	reel passer on parametre comme pointeur ( *resultas).
	 	 - le caratere qui me fais sortie de la fonction du calcule
	 	est mis dans une variable de type char passer on parametre
		comme pointeur (*sorti).
**********************************************************/

int calcule_nombre_float(float *resultat,char entrer,char *sorti)
{
	char current;
	int numbre=0;
	float numbre_float=0.0;
	float coef=1;
	current=entrer;
	// debut du traitement sur le caractere d'entrer
	// soit il est un chiffre ou une vergule
	if(est_chiffre(current) || current == '.')
	{
		while(est_chiffre(current)) // le cas d'un chiffre
		{// calcule de la partie decimale
			numbre=calcule_partie_decimale(numbre,current);
			//refaire la lecture du caractere suivant tant qu'on a des espace
			// pour les eviter.
			do current=getchar(); while(current == ' ');
		}
		if(current== '.') // le cas d'une vergule
		{
			current=getchar();// lecture du caractere qui suit la vergule
			// retourner 0 si on a deux vergule qui ce suive
			if(current == '.') return 0;
			//refaire la lecture du caractere suivant tant qu'on a des espace
			// pour les eviter.
			while(current== ' ') current=getchar();
			// retourner 0 si on a une autre vergule
			if(current == '.') return 0;

			// le cas de saisie de chiffre apres la vergule
			while(est_chiffre(current))
			{	// le calcule de la partie entiere
				coef*=0.1; // multiplier a chaque fois le coef par 0.1
				// faire appel a la fonction du calcule de cette partie
				// en passe le nombre_float qui joue le role du nombre initale
				// avec le caractere lu (current)
				// meme le coef a multiplier
				numbre_float=calcule_partie_entiere(numbre_float,current,coef);
				//refaire la lecture du caractere suivant tant qu'on a des espace
				// pour les eviter.
				do current=getchar(); while(current == ' ');
				// retourner 0, si apres un certains espace saisie on a vergule
				if(current == '.') return 0;
			}//fin while(est_chiffre(current))
		}//fin if(current== '.')
		numbre_float+=numbre;  // ajouter la partie decimale à la partie entiere
		*resultat=numbre_float;// pointer sur le resultas obtenue
		*sorti=current;        // pointer sur le caractere qui nous fait sorti
		return 1;			   // retourner 1 mentrons que tout est bien passer
	} // fin if(est_chiffre(current) || current == '.')
}// fin fonction


/***** float calcule_opperation(float , char , float )********
Entrées: 2 reel represente les operandes et un caractere designe
	l'operation a fair.
Sorties: reel , resultas de l'operation fait.
**********************************************************/

float calcule_opperation(float a, char op , float b)
{
	switch (op)
	{
		case '+' : return((float)a + b) ;
		case '-' : return ((float)a-b);
		case '/' : return ((float)a / b);
		case '*' : return ((float)a * b);
	}
}



/********** float calcule_arbre(ARBRE* )******************
Entrées: arbre a traite.
Sorties: reel qui represente le resultas obtenue,apres le
	parcous infixe de l'arbre.
Fonctionnement:




**********************************************************/

float calcule_arbre(ARBRE* arb)
{
	// declaration des variables qui vas contenir les resultas du SAG & SAD
	float res_gch,res_dt;
	// declaration du caractere qui vas contenir l'operation a effectuer
	char op;

	if(arb) // si l'arbre n'est pas vide
	{
		res_gch = calcule_arbre(arb->fg);// calcule du SAG
		res_dt = calcule_arbre(arb->fd);//  calcule du SAD
		op = arb->info.opperation;      // operation a effectuer

		// si la donner du noeud est un chiffre en le retourne
		// condition d'arret
		if ( verife(arb->info) ) return ((float)(arb->info.nombre));
		// si non fait l'appel de la fonction avec le resultas
		// du SAG et SAD avec l'operation qu'on dans la racine
		printf ("\n\n*************************************************\n\n");
		affichage_arbre(arb,0);
		printf ("\n\n*************************************************\n\n");
		return ((float) calcule_opperation(res_gch, op ,res_dt));
	}//fin if(arb)
	else return 0; // retourner 0 si l'arbre est vide
}// fin du fonction calcule_arbre(arbre *arb)

/************ int verife(valeur) ****************
Entrées: variable de type union
Sorties: eniter qui soit 0 si c'est operation
		 sinon 1 ,le cas d'un reel.
Fonctionnement:
	Cette fonction a l'interet de verifier un champs
 de l'union , si c'est une operation en retourne 0
 sinon en retourne 1 (le cas d'un reel).
**********************************************************/

int verife(valeur val)
{
	// si le champs opperation d'union est une operation retourne 0
	if(est_opperation(val.opperation)) return 0;
	//sinon retourne 1
	return 1;
}

/************ARBRE * creer_noeud(valeur var)*****************
Entrées: variable de type union (valeur)
Sorties: arbre ( le Noeud creer)
Fonctionnement:
	Cette fonction sert a construire un noeud , on mettent
 le valeur passer en parametre dans le champs de donnée
 du noeud , et initialiser SAD et SAG à NULL,tous ça apres
 faire l'allocation dynamique de ce Noeud, et en le retourne .
**********************************************************/

ARBRE * creer_noeud(valeur var)
{
	ARBRE * noeud; // declaration du noeud
	noeud = (ARBRE*) malloc(sizeof(ARBRE));// l'allocation dynamique du noeud
	if(!noeud) //Erreur de la location
	 {
	 	printf("\n\a Erreur d'allocation du Noeud ");
	 	exit(1);
	 }
	noeud->info = var; // met la donne de le champs info du noeud
	noeud->fg = NULL; // initaliser SAG à NULL
	noeud->fd = NULL; // initaliser SAD à NULL
	return noeud;     // retourner le noeud creer
}

/********** ARBRE * free_arb(ARBRE* )*************
Entrées: une arbre
Sorties: arbre vide
Fonctionnement:
	Le deroulement , commence a vider sous arbre gauche ,
 puis le sous arbre droit et finalement la racine .
 	Finnalement on met l'arbre a NULL pour assurer quand
 va retourner un arbre vide .
**********************************************************/

ARBRE * free_arb(ARBRE* arb)
{
	if (arb)
	{
		arb->fg= free_arb(arb->fg); // vider l'arbre gauch
		arb->fd = free_arb(arb->fd); // vider l'arbre droit
		free(arb);					 // vider la racine
	}
	arb = NULL;						// pointer l'arbre a NULL
	return arb;						// retourner l'arbre resulta
}

/**********ARBRE * inserer_arbre(ARBRE *, valeur)***********
Entrées:- arbre dans lequel on vas inserer
		- la donnée a inserer de type union(valeur)

Sorties: - arbre resultat , apres faire l'insertion
Fonctionnement:
	Cette fonction sert à inserer un nouveau noeud dans la bonne
place selon sa nature et son ordre de priorité s'il s'agit d'une
opération.
	Le stockage et l'évaluation de l'expression se complètent
l'un l'autre, le stockage est fait de telle façon à ce
que l'évaluation se fait dans le sens:
gauche->racine->droite.
	L'insertion dans cette fonction ce base sur la nature de
l'element a inserer , le probleme ce pose au cas des operations
car il faut bien gerer la priorité de ces derniers, generalement
s'il s'agit d'une '+' ou '-' on met ce noeud comme nouvelle racine
de l'arbre , et s'il s'agit d'une '*' ou '/'  en remplace le noeud
actuelle par le nouveau noeud a inserer et le reste de l'arbre reçoit
SAG de ce noeud.
**********************************************************/

ARBRE * inserer_arbre(ARBRE * mon_arb, valeur var)
{
	ARBRE * arb = mon_arb;	  // pointeur sur la racine de l'arbre a traiter
	ARBRE * noeud = NULL;     // le noeud a inserer
	noeud = creer_noeud(var); // la creation du noeud avec la donnée (var)
	if (!arb) return noeud;   // si l'arbre est vide retourner le noeud creer
	if (verife(var))          // si la donnée a inserer est un chiffre
	{
		while (arb->fd) arb = arb->fd; // on part jusqu'a le dernier fils dt
		arb->fd = noeud;     // on insere le noeud creer comme un fils dt
	}//fin if (verife(var))
	else
	{// si la donnée a inserer est une operation besoin de traitement des
	 // priorité
	 	// si l'operation est '*' ou '/'
		if ((var.opperation == '*') || (var.opperation == '/'))
		{
			if (!mon_arb->fd)
			{ // si l'arbre n'a pas un fils dt
				noeud->fg = mon_arb; // SAG du noeud creer reçoit l'arbre
				return noeud;// retourner la nouvelle arbre
			}// fin if (!mon_arb->fd)
			else if (!mon_arb->fd->fd)
			{// si non si l'arbre a un seul fils dt
				if (mon_arb->info.opperation == '/')
				{// si la donnée du noeud est : '/'
					noeud->fg = mon_arb; // SAG du noeud creer reçoit l'arbre
					return noeud; // retourner la nouvelle arbre
				}// fin if (mon_arb->info.opperation == '/')
				else
				{// si la donnée du noeud est different du  '/'
					// on part jusqu'à un noeud qui posséde 2 fils dt
					while (arb->fd->fd)arb = arb->fd;
					// on point SAG du noeud creer sur la S-A qui reste
					noeud->fg = arb->fd;
					//et en remplace la racine de cette S-A par le noeud creer
					arb->fd = noeud;
				}
			}// fin else if (!mon_arb->fd->fd)
			else
			{// sinon si SAD  a plus que deux fd
				// on boucle jusqu'à s'arret sur un ancetre
				// un noued qu'a 3 fils dt
				while (arb->fd->fd->fd) arb = arb->fd;
				// test sur le continue de ce noeud
				if (arb->fd->info.opperation == '/')
				{// si c'est un '/'
					// pointer le SAG du noeud creer sur l'arbre dt pointer
					noeud->fg = arb->fd;
					// remplacer ce racine par le noeud creer
					arb->fd = noeud;
				}//fin if (arb->fd->info.opperation == '/')
				else
				{// si arb->fd->info.opperation != '/'
					arb = arb->fd;
					noeud->fg = arb->fd;
					arb->fd = noeud;
				}//fin else
			}
		}//fin if ((var.opperation == '*') || (var.opperation == '/'))
		else
		{// si l'operation a inserer est '+' ou '-'
		   // le noeud creer reçoit la racine & l'ancienne arbre reçoit leur fg
			noeud->fg = mon_arb;
			// retourner la nouvelle arbre
			return noeud;
		}// fin else
	}

	return mon_arb; // retourner l'arbre resultat
}//fin de inserer_arbre(ARBRE * mon_arb, valeur var)

/************ARBRE* lecture_opperation_arithmetique()*******
Entrées: les caractere a lire du buffer et les traiter
Sorties: arbre dans lequel on stocke l'operation arithmetique
Fonctionnement:




**********************************************************/

ARBRE* lecture_opperation_arithmetique()
{
	ARBRE* arb = NULL;	// arbre dans lequel on stock
	// current : variable à stocker le caractere lu
	//operation: variable à stocker l'opperation a faire
	char current, operation;
	//etat:indicateur de traitement du chiffre saisie 1 tout bien passer 0 sinon
	//signe: indicateur du signe d'un operande -1 negative, 1 positif
	//der_operation:indicateur qui montre si la formule termine par operation
	int etat=1,signe = 1,der_operation = 0;
	float number_float=0.0;	//number_float : reel à stocker la valeur saisie
	valeur var;	// la donnée a inserer dans l'arbre
	current = getchar(); // lecture du premier caratere
	while(current==' ') current=getchar();// eviter tous les espaces
	if(current=='-' || current=='+')
	  { // si le premier caractére lu '-' ou '+'
	  	// on les considére comme signe
		if(current=='-') signe*=-1; // si '-' le signe reçoit -1
		current=getchar(); //lecture du caratére qui le suit
		while(current==' ') current=getchar(); //eviter les espaces
		while(current=='-' || current=='+')
			{// tant que on a une suite des operations '+' ou '-'
				// on les considere comme signe
			  if(current=='-') signe*=-1;
			  current=getchar(); // lecture de caractere qui le suit
			}// fin while(current=='-' || current=='+')
		if ((current == '*') || (current == '/'))
			{// si le caractere est un '*' ou'/'
				printf("Erreur operation succesive !!\n");// signialer erreur
				arb = free_arb(arb);		    // assurer de vider l'arbre
				return arb; 					 // retourner l'arbre vide
			}//fin if ((current == '*') || (current == '/'))
   	  }//fin if(current=='-' || current=='+')
	if ((current == '*') || (current == '/'))
	  {// si on commence par '*' ou '/'
		printf("Erreur operation debut !!\n"); // signialer erreur
		arb = free_arb(arb);   // assurer de vider l'arbre
		return arb;         // retourner l'arbre vide
	  }	// fin if ((current == '*') || (current == '/'))
	while (current != '\n')
	{
		// intialiser a chaque fois indicateur de la dernier operation
		der_operation = 0;
		//  initialier a chaque fois le nombre a saisie
		number_float=0.0;
		if ( est_chiffre(current) || current=='.' )
		{// si on lit un chiffre ou une vergule
			//faire l'appel a la fonction du calcule
			//et mettre le caractere du sorti dans current
			etat=calcule_nombre_float(&number_float,current,&current);
			// multiplier le resultas de la fonction par le signe
			number_float = (float)number_float * signe;
			/************** Partis de Gestion d'erreur ************/
			if ((! number_float) && (operation == '/'))
			 {// le nombre saisie est le zero et suivis par l'operation '/'
				printf("Erreur devision par zero !!\n");// signialer erreur
				arb = free_arb(arb);// assurer de vider l'arbre
				return arb;// retourner l'arbre vide
			 }//fin if ((! number_float) && (operation == '/'))
			if(!etat)
			 {// si etat == 0
				printf("Erreur syntaxe du nombre saisie  !!\n"); // signaler erreur
				arb = free_arb(arb);// retourner l'arbre vide
				return arb;// retourner l'arbre vide
			 }//fin if(!etat)
			 // si tout est bien passer
			 // remplir le champ reel d'union par le resultas obtenue
			var.nombre = number_float;
			// inserer la donnée dans l'arbre
			arb = inserer_arbre(arb, var);
		}// fin if ( est_chiffre(current) || current=='.' )
		else
		{
			if (est_opperation(current))
			{// si le caractere est une operation
				// initialiser l'indicateur du signe
				signe = 1;
				//stocker l'operation
				operation = current;
				//eviter les espaces
				do current = getchar();while ( current == ' ');
				while (est_opperation(current))
					{// tant que on saisie autre operation
						if ((current == '*') || (current == '/'))
						{// si c'est '*' ou '/'
							// signaler erreur
							printf("Erreur operation succes !!\n");
							arb = free_arb(arb);// assurer de vider l'arbre
							return arb;// retourner l'arbre vide
						}//fin if ((current == '*') || (current == '/'))
						else // si l'operation lu est '-'
							 // changer encore signe
							if (current =='-') signe *= -1;
							//eviter les espaces
						do current = getchar();	while ( current == ' ');
					}//fin while (est_opperation(current))
				der_operation = 1; // signaler comme dernier operation
				// remplis le champs operation de l'union par operation a inserer
				var.opperation = operation;
				// inserer la donnée dans l'arbre
				arb = inserer_arbre(arb, var);
			}//fin if (est_opperation(current))
		   else
			{// ni operande ni opearation
			  if(current != ' ')
			   {//caractére different d'espace
				 printf("Erreur: caractere non inclut !!\n");//signaler l'erreur
				 arb = free_arb(arb);// assurer de vider l'arbre
				 return arb;// retourner l'arbre vide
			   }
			  current = getchar();
		    }
	    }
	}//fin while (current != '\n')
	if(der_operation && ( (operation == '/') || (operation == '*')
	    || (operation=='+') || (operation=='-') )
	  )
	{
		printf("Erreur operation fin !!\n");//signaler l'erreur
		arb = free_arb(arb);// assurer de vider l'arbre
		return arb;// retourner l'arbre vide
	}// fin if(der_operation && ( (operation == '/')....)
	return arb;// retourner l'arbre resultat
}

/**********void affichage_arbre(ARBRE *arb, int current_niveau, int niveau)
Entrées: - arbre a afficher
		 -entier qui designe le niveau actuelle dans l'arbre
		 -entier qui designe la longeur de l'arbre
Sorties: l'affichage structurer de l'arbre
Fonctionnement:
	Cette fonction sert a afficher l'arbre d'une maniére rassemble vraiment
 a un arbre reel.
 	Cette fonction est recursive , se qui faut le besoin d'une condition d'arret,
 la condition cette fois ce fait sur l'arbre s'il n'est pas vide,on commence
 à faire l'appel du fonction avec SAD, cette appel s'arret dans les feuilles
 avec leur niveau , apres on boucle avec un for pour saisie les espaces par rapport
 à leur niveau , et on affiche le noeud.
 	Puis on passe a faire l'appel avec le SAG  de la meme maniere.
**********************************************************/

void affichage_arbre(ARBRE *arb, int current_niveau)
{
  int i; // l'indice de la boucle for
  if (arb) // si l'arbre est non vide
  {
  	//afficher le SAD
    affichage_arbre(arb->fd, current_niveau + 1);
    // afficher les espace par rapport au niveau courant
    for (i = 0; i < current_niveau; i++) printf("    ");
    //affichage de la donnée du noeud
    //  s'il est entier
    if (verife(arb->info)) printf("%.4f\n", arb->info.nombre);
    // sinon une operation
	else printf("%c\n", arb->info.opperation);
	// afficher le SAG
    affichage_arbre(arb->fg, current_niveau + 1);
  } // fin if (arb)
}

/***********void operation_arithmetique()******************
Entrées: l'operation saisie par l'utilisateur
Sorties: -affichage de l'arbre & le resultas obtenue
		 - au cas d'erreur message d'erreur

**********************************************************/
void operation()
{
	// arbre dans lequel on insere
	ARBRE * arb = NULL;
	char c;// le caractere a stocker ce qu'on tape
	printf("\n***************************************\n");
	printf("\n\t\t\t Programme de calcule de l'operation arithmetique : \n");
	while(1)
		{// boucle pour repeter le programme
			printf("\n\t Saisie votre operation a traiter : \n");
			// lecture de l'operation saisie
			arb=lecture_opperation_arithmetique();
			// si l'arbre est vide , on vide le buffer
			if (!arb)	do c = getchar(); while (c != '\n');
			else
			{// si l'arbre n'est pas vide
				printf("\t\t\t ARBRE DONNEE : \n\n");
				//affichage de l'arbre
  				affichage_arbre(arb, 0);
  				printf("\n\n");
  				//affichage du resultas obtenue
				printf("\nLe resultat est : %.4f\n", calcule_arbre(arb));
			}
			// montrer la fin d'une operation pour tapez une autre
			printf("\n***************************************\n");
		}//fin while(1)
}
int main()
{
	operation();
	return 0;
}
