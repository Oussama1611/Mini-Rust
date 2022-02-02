# Mini-Rust

Le but de ce projet est de réaliser un mini-compilateur du langage de programmation [Rust](https://www.rust-lang.org/).

___
### **Le langage Rust :**

Rust est un langage de programmation compilé multi-paradigme conçu et développé par Mozilla Research depuis 2015. Il a été conçu pour être « un langage fiable, concurrent, pratique », supportant les styles de programmation purement fonctionnel, modèle d'acteur, procédural, ainsi qu'orienté objet sous certains aspects.

En 2020, ses domaines de prédilection sont la programmation système, les applications en ligne de commande, les applications Web via WebAssembly, les services réseaux et les systèmes embarqués.
___
### **Hello, World par Rust :**
```rust
    fn main(){
        println!("Hello, world!");
    }
```
___
### **Grammaire du langage :**

### **Syntax :**

Nous utilisons les notations suivantes dans la grammaire :

Notation | Signification
-------- | ------------------------------------------------------------------------------
⟨regle⟩⋆  | repetition de la regle ⟨regle⟩ un nombre quelconque de fois (y compris aucune)
⟨regle⟩+  | repetition de la regle ⟨regle⟩ au moins une fois
⟨regle⟩?  | repetition optionnelle de la regle ⟨regle⟩ (i.e. 0 ou 1 fois)


#### **Les conventions léxicales :**

* *Les blancs* : espaces, tabulations, les retour-chariot.

* *Les commentaires* : commencent par '//' et s'étendent jusqu'à la fin de la ligne.

* *Les identificateurs* : obeeissent à l’expression reguliere ⟨ID⟩ suivante :

    ```
        ⟨chiffre⟩ ::= 0–9
        ⟨alpha⟩ ::= a–z | A–Z
        ⟨ID⟩ ::= ⟨alpha⟩ (⟨alpha⟩ | ⟨chiffre⟩ | _)

    ```

* Les mots clés :

```rust
{
    if,
    else,
    false,
    true,
    fn,
    struct,
    let,
    mut,
    const,
    return,
    struct,
    while,
    loop,
    for,
    break,
    continue,
    in,
}

```

#### **Les règles de production :**


```rust
⟨DECL⟩ ::= ⟨DECL FON⟩ | ⟨DECL STRUCT⟩

⟨DECL STRUCT⟩ ::= struct ⟨ID⟩ '{' (⟨ID⟩ : ⟨TYPE⟩)⋆, '}'

⟨DECL FON⟩ ::= fn ⟨ID⟩ ( ⟨ARG⟩⋆, ) (-> ⟨TYPE⟩)? ⟨BLOC⟩

⟨TYPE⟩ ::= String | bool | ⟨ NUM_TYPE_TOKEN ⟩ | ()

⟨ARG⟩ ::= ⟨ID⟩ : ⟨TYPE⟩


⟨BLOC⟩ ::= '{' ⟨INSTR ⟩⋆ ⟨EXPR ⟩? '}'


⟨INSTR⟩ ::= ⟨EXPR⟩;
        | let mut? ⟨ID⟩ = ⟨EXPR⟩;
        | let mut? ⟨ID⟩ = ⟨ID⟩ '{' (⟨ID⟩ : ⟨EXPR⟩)⋆, '}';
        | while ⟨EXPR⟩ ⟨BLOC⟩
        | loop ⟨BLOC⟩
        | for ⟨EXPR⟩ ⟨BLOC⟩
        | return ⟨EXPR⟩? ;
        | ⟨IF⟩

⟨IF⟩ ::= if ⟨EXPR⟩ ⟨BLOC⟩ (else (⟨BLOC⟩ | ⟨if ⟩))?

⟨EXPR⟩ ::= ⟨NUM TOKEN ⟩ | true | false
        | ⟨ID⟩
        | ⟨EXPR⟩ ⟨OPR⟩ ⟨EXPR⟩ | ⟨NEG⟩ ⟨EXPR⟩
        | ⟨ID⟩ ( ⟨EXPR⟩⋆, )
        | ⟨ID⟩ in (⟨NUM TOKEN⟩..⟨NUM TOKEN⟩)
        | println! ( ⟨ID⟩ | ⟨CHAINE⟩)
        | ⟨BLOC⟩
        | ⟨IF⟩
        | ( ⟨EXPR ⟩ )

⟨OPR⟩ ::= ==| != | < | <= | > | >= | + | - | * | / | % | && | || | =

⟨NEG⟩ ::= - | !

⟨CHAINE⟩ ::= ”⟨ID⟩∗”
```

___
### **Les tâches réalisées durant ce projet :**

- [x] Analyseur Léxicale
- [x] Analyseur Syntaxique
- [x] Analyseur Sémantique
___
### **Pour exécuter le projet :**
Pour exécuter le compilateur, utilisez les commandes suivantes :
1. Compiler le projet à l'aide de gcc :
    ```shell
        cd "Mini-Rust"
        gcc *.c -o compiler
    ```
2. Exécuter le compilateur en passant le fichier Rust .rs à compiler :
    ```shell
        ./compiler "Fichier Rust"
    ```

___
### **Contributeurs :**
Ce projet a été réalisé par : 
  
  * [Krab Oussama](https://github.com/oussama1611)
  * [Zarkaoui Idriss](https://github.com/ZarkaouiI)
  * [Salbi Mohamed](https://github.com/vulture990)
  * [Benzha Yahya](https://github.com/OdapX)
  
___
