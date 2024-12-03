(*
LIFLF - TP noté - lundi 4 décembre 2023 8h00

Evaluation pratique en temps limité : 30 minutes

À REPONDRE EN COMPLÉTANT DIRECTEMENT CE FICHIER

Fichier à téléverser dans Tomuss à 8h30 au plus tard dans la case "TPN/rendu_A".
*)



(* PARTIE 1 - AUTOMATES *)
(*----------------------------------------------------------------------------*)

(* Définitions nécessaires pour la suite des exercices *)

Require Import Nat.
Inductive Alphabet : Type :=
| a : Alphabet
| b : Alphabet
| c : Alphabet.
Definition comp_alphabet (x y : Alphabet) : bool :=
  match x with
  | a => match y with a => true  | b => false | c => false end
  | b => match y with a => false | b => true  | c => false end
  | c => match y with a => false | b => false | c => true  end
end.
Require Export List.
Import ListNotations.
Fixpoint appartient (x : nat) (l : list nat) : bool :=
  match l with
  | [] => false
  | h::rl => (Nat.eqb x h) || (appartient x rl)
  end.
Fixpoint trouve (assoc : list (Alphabet * nat)) (key : Alphabet) : option nat :=
  match assoc with
    | [] => None
    | h::rassoc => if (comp_alphabet key (fst h)) then (Some (snd h))
                   else trouve rassoc key
  end.
Inductive Automate : Type :=
    automate : list nat -> list Alphabet -> (nat -> Alphabet -> option nat) -> nat -> list nat -> Automate.
Definition etats (M : Automate) :  list nat :=
  match M with
    automate ql _ _ _ _ => ql
  end.
Definition symboles (M : Automate) :  list Alphabet :=
  match M with
    automate _ sigma _ _ _ => sigma
  end.
Definition initial  (M : Automate) :  nat :=
  match M with
    automate _ _ _ q0 _ => q0
  end.
Definition acceptant  (M : Automate) (q : nat) : bool  :=
  match M with
    automate _ _ _ _ lF => (appartient q lF)
  end.
Definition transition  (M : Automate) (q : nat) (c : Alphabet) : option nat :=
  match M with
    automate _ _ f _ _ => f q c
  end.
Fixpoint execute (M : Automate)  (q : nat) (w : list Alphabet) : option nat :=
  match w with
  | [] => Some q
  | h::rw => match transition M q h with
             | None => None
             | Some e => execute M e rw end
  end.
Definition reconnait (M : Automate) (w : list Alphabet) : bool :=
  match (execute M (initial M) w) with
  | None => false
  | Some e => acceptant M e
  end.


(* Soit l'alphabet {a,b}.
   Soit L le langage des mots contenant un nombre pair de a et un nombre impair de b. *)

