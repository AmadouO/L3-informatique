(* TP1 Logique classique

   ATTENTION
   Pour le bon affichage des caractères accentués, précisez que l'encodage par défaut de votre NAVIGATEUR doit être Unicode (UTF-8)

   BUT DU TP
     - Manipuler Coq / Gallina
     - Se familiariser avec 4 mots-clés :
        + Definition
        + Definition avec match ... with
        + Inductive
        + Fixpoint
     - Premières preuves en logique propositionnelle
*)
        

(* -------------------------------------------------------------------------- *)

(* PRISE EN MAIN DE L'ENVIRONNEMENT *)


(* DÉFINIR UN OBJET (entier, fonction, etc.) *)
(* Mot-clef "Definition" 
   suivi du nom de l'objet
   suivi de ":" 
   suivi du type de l'objet
   suivi de ":="
   suivi de la valeur de l'objet. *)
Definition a : nat := 3.
Definition b : nat := 6.

(* En Coq on donne TOUJOURS les types. *)

(* EFFECTUER UN CALCUL... dans l'interpréteur *)
(* Directive "Compute" *)
(* RÉSULTAT ATTENDU : 9 *)
Compute (a+b).

(* AFFICHER LE TYPE... dans l'interpréteur *)
(* Directive "Check" *)
Check (a+b).

Print a.
Print b.

(* -------------------------------------------------------------------------- *)

(* 1. TYPES ÉNUMÉRÉS ET TYPES INDUCTIFS *)


(* Mots-clefs "Inductive" et "|" par cas. 
   C'est la définition d'un ensemble inductif, on donne des règles...
   Comme on définit un *type* de données, son propre type est Type. *)
Inductive jour : Type :=
  | lundi : jour
  | mardi : jour
  | mercredi : jour
  | jeudi : jour
  | vendredi: jour
  | samedi : jour
  | dimanche : jour.
(* ici uniquement des cas de base *)


(* On peut définir une FONCTION jour_suivant sur ce type.
   (jour_suivant e) s'évalue en le nom du jour suivant le jour e.
   Elle est réalisée suivant *la forme* du paramètre, c'est du
   "filtrage" ou "PATTERN MATCHING". C'est le mécanisme le plus
   confortable pour manipuler des structures inductives. *)
(* Mots-clef "match" "with" "end" *)
Definition jour_suivant (j : jour) : jour :=
  match j with
  | lundi => mardi
  | mardi => mercredi
  | mercredi => jeudi
  | jeudi => vendredi
  | vendredi => samedi
  | samedi => dimanche
  | dimanche => lundi
  end.

(* On teste. RÉSULTAT ATTENDU : jeudi *)
Compute (jour_suivant mercredi).


(* EXERCICE 2 *)
(* Définir la fonction qui retourne le surlendemain d'un jour donné *)
(* C'est une fonction qui APPLIQUÉE À un jour, RETOURNE un jour *)

Definition jour_suivant_le_jour_suivant (j : jour) : jour :=
  jour_suivant (jour_suivant j).

(* On re-teste et on devrait obtenir vendredi*)
(*  *)

Compute (jour_suivant_le_jour_suivant mercredi).
Compute (jour_suivant_le_jour_suivant jeudi).


(* On peut aussi définir les booléens... *)
(* Il n'y a que des cas de base et on va les appeler Vrai et Faux *)
Inductive booleens : Type :=
| Vrai : booleens
| Faux : booleens.

(* Ainsi que les fonctions logiques usuelles. *)
(* Le complémentaire : non. *)
Definition non (a : booleens) : booleens :=
  match a with
  | Vrai => Faux
  | Faux => Vrai
  end.


(* Directive d'affichage de type *)
Check non.

(* Directive d'affichage de valeur *)
Print non.


(* EXERCICE 3 *)
(* Définir la fonction "et" sur les booléens. *)
Definition et (a : booleens) (b : booleens) : booleens :=
  match a, b with
  |Vrai, Vrai => Vrai
  |_, _ => Faux
  end.
  

(* un petit test, RÉPONSE ATTENDUE : Faux *)
Compute (et Vrai (et Faux Vrai)).
Compute et Vrai Vrai.
Compute et Faux Faux.
Compute et Faux Vrai.


(* EXERCICE 4 *)
(* Définir la fonction "ou" sur les booléens. *)
Definition ou (a : booleens) (b : booleens) : booleens :=
  match a, b with
  | Faux, Faux => Faux
  | _, _ => Vrai
  end.

(* RÉPONSE ATTENDUE : Vrai *)
(* Compute (et Vrai (ou Faux Vrai)). *)
Compute ou Faux Faux.
Compute ou Faux Vrai.
Compute ou Vrai Faux.
Compute ou Vrai Vrai.


(* EXERCICE 5 (A FAIRE CHEZ VOUS) *)
(* Définir une fonction bcompose : f -> g -> h telle que h est la composition des
deux fonctions booléennes f et g *)
Definition bcompose (f g : booleens -> booleens) : booleens -> booleens :=
  fun x => f (g x).


(* Tester bcompose en définissant une fonction nonnon : booléens -> booléens qui
définit non o non *)
Definition nonnon : booleens -> booleens :=
  bcompose non non.



(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (nonnon Vrai). *)
(* RÉSULTAT ATTENDU : Vrai *)
Compute (nonnon Vrai).

(* RÉSULTAT ATTENDU : Faux *)
Compute (nonnon Faux).



(* Le langage de Coq a bien sûr des booléens (dans le type prédéfini bool),
   ils sont en fait définis de la même façon que nos booleens. Pour l'instant
   nous allons continuer de travailler avec les nôtres. *)


(* On définit maintenant de façon inductive le type des entiers naturels.
   Un entier naturel est :
   - soit un élément particulier noté Z (pour zéro, c'est un cas de base ici),
   - soit le successeur d'un entier naturel.
 
   On a bien DEUX CONSTRUCTEURS pour les entiers : ils sont soit de la
   *forme* "Z" soit de la *forme* "Succ d'un entier".
*)
Inductive entiers : Type :=
| Z : entiers
| Succ : entiers -> entiers.

Definition un  := Succ Z.
Definition deux  := Succ un.
Definition trois  := Succ deux.

Print trois.


(* EXERCICE 6 *)
(* Définir la fonction prédécesseur *)
(* C'est une fonction qui APPLIQUÉE À un entier, RETOURNE un entier *)
(* On considère que le prédécesseur de quelque chose de la forme Z est... Z *)
(* Le prédécesseur de quelque chose de la forme Succ toto est bien sûr toto *)
Definition pred (n : entiers) : entiers :=
  match n with
  | Z => Z
  | Succ m => m
  end.


(* RÉSULTAT ATTENDU :  Succ (Succ Z) *)
Compute (pred (Succ (Succ (Succ Z)))).


(* On veut écrire une FONCTION RÉCURSIVE pour ajouter deux entiers.
   Comme la fonction est récursive, on utilise le mot-clé Fixpoint (et
   non plus Definition).
   Elle se calcule selon la forme du premier paramètre *) 
Fixpoint plus (a : entiers) (b : entiers) : entiers :=
  match a with
  | Z => b (* si a est un Z zero alors la somme c'est b *)
  | Succ n => Succ (plus n b)
  
    (* Si a est de la forme Succ n, cela signifie que a est le successeur d'un entier n.
      Le résultat est alors obtenu en ajoutant récursivement n à b 
      et en prenant le successeur du résultat.*)
  end.
  (* RÉSULTAT ATTENDU : Succ (Succ (Succ Z)), qui représente 3 *)
Compute (plus (Succ (Succ Z)) (Succ Z)).



(* EXERCICE 7 *)
(* Multiplication
   Elle se calcule selon la forme du premier paramètre *)
Fixpoint mult( a : entiers ) (b : entiers ) : entiers :=
  match a with 
  | Z => Z
  | Succ n => plus b (mult n b )
  end.

(* RÉSULTAT ATTENDU : 9 *)
Compute (mult trois trois).


(* EXERCICE 8 *)
(* Définir une fonction est_pair, telle que est_pair APPLIQUÉE À un entier a RETOURNE Vrai si a est pair, Faux sinon. *)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (est_pair deux). *)

(* RÉSULTAT ATTENDU : Faux *)
(* Compute (est_pair trois). *)


(* EXERCICE 9 (A FAIRE CHEZ VOUS) *)
(* Définir la fonction factorielle sur les entiers *)

(* RÉSULTAT ATTENDU : 24 sous forme de Succ( ... (Succ(Z) ...) *)
(* Compute (factorielle (plus trois un)). *)


(* EXERCICE 10 (A FAIRE CHEZ VOUS) *)
(* Définir la fonction moins, soustraction non négative sur les entiers *)

(* RÉSULTAT ATTENDU : Succ Z *)
(* Compute (moins deux un).*)

(* RÉSULTAT ATTENDU : Z *)
(* Compute (moins deux trois).*)

(* EXERCICE 11 (A FAIRE CHEZ VOUS) *)
(* Définir une fonction inf, tel que inf a b vaut/retourne Vrai si a est
   inférieur ou égal à b, Faux sinon. *)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (inf trois trois). *)


(* EXERCICE 12 (A FAIRE CHEZ VOUS) *)
(* Définir une fonction egal, tel que egal a b donne Vrai si les entiers
   a et b sont égaux, Faux sinon. *)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (egal trois trois). *)

(* RÉSULTAT ATTENDU : Faux *)
(* Compute (egal un trois). *)


(* ------------------------------------------------------------ *)


(* Précédemment, on a défini nos booléens et nos entiers naturels,
mais ils sont en fait déjà définis dans la bibliothèque que Coq charge
initialement au démarrage :

NE PAS DECOMMENTER CE QUI SUIT, CE SONT DES TYPES COQ PREDEFINIS

Inductive bool : Set :=
  | true : bool
  | false : bool.

avec les fonctions 

negb (le complémentaire)
andb (le et, (le min))
orb  (le ou, (le max))

Inductive nat : Set :=
  | O : nat
  | S : nat -> nat.

avec les fonctions usuelles + , - , * , etc.
et les comparaisons :
Nat.eqb pour le test d'égalité
Nat.ltb pour le test plus petit
Nat.leb pour le test plus petit ou égal.


CE SONT EUX QU'ON UTILISERA DORÉNAVANT.

*)


(* -------------------------------------------------------------------------- *)

(* 2. PREMIÈRES PREUVES EN LOGIQUE PROPOSITIONNELLE *)

(* Introduction des mots-clés 
    - assumption
    - intro
    - apply
    - destruct
    - split
    - left / right *)

(* On introduit les variables propositionnelles avec lesquelles 
   on va travailler par la suite *)
Context (P Q R S T U: Prop).

(* LA FLÈCHE *)
(* - axiome : assumption
   - introduction de la flèche : intro [nom qu'on donne à l'hypothèse] 
   - élimination de la flèche : apply [nom de l'hypothèse utilisée] *)

(* EXERCICE 13 *)
Theorem exercice_13: P -> (P -> Q) -> Q.
Proof.
intro HP.
intro HPQ.
apply HPQ.
assumption.
Qed.


(* EXERCICE 14 *)
Theorem exercice_14: (P -> Q) -> (Q -> R) -> (P -> R).
Proof.
intro HPQ.
intro HQR.
intro HP.
apply HQR.
apply HPQ.
assumption.
Qed.

(* LE ET *)
(* Une variante de la question précédente avec /\ *)
(* - décomposition du /\ en hypothèse : destruct [nom de l'hypothèse avec /\] *)

(* EXERCICE 15 *)
Theorem exercice_15: (P -> Q) /\ (Q -> R) -> (P -> R).
Proof.
intro HPQeQR.
intro HP.
destruct HPQeQR as [HPQ HQR].
apply HQR.
apply HPQ.
assumption.
Qed.

(* - introduction du /\ : split *)
(* On obtient bien deux sous-buts *)

(* EXERCICE 15 *)
Theorem exercice_16 : P -> Q -> P /\ Q.
Proof.
intro HP.
intro HQ.
split.
apply HP.
assumption.
Qed.
  
(* LE OU *)
(* - introduction du \/ :
       - depuis la droite : right
       - depuis la gauche : left
   - decomposition du \/ en hypothèse : destruct [nom de l'hypothèse avec \/]*)

(* EXERCICE 17 *)
Theorem exercice_17: (P \/ Q) -> (Q \/ P).
Proof.
intro HPoQ.
destruct HPoQ as [HP | HQ].
right.
apply HP.
left.
assumption.
Qed.


(* zéro constructeur *)
Print False. 
(* un seul constructeur car une seule règle d'intro *)
Print and.
(* deux constructeurs car deux règles d'intro *)
Print or.  

(* destruct donne bien un sous but par constructeur *)


(* EXERCICE 18 *)
(* On remarque que comme False n'a aucun constructeur : le destruct résout le but *)
Theorem ex_falso_quodlibet : False ->  P.
Proof.
intro f.
destruct f.
Qed.

(* EXERCICE 19 *)
(** un peu difficile **)
(* Plus généralement, la tactique exfalso remplace tout but par False. *)
(* Si on peut déduire False des hypothèses, c'est alors gagné ! *)
Theorem ex_falso_quodlibet_Q : (P -> False) -> P -> (Q \/ (R -> S /\ T) -> U).
Proof.
intro HPf.
intro HP.
intro HQoRST.
exfalso.
apply HPf.
apply HP.
Qed.
  
(* -------------------------------------------------------------------------- *)
