(* TP1 *)


(* rappels sur les listes *)

(* Proposer une fonction qui sur la donnée de deux listes retourne la concaténation des deux listes (sans aller chercher dans la doc) *)

let rec concatene l1 l2 =
  match l1 with
  | [] -> l2
  | t::q -> t :: concatene q l2;;

  let l1 = [1; 2; 3];;
  let l1 = [1; 2; 3];;

  let conca = concatene l1 l2;;
  

(* Proposer une fonction qui sur la donnée d'une liste de couples
  (clef,valeur) et d'une clef retourne la première valeur associée à
  cette clef. On appellera ce genre de liste "liste
  d'associations". Que faut-il retourner si jamais on considère des
  listes dans lesquelles il peut ne pas y avoir de valeur associée ? *)

  let rec association k liste_ass  =
    match liste_ass with
    | [] -> 0 
    | (cle, valeur) :: t ->
        if cle = k then  valeur 
        else association k t ;;

  let l = [(1,2);(3,4)];;

  let ass = association 1 l;;


 (*
  Plusieurs moyens de définir des automates finis sont envisageables :
  un type somme à un seul constructeur équipé d'un n-uplet, par
  exemple ou encore un enregistrement. Les enregistrements en ocaml
  sont écrits entre accolades, les champs sont séparés par des ";",
  etc.  Un intérêt des enregistrement est que les fonctions de
  projection sont déjà définies.

  Pour simplifier, nos automates auront un vocabulaire donné sous la
  forme d'une liste de chaînes de caractères et les états seront des
  entiers (fournis aussi sous forme de liste. Les mots seront des
  listes de chaînes.

  Définir le type des automates finis.

 *)

 type automate = {
  vt : string list;
  states : int list;
  initial : int ;
  finaux : int list;
  transition : int -> string -> int  
 };;


(*
  Proposer une fonction qui sur la donnée d'un automate, d'un mot et
  d'un état retourne un bool indiquant si l'état atteint au terme de
  l'exécution de l'automate sur le mot à partir de l'état indiqué est
  acceptant (true) ou pas (false).

  En déduire une fonction qui détermine si un mot appartient au
  langage reconnu par un automate *)



(*
  Les fonctions de transition peuvent être vues comme associant, à un
  état, des associations entre caractère lu et état d'arrivée.

  Un moyen **naïf** de représenter ces associations est d'utiliser des
  listes.

  Proposer la structure d'association permettant de construire
  l'automate acceptant les mots sur "a" et "b" comportant un nombre
  impair de "b".

  Proposer cet automate et le tester.  *)



(* Proposer une fonction qui sur une liste d'associations indique si cette liste contient un choix non déterministe *)



(* Proposer une fonction qui sur la description sous forme d'associations d'une fonction de transition indique si elle est non déterministe. *)
(* Comment simplifier ce problème ? *)


(* Pour ceux qui ont fini : minimiser un automate (données : automate et structure d'association), attention il va falloir d'autres structures *)