(* QUESTION 1a *)
(* Définissez l'automate complet "M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b" à quatre états qui accepte le langage L. *)
Definition M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b : Automate :=
  automate
    [0; 1; 2; 3] (* États *)
    [a; b]        (* Alphabet *)
    (fun q c =>    (* Fonction de transition *)
       match q, c with
       | 0, a => Some 1 (* Pair/impair → Impair/impair *)
       | 0, b => Some 2 (* Pair/impair → Pair/pair *)
       | 1, a => Some 0 (* Impair/impair → Pair/impair *)
       | 1, b => Some 3 (* Impair/impair → Impair/pair *)
       | 2, a => Some 3 (* Pair/pair → Impair/pair *)
       | 2, b => Some 0 (* Pair/pair → Pair/impair *)
       | 3, a => Some 2 (* Impair/pair → Pair/pair *)
       | 3, b => Some 1 (* Impair/pair → Impair/impair *)
       | _, _ => None    (* Transition invalide *)
       end)
    2               (* État initial : pair pour `a`, pair pour `b` *)
    [0].            (* État acceptant : pair pour `a`, impair pour `b` *)


(* QUESTION 1b *)
(* Vérifiez que votre automate accepte le mot b et le mot abaabba, et refuse le mot vide et le mot bba. *)

(* Définir les mots de test *)
Definition mot_b := [b].
Definition mot_abaabba := [a; b; a; a; b; b; a].
(* Definition mot_vide := []. *)
Definition mot_vide := @nil Alphabet.
Definition mot_bba := [b; b; a].

(* Vérification des mots *)
Eval compute in reconnait M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b mot_b.
(* Doit renvoyer true, car "b" est accepté *)

Eval compute in reconnait M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b mot_abaabba.
(* Doit renvoyer true, car "abaabba" est accepté *)

Eval compute in reconnait M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b mot_vide.
(* Doit renvoyer false, car le mot vide n'est pas accepté *)

Eval compute in reconnait M_contient_un_nb_pair_de_a_et_un_nb_impair_de_b mot_bba.
(* Doit renvoyer false, car "bba" n'est pas accepté *)

(* PARTIE 2 - QUELQUES FONCTIONS *)
(*----------------------------------------------------------------------------*)

Check Nat.eqb.

(* QUESTION 2a *)
(* Définissez la fonction "map"
        Paramètres : une liste de nat l et une fonction f : nat -> nat
        Retour : la liste résultant de l'application de la fonction f à tous les éléments de la liste l
*)

Fixpoint map (f : nat -> nat) (l : list nat) : list nat :=
  match l with
  | [] => []                     (* Cas de base : une liste vide donne une liste vide *)
  | x :: xs => (f x) :: (map f xs) (* Cas inductif : applique f à la tête et appelle récursivement sur la queue *)
  end.
Definition double (x : nat) : nat := x * 2.

(* Exemple 1 : doubler les éléments d'une liste *)
Eval compute in map double [1; 2; 3; 4].
(* Résultat attendu : [2; 4; 6; 8] *)

(* QUESTION 2b *)
(* Définissez la fonction "puissance_4" 
        Paramètres : un nat n
        Retour : n élevé à la puissance 4
*)

Definition puissance_4 (n : nat) : nat :=
  n * n * n * n.


(* Décommentez les exemples *)
(**)
Goal (puissance_4 2) = 16.
cbv. reflexivity. Qed.
Goal (puissance_4 0) = 0.
cbv. reflexivity. Qed.


(* QUESTION 2c *)
(* Définissez la fonction "map_puissance_4" 
        Paramètres : une list de nat l
        Retour : la liste l avec chaque élément élevé à la puissance 4
*)

Definition map_puissance_4 (l : list nat) : list nat :=
  map puissance_4 l.


(* Décommentez les exemples *)
(* *)
Goal (map_puissance_4 [1 ; 3 ; 2]) = [1 ; 81 ; 16].
cbv. reflexivity. Qed.
Goal (map_puissance_4 []) = [].
cbv. reflexivity. Qed.


(* QUESTION 2d *)
(* Définissez la fonction "supprime"
        Paramètres : un nat n et une liste de nat l
        Retour : la liste l sans la première occurence de n (le cas échéant), la liste l elle-même sinon
*)
Fixpoint supprime (n : nat) (l : list nat) : list nat :=
  match l with
  | [] => []                            (* Liste vide, rien à supprimer *)
  | x :: xs => if Nat.eqb n x then xs   (* Si l'élément courant est égal à n, on le supprime *)
              else x :: (supprime n xs) (* Sinon, on garde l'élément et on continue la recherche *)
  end.

(* Décommentez les exemples *)
(* *)
Goal supprime 2 [1; 2; 3; 4] = [1; 3; 4].
cbv. reflexivity. Qed.
Goal supprime 5 [1; 2; 3; 4] = [1; 2; 3; 4].
cbv. reflexivity. Qed.


(* QUESTION 2e *)
(* Définissez la fonction "ex"
        Paramètres : une fonction p : nat -> bool et une liste de nat l
        Retour : true s'il existe un élément n0 de l tel que (p n0) = true, false sinon
*)
Fixpoint ex (p : nat -> bool) (l : list nat) : bool :=
  match l with
  | [] => false                    (* Cas de base : une liste vide ne contient aucun élément satisfaisant p *)
  | x :: xs => (p x) || (ex p xs)  (* Cas inductif : vrai si p x est vrai ou si un élément de xs satisfait p *)
  end.


(* Décommentez les exemples *)
(* *)
Goal ex even [1;2;3;4] = true.
cbv. reflexivity. Qed.
Goal ex even [1;3;5;7] = false.
cbv. reflexivity. Qed.
Goal ex even [] = false.
cbv. reflexivity. Qed.


(* QUESTION 2f *)
(* Définissez la fonction "zip"
        Paramètre : une paire de listes de nat
        Retour : la liste de paires correspondantes
   Exemple : voir les tests unitaires ci-dessous
*)

Fixpoint zip (l1 : list nat) (l2 : list bool) : list (nat * bool) :=
  match l1, l2 with
  | [], _ => []                         (* Si la première liste est vide, le résultat est vide *)
  | _, [] => []                         (* Si la deuxième liste est vide, le résultat est vide *)
  | x1 :: xs1, x2 :: xs2 => (x1, x2) :: zip xs1 xs2
                                          (* On associe les têtes des deux listes, puis on continue avec les queues *)
  end.


(* Décommentez les exemples *)
(* *)
Goal zip [1; 2] [true; false] = [(1, true); (2, false)].
cbv. reflexivity. Qed.
Goal zip [1] [true; false] = [(1, true)].
cbv. reflexivity. Qed.
Goal zip [1; 2] [true] = [(1, true)].
cbv. reflexivity. Qed.


(* QUESTION 2g *)
(* Définissez la fonction "unzip"
        Paramètre : une liste de paires de nat
        Retour : la paire de listes correspondantes
   Exemple : voir les tests unitaires ci-dessous
*)
Fixpoint unzip (l : list (nat * bool)) : (list nat * list bool) :=
  match l with
  | [] => ([], [])                            (* Cas de base : une liste vide donne deux listes vides *)
  | (x, y) :: xs => 
      let (l1, l2) := unzip xs in            (* Décomposition récursive sur le reste de la liste *)
      (x :: l1, y :: l2)                     (* Ajout des éléments x et y aux listes séparées *)
  end.


(* Décommentez les exemples *)
(* *)
Goal unzip [(1, true); (2, false)] = ([1; 2], [true; false]).
cbv. reflexivity. Qed.



(* PARTIE 3 - COMPARAISON D'OPTION NAT *)
(*----------------------------------------------------------------------------*)

(* On rappelle la définition de "option A" (NE PAS DÉCOMMENTER, c'est un type prédéfini) :
   Inductive option (A : Type) : Type := 
     | Some : A -> option A
     | None : option A
*)

(* Les lemmes suivants pourront être utiles pour la suite *)
Lemma eqb_true_eq : forall n m, Nat.eqb n m = true -> n = m.
Proof.
apply PeanoNat.Nat.eqb_eq.
Qed.

Lemma eq_eqb_true : forall n m, n = m -> Nat.eqb n m = true.
Proof.
apply PeanoNat.Nat.eqb_eq.
Qed.

(* RAPPEL.
   On peut utiliser un théorème spécialisé aux bons paramètres fixés :
   par exemple
   pose (eqb_true_eq "n_fixe" "m_fixe") as "nom_de_la_nouvelle_hypothèse".
*)

(* QUESTION 3a *)
(* Définissez la fonction "comp_option_nat"
   Paramètres : deux "option nat"
   Retour : true si les deux options nat sont égaux, false sinon. Par convention, comp_option_nat None None = true
*)
Definition comp_option_nat (o1 o2 : option nat) : bool :=
  match o1, o2 with
  | None, None => true                  (* Les deux valeurs sont None, elles sont égales *)
  | Some n1, Some n2 => Nat.eqb n1 n2   (* Compare les valeurs si elles sont toutes deux Some *)
  | _, _ => false                       (* Si l'une est None et l'autre Some, elles sont différentes *)
  end.


(* Décommentez les exemples *)
(* *)
Goal comp_option_nat None None = true.
cbv. reflexivity. Qed.
Goal comp_option_nat (Some 2) (Some 2)  = true.
cbv. reflexivity. Qed.
Goal comp_option_nat (Some 2) (Some 3)  = false.
cbv. reflexivity. Qed.


(* QUESTION 3b *)
(* Prouvez que votre fonction de comparaison est correcte et complète :
   La fonction "comp_option_nat" retourne true SI ET SEULEMENT SI ses deux arguments sont égaux. *)
Lemma comp_option_nat_correct : forall o1 o2 : option nat,
  comp_option_nat o1 o2 = true <-> o1 = o2.
Proof.
  intros o1 o2. split.
  - (* Sens direct : comp_option_nat o1 o2 = true -> o1 = o2 *)
    intros H.
    destruct o1, o2.
    + (* Cas o1 = Some n et o2 = Some n0 *)
      simpl in H. apply eqb_true_eq in H. subst. reflexivity.
    + (* Cas o1 = Some n et o2 = None *)
      simpl in H. discriminate.
    + (* Cas o1 = None et o2 = Some n *)
      simpl in H. discriminate.
    + (* Cas o1 = None et o2 = None *)
      simpl in H. reflexivity.
  - (* Sens réciproque : o1 = o2 -> comp_option_nat o1 o2 = true *)
    intros H. subst.
    destruct o2.
    + (* Cas o2 = Some n *)
      simpl. apply eq_eqb_true. reflexivity.
    + (* Cas o2 = None *)
      simpl. reflexivity.
Qed.


(*----------------------------------------------------------------------------*)
