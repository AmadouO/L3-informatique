(* TP1 *)


(* rappels sur les listes *)

(* Proposer une fonction qui sur la donnée de deux listes retourne la concaténation des deux listes (sans aller chercher dans la doc) *)
let rec concat l1 l2 =
  match l1 with
  | [] -> l2                (* Si la première liste est vide, retourne la seconde liste *)
  | h::t -> h :: concat t l2 (* Sinon, prends la tête de la première liste et concatène le reste *)

(* Exemple d'utilisation *)
let _ = 
  let l1 = [1; 2; 3] in
  let l2 = [4; 5; 6] in
  let result = concat l1 l2 in
  Printf.printf "Résultat: [%s]\n" (String.concat "; " (List.map string_of_int result));;


(* Proposer une fonction qui sur la donnée d'une liste de couples
  (clef,valeur) et d'une clef retourne la première valeur associée à
  cette clef. On appellera ce genre de liste "liste
  d'associations". Que faut-il retourner si jamais on considère des
  listes dans lesquelles il peut ne pas y avoir de valeur associée ? *)

  let rec find_value key assoc_list =
    match assoc_list with
    | [] -> None  (* Si la liste est vide, il n'y a pas de valeur associée, on retourne None *)
    | (k, v) :: t ->
        if k = key then Some v (* Si la clef est trouvée, on retourne la valeur sous forme de Some *)
        else find_value key t  (* Sinon, on continue à chercher dans le reste de la liste *)
  
  (* Exemple d'utilisation *)
  let _ = 
    let assoc_list = [(1, "un"); (2, "deux"); (3, "trois")] in
    match find_value 2 assoc_list with
    | Some v -> Printf.printf "Valeur trouvée : %s\n" v
    | None -> Printf.printf "Aucune valeur associée à la clef\n"
  


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

 (* Définition du type pour un automate fini *)
type automate_fini = {
  alphabet : string list;         (* Vocabulaire : liste de chaînes de caractères *)
  etats : int list;               (* Liste des états *)
  etat_initial : int;             (* État initial *)
  etats_finaux : int list;        (* Liste des états finaux *)
  transitions : (int * string * int) list;  (* Fonction de transition sous forme de triplets (état_départ, symbole, état_arrivée) *)
}

(* Exemple d'un automate fini *)
let exemple_automate = {
  alphabet = ["a"; "b"];            (* Vocabulaire : les symboles "a" et "b" *)
  etats = [0; 1; 2];                (* Trois états : 0, 1 et 2 *)
  etat_initial = 0;                 (* L'état initial est 0 *)
  etats_finaux = [2];               (* L'état final est 2 *)
  transitions = [(0, "a", 1); (1, "b", 2)];  (* Transitions : de 0 à 1 avec "a", de 1 à 2 avec "b" *)
}



(*
  Proposer une fonction qui sur la donnée d'un automate, d'un mot et
  d'un état retourne un bool indiquant si l'état atteint au terme de
  l'exécution de l'automate sur le mot à partir de l'état indiqué est
  acceptant (true) ou pas (false).

  En déduire une fonction qui détermine si un mot appartient au
  langage reconnu par un automate *)

  (* Fonction qui simule l'exécution de l'automate sur un mot à partir d'un état donné *)
let rec execute automate mot etat_actuel =
  match mot with
  | [] -> etat_actuel  (* Si le mot est vide, on retourne l'état actuel *)
  | symbole :: reste_mot -> 
      (* On cherche une transition correspondant à l'état actuel et au symbole *)
      let transition_suivante = List.find_opt 
          (fun (etat_de_depart, s, etat_d_arrivee) -> 
            etat_de_depart = etat_actuel && s = symbole)
          automate.transitions
      in
      match transition_suivante with
      | None -> failwith "Aucune transition possible"  (* Pas de transition, erreur *)
      | Some (_, _, etat_suivant) -> 
          execute automate reste_mot etat_suivant  (* Appel récursif pour traiter le reste du mot *)

(* Fonction qui indique si l'état atteint à la fin est un état acceptant *)
let est_acceptant automate mot etat =
  let etat_final = execute automate mot etat in
  List.mem etat_final automate.etats_finaux  (* On vérifie si l'état final est dans la liste des états finaux *)

(******************************************)
(* Fonction qui détermine si un mot est accepté par l'automate *)
let mot_accepte automate mot =
  est_acceptant automate mot automate.etat_initial
(******************************************************)
(* Définition d'un automate exemple *)
let automate_exemple = {
  alphabet = ["a"; "b"];
  etats = [0; 1; 2];
  etat_initial = 0;
  etats_finaux = [2];
  transitions = [(0, "a", 1); (1, "b", 2)];
}

(* Test de la fonction *)
let _ =
  let mot1 = ["a"; "b"] in
  let mot2 = ["a"; "a"] in
  Printf.printf "Le mot ['a'; 'b'] est accepté : %b\n" (mot_accepte automate_exemple mot1);
  Printf.printf "Le mot ['a'; 'a'] est accepté : %b\n" (mot_accepte automate_exemple mot2)



(*
  Les fonctions de transition peuvent être vues comme associant, à un
  état, des associations entre caractère lu et état d'arrivée.

  Un moyen **naïf** de représenter ces associations est d'utiliser des
  listes.

  Proposer la structure d'association permettant de construire
  l'automate acceptant les mots sur "a" et "b" comportant un nombre
  impair de "b".

  Proposer cet automate et le tester.  *)

  (* Définition de la structure de l'automate avec une liste d'associations *)
type automate_fini = {
  alphabet : string list;          (* Alphabet : liste de symboles *)
  etats : int list;                (* Liste des états *)
  etat_initial : int;              (* État initial *)
  etats_finaux : int list;         (* États finaux *)
  transitions : (int * (string * int) list) list;  (* Liste d'associations : état -> (symbole -> état) *)
}

(* Automate acceptant un nombre impair de "b" *)
let automate_impair_b = {
  alphabet = ["a"; "b"];
  etats = [0; 1];
  etat_initial = 0;
  etats_finaux = [1];  (* On accepte les états ayant un nombre impair de "b" *)
  transitions = [
    (0, [("a", 0); ("b", 1)]);  (* Depuis l'état 0 (pair) : "a" -> reste 0, "b" -> devient 1 (impair) *)
    (1, [("a", 1); ("b", 0)]);  (* Depuis l'état 1 (impair) : "a" -> reste 1, "b" -> devient 0 (pair) *)
  ];
}
(****************************************************************************)
(* Fonction pour récupérer l'état suivant en fonction de l'état actuel et du symbole lu *)
let rec trouver_transition etat symbole transitions =
  match transitions with
  | [] -> None  (* Aucune transition trouvée *)
  | (etat_source, assoc_list) :: reste_transitions ->
      if etat_source = etat then 
        List.assoc_opt symbole assoc_list  (* Cherche la transition dans les associations du bon état *)
      else 
        trouver_transition etat symbole reste_transitions  (* Continue à chercher dans les autres transitions *)

(* Fonction qui simule l'exécution de l'automate sur un mot donné *)
let rec execute automate mot etat_actuel =
  match mot with
  | [] -> etat_actuel  (* Si le mot est vide, on retourne l'état actuel *)
  | symbole :: reste_mot ->
      match trouver_transition etat_actuel symbole automate.transitions with
      | None -> failwith "Aucune transition possible"  (* Pas de transition trouvée pour ce symbole *)
      | Some etat_suivant -> 
          execute automate reste_mot etat_suivant  (* Appel récursif pour traiter le reste du mot *)

(* Fonction qui indique si un état est acceptant *)
let est_acceptant automate mot =
  let etat_final = execute automate mot automate.etat_initial in
  List.mem etat_final automate.etats_finaux  (* Vérifie si l'état final est dans les états finaux *)
(******************************************************)
(* Exemples de tests avec différents mots *)
let _ =
  let mot1 = ["a"; "b"; "a"; "b"; "b"] in  (* Mot avec 3 "b" -> impair *)
  let mot2 = ["a"; "b"; "a"; "b"] in       (* Mot avec 2 "b" -> pair *)
  let mot3 = ["a"; "a"; "a"] in            (* Mot sans "b" -> pair *)
  Printf.printf "Le mot ['a'; 'b'; 'a'; 'b'; 'b'] est accepté : %b\n" (est_acceptant automate_impair_b mot1);
  Printf.printf "Le mot ['a'; 'b'; 'a'; 'b'] est accepté : %b\n" (est_acceptant automate_impair_b mot2);
  Printf.printf "Le mot ['a'; 'a'; 'a'] est accepté : %b\n" (est_acceptant automate_impair_b mot3)




(* Proposer une fonction qui sur une liste d'associations indique si cette liste contient un choix non déterministe *)

type transitions = (int * (string * int) list) list

(* Fonction qui vérifie s'il existe un choix non déterministe dans une liste d'associations *)
let rec contient_non_determinisme transitions =
  let rec verifie_doublons liste =
    match liste with
    | [] -> false
    | (symbole, _) :: reste ->
        if List.exists (fun (s, _) -> s = symbole) reste then true
        else verifie_doublons reste
  in
  match transitions with
  | [] -> false  (* Aucune transition, donc pas de non-déterminisme *)
  | (_, assoc_list) :: reste ->
      if verifie_doublons assoc_list then true
      else contient_non_determinisme reste

(* Exemple de transitions *)
let transitions = [
  (0, [("a", 1); ("b", 2)]);       (* Aucun non-déterminisme ici *)
  (1, [("a", 1); ("a", 2)]);       (* Non-déterminisme ici : deux transitions pour "a" *)
  (2, [("b", 1)]);
]

(* Test de la fonction *)
let _ =
  Printf.printf "L'automate contient-il un non-déterminisme ? %b\n" (contient_non_determinisme transitions)


(* Proposer une fonction qui sur la description sous forme d'associations d'une fonction de transition indique si elle est non déterministe. *)
(* Comment simplifier ce problème ? *)

(* Type des transitions : (etat, (symbole, etat d'arrivée)) *)
type transition = (int * string * int)

(* Fonction pour vérifier si une fonction de transition est non déterministe *)
let est_non_deterministe transitions =
  (* Fonction pour vérifier s'il y a des doublons de symboles pour un état donné *)
  let rec contient_doublons transition_list =
    match transition_list with
    | [] -> false
    | (_, symbole1, _) :: reste ->
        if List.exists (fun (_, symbole2, _) -> symbole1 = symbole2) reste then true
        else contient_doublons reste
  in
  (* Regrouper les transitions par état de départ *)
  let transitions_par_etat = 
    List.fold_left (fun acc (etat, symbole, etat_suivant) ->
      let assoc_etat = try List.assoc etat acc with Not_found -> [] in
      (etat, (etat, symbole, etat_suivant) :: assoc_etat) :: List.remove_assoc etat acc
    ) [] transitions
  in
  (* Vérifier chaque état pour un éventuel non-déterminisme *)
  List.exists (fun (_, liste_transitions) -> contient_doublons liste_transitions) transitions_par_etat

(* Exemple de transitions avec un non-déterminisme pour l'état 1 *)
let transitions = [
  (0, "a", 1); (0, "b", 2);
  (1, "a", 1); (1, "a", 2); (* Non-déterminisme ici : deux transitions pour "a" depuis l'état 1 *)
  (2, "b", 1)
]

(* Test de la fonction *)
let _ =
  Printf.printf "L'automate est non déterministe : %b\n" (est_non_deterministe transitions)


(* Pour ceux qui ont fini : minimiser un automate (données : automate et structure d'association), attention il va falloir d'autres structures *)

(* Types pour représenter les automates *)
type transition = (int * string * int)
type automate_fini = {
  alphabet : string list;
  etats : int list;
  etat_initial : int;
  etats_finaux : int list;
  transitions : transition list;
}

(* Fonction pour obtenir les états acceptants et non acceptants *)
let partition_initiale automate =
  let acceptants = List.fold_left (fun acc etat ->
    if List.mem etat automate.etats_finaux then
      etat :: acc
    else
      acc
  ) [] automate.etats in
  let non_acceptants = List.filter (fun etat -> not (List.mem etat automate.etats_finaux)) automate.etats in
  [acceptants; non_acceptants]  (* Retourne une partition avec deux groupes *)

(* Fonction pour vérifier si deux états sont distinguables *)
let etats_distinguables automate etat1 etat2 =
  let transitions_par_etat = List.fold_left (fun acc (e1, s, e2) ->
    if e1 = etat1 || e1 = etat2 then
      let cible = if e1 = etat1 then etat1 else etat2 in
      (cible, s, e2) :: acc
    else
      acc
  ) [] automate.transitions in
  List.exists (fun (e, s, e2) ->
    List.exists (fun (e', s', e2') ->
      e <> e' && e2 <> e2' && s = s'  (* Compare les cibles des états *)
    ) transitions_par_etat
  ) transitions_par_etat

(* Fonction pour affiner la partition *)
let rec affiner_partition automate partitions =
  let rec iterer partitions acc =
    match partitions with
    | [] -> acc
    | p :: reste ->
        let new_parts = List.fold_left (fun acc etat1 ->
          List.fold_left (fun acc etat2 ->
            if etats_distinguables automate etat1 etat2 then
              acc
            else
              (* Créer une nouvelle partition avec etat1 et etat2 *)
              (etat1 :: etat2 :: []) :: acc
          ) acc p
        ) [] p in
        let updated = new_parts @ reste in
        iterer updated acc
  in
  let nouvelles_partitions = iterer partitions [] in
  if nouvelles_partitions = partitions then partitions
  else affiner_partition automate nouvelles_partitions

(* Fonction pour minimiser l'automate *)
let minimiser automate =
  let partitions = partition_initiale automate in
  let partitions_affinees = affiner_partition automate partitions in
  (* Construction de l'automate minimisé *)
  let nouvelles_transitions = [] in  (* À construire avec la nouvelle structure d'états *)
  (* On va devoir mapper chaque état à son équivalent dans la partition *)
  let etat_map = List.fold_left (fun acc p ->
    let new_etat = List.hd p in
    List.fold_left (fun acc etat -> (etat, new_etat) :: acc) acc p
  ) [] partitions_affinees in
  let etats_min = List.map List.hd partitions_affinees in
  {
    alphabet = automate.alphabet;
    etats = etats_min;
    etat_initial = List.assoc automate.etat_initial etat_map;  (* Nouveau état initial *)
    etats_finaux = List.filter (fun etat -> List.exists (fun p -> List.mem etat p) partitions_affinees) etats_min;
    transitions = nouvelles_transitions  (* À construire avec la logique de transition *)
  }


  (* Exemple d'automate à minimiser *)
let automate_exemple = {
  alphabet = ["a"; "b"];
  etats = [0; 1; 2; 3];
  etat_initial = 0;
  etats_finaux = [2; 3];
  transitions = [
    (0, "a", 1);
    (0, "b", 2);
    (1, "a", 0);
    (1, "b", 3);
    (2, "a", 3);
    (2, "b", 2);
    (3, "a", 2);
    (3, "b", 1);
  ]
}

(* Test de la fonction de minimisation *)
let automate_minimisé = minimiser automate_exemple
